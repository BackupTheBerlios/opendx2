#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 2 "yuiif.y"
/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#define DXD_ENABLE_SOCKET_POINTERS	/* define SFILE in arch.h, os2 */
#include <dx/dx.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#if DXD_HAS_UNISTD_H
#include <unistd.h>
#endif
#include <string.h>
#ifndef DXD_LACKS_UNIX_UID
#include <pwd.h>
#endif

#if  defined(DXD_NON_UNIX_DIR_SEPARATOR)
#define DX_DIR_SEPARATOR ';'
#define DX_DIR_SEPARATOR_STR ";"
#else
#define DX_DIR_SEPARATOR ':'
#define DX_DIR_SEPARATOR_STR ":"
#endif

#include "exobject.h"
#include "parse.h"
#include "vcr.h"
#include "log.h"

extern int	yylineno;
extern int	yycharno;
extern char	*yyText;
extern SFILE	*yyin;
extern int	yyLeng;
extern int	_dxd_exPPID;

extern int	_dxd_exRemote;


extern int 	_dxd_exUIPacket;

static int		*fnum;
static int		*linenum;
static int		*charnum;
static SFILE		**fps;
static char		**fname;

int		_dxd_exBaseFD = 0;

int		_dxd_exParseError;
node		*_dxd_exParseTree;
char		*_dxd_exParseMesg;

static int	data_len;

static int 	_pushInput	(char *name);
int		yyerror		(char *s);


#define	LIST_APPEND_CHECK(_l,_e)\
{\
    if (_l)\
	LIST_APPEND (_l, _e)\
    else\
	_dxd_exParseError = TRUE;\
}


static void one_dxrc (char *f)
{
    SFILE	*fp;

    if ((fp = fopen (f, "r")) != NULL)
    {
	fclose (fp);
	_pushInput (f);
    }
}

#define	DIFFERENT_FILES(_a,_b) \
(((_a).st_dev != (_b).st_dev) ||\
 ((_a).st_ino != (_b).st_ino) ||\
 (((_a).st_dev == 0) && ((_a).st_ino == 0)) ||\
 (((_b).st_dev == 0) && ((_b).st_ino == 0)))

void _dxf_ExReadDXRCFiles ()
{
    struct passwd	*pass;
    char		buf [1024];
    struct stat		curr;				/* local dir */
    struct stat		home;				/* home  dir */
    struct stat		sys;				/* system dir */
    struct stat		sys2;				/* system dir */
    int			n;
    char		*root;

    /*
     * Since the inputs get stacked we want them in reverse order.
     *
     * We use the stat calls to make sure that we don't include an init
     * file twice.  This could occur previously if $HOME == current dir,
     * etc.
     */

    /* If we are connected to the UI then this is called from the command
     * to get a license. The linefeed from the license command gets read
     * by the include in the dxrc system file. When we return we don't read
     * the linefeed from the license command and our char ptr is not reset.
     * this will cause a syntax error if the next command is a "$" command.
     */
    if(_dxd_exRemote)
        yycharno = 0;

    curr.st_dev = curr.st_ino = 0;
    home.st_dev = home.st_ino = 0;
    sys .st_dev = sys .st_ino = 0;

    buf[0] = '\0';

    if (getcwd (buf, 1022) == NULL)
	buf[0] = '\0';

    n = strlen (buf);
    sprintf (&buf[n], "/%s", DXRC);
    stat (buf, &curr);

    one_dxrc (DXRC);					/* local dir */

#if DXD_LACKS_UNIX_UID
    sprintf(buf, "C:\\%s", DXRC);
    stat(buf, &home);
    if(DIFFERENT_FILES (curr, home))
	one_dxrc (buf);					/* home dir */

#else
    if ((pass = getpwuid (geteuid ())) != NULL)
    {
	sprintf (buf, "%s/%s", pass->pw_dir, DXRC);
	stat (buf, &home);

	if (DIFFERENT_FILES (curr, home))
	    one_dxrc (buf);				/* home dir */
    }
#endif

    if ((root = (char *) getenv ("DXROOT")) != NULL)
    {
	sprintf (buf, "%s/%s", root, DXRC);
	stat (buf, &sys);

	if (DIFFERENT_FILES (curr, sys) &&
	    DIFFERENT_FILES (home, sys))
	    one_dxrc (buf);				/* system */

	sprintf (buf, "%s/lib/%s", root, SYSDXRC);
	stat (buf, &sys2);
        
	if (DIFFERENT_FILES (curr, sys2) &&
	    DIFFERENT_FILES (home, sys2) &&
	    DIFFERENT_FILES (sys, sys2))
	    one_dxrc (buf);				/* 2nd system */

    }
}


Error
_dxf_ExParseInit (char *name, int fd)
{
    int i;

    if (_dxf_ExInitLex() != OK)
	return (ERROR);

    fnum	= (int *)   DXAllocate (sizeof (int));
    linenum	= (int *)   DXAllocate (sizeof (int)    * MAXINCLUDES);
    charnum	= (int *)   DXAllocate (sizeof (int)    * MAXINCLUDES);
    fps		= (SFILE **)DXAllocate (sizeof (SFILE *)* MAXINCLUDES);
    fname	= (char **) DXAllocate (sizeof (char *) * MAXINCLUDES);

    if (fnum == NULL || linenum == NULL || charnum == NULL ||
	fps == NULL || fname == NULL)
	return (ERROR);

    for (i = 0; i < MAXINCLUDES; i++)
	if ((fname[i] = (char *) DXAllocate (sizeof (char) * 128)) == NULL)
	    return (ERROR);

    *fnum = 0;
    linenum[*fnum] = 1;
    charnum[*fnum] = 0;
    strcpy (fname[*fnum], name);
    fps[*fnum] = fdopen (fd, "r");
    yyin = fps[*fnum];
    _dxd_exBaseFD = fd;

    /*
     * can do .rc file processing here.
     * Unlicensed PC's will always load dxrc files here since they don't get "license" message.
     */
#ifndef DXD_WIN
    if (! _dxd_exRemote)
	_dxf_ExReadDXRCFiles ();
#else
    _dxf_ExReadDXRCFiles ();
#endif

    return (OK);
}

#if 0
_parseCleanup()
{
    int i;

    /* close stdin */
    fclose (fps[0]);

    DXFree((Pointer) fnum);
    DXFree((Pointer) linenum);
    DXFree((Pointer) charnum);
    DXFree((Pointer) fps);

    for (i=0; i < MAXINCLUDES; i++)
	DXFree((Pointer)fname[i]);
    DXFree((Pointer)fname);

    _dxf_ExCleanupLex();
}
#endif


typedef struct
{
    char	*path;
    int		len;
} IPath;


static int
_pushInput (char *name)
{
    static int		initme = TRUE;
    static int		npaths = 0;
    static IPath	*ipaths	= NULL;
    int			i;
    int			len;
    SFILE		*fp;
    char		buf[4096];

    while (initme)
    {
	char		*tmp1;
	char		*tmp2;
	int		size;

	initme = FALSE;

	tmp1 = (char *) getenv ("DXINCLUDE");
        tmp2 = (char *) getenv ("DXMACROS");
	if (tmp1 == NULL && tmp2 == NULL) 
	    break;

        if(tmp1 && *tmp1 != '\000') {
            strcpy(buf, tmp1);
            if(tmp2 && *tmp2 != '\000')
                strcat(buf, DX_DIR_SEPARATOR_STR);
        }
        if(tmp2 && *tmp2 != '\000') 
            strcat(buf, tmp2);

	tmp2 = _dxf_ExCopyStringLocal (buf);
        if (tmp2 == NULL) {
           DXWarning("Ignoring DXINCLUDE and DXMACROS environment variables\n");
           break;
        }
	for (tmp1 = tmp2, npaths = 1; *tmp1; )
	    if (*tmp1++ == DX_DIR_SEPARATOR)
		npaths++;
	size = npaths * sizeof (IPath);
	ipaths = (IPath *) DXAllocateLocal (size);
	if (ipaths == NULL)
	{
	    DXPrintError ("Can't initialize file inclusion path");
	    break;
	}
	ExZero (ipaths, size);
	for (tmp1 = tmp2, ipaths[0].path = tmp1, i = 1; i < npaths; tmp1++)
	{
	    if (*tmp1 == DX_DIR_SEPARATOR)
	    {
		*tmp1 = '\000';
		ipaths[i++].path = tmp1 + 1;
	    }
	}
	for (i = 0; i < npaths; i++)
	    ipaths[i].len = strlen (ipaths[i].path);
    }

    if (*fnum >= MAXINCLUDES - 1)
    {
	DXPrintError ("include:  input file nesting level exceeded");
	return (NULL);
    }

    fp = fopen (name, "r");
    for (i = 0; fp == NULL && i < npaths; i++)
    {
	len = ipaths[i].len;
	if (len <= 0)
	    continue;
	strcpy (buf, ipaths[i].path);
#if  defined(DXD_NON_UNIX_DIR_SEPARATOR)
	buf[len] = '\\';
#else
	buf[len] = '/';
#endif
	strcpy (buf + len + 1, name);
	fp = fopen (buf, "r");
    }

    if (fp == NULL && getenv("DXROOT"))
    {
#if  defined(DXD_NON_UNIX_DIR_SEPARATOR)
	sprintf(buf, "%s\\lib\\%s", getenv("DXROOT"), name);
#else
	sprintf(buf, "%s/lib/%s", getenv("DXROOT"), name);
#endif
	fp = fopen (buf, "r");
    }

    if (fp != NULL)
    {
	linenum[*fnum] = yylineno;
	charnum[*fnum] = yycharno;
	(*fnum)++;
	linenum[*fnum] = 1;
	charnum[*fnum] = 0;
	strncpy (fname[*fnum], name, 128);
	fname[*fnum][127] = '\0';
	fps[*fnum] = fp;
	_dxf_ExBeginInput ();
    }
    else
    {
	DXUIMessage ("ERROR", "include:  can't open file '%s'", name);
        /* in script mode running MP you will get 2 prompts on error
         * unless you flush out the newline after the error.
         */
        if(! _dxd_exRemote)
            _dxf_ExFlushNewLine();
    }

    return ((int) fp);
}

static char PopMessage[] = "< INCLUDED FILE > ";

static
_popInput()
{
    char	*cp;
    char	*mp;
    int		i;

    yyerror (NULL);		/* reset error file name and line number */

    if (*fnum > 0)
    {
	fclose (yyin);
	yyin = fps[--(*fnum)];
	yylineno = linenum[*fnum];
	yycharno = charnum[*fnum];
				/* obliterate include file text */
	for (i = 0, cp = yyText, mp = PopMessage; i < yycharno; i++)
	    *cp++ = *mp ? *mp++ : '.';

	return (0);
    }

    return (1);
}

_dxf_ExBeginInput()
{
    yyin = fps[*fnum];
    yylineno = linenum[*fnum];
    yycharno = charnum[*fnum];
}

_dxf_ExEndInput()
{
    linenum[*fnum] = yylineno;
    charnum[*fnum] = yycharno;
}

#line 412 "yuiif.y"
typedef union
{
    char		c;
    int			i;
    float		f;
    char		*s;
    void		*v;
    node		*n;
} YYSTYPE;
#line 431 "y.tab.c"
#define L_OR 257
#define L_AND 258
#define L_NOT 259
#define L_EQ 260
#define L_NEQ 261
#define L_LT 262
#define L_GT 263
#define L_LEQ 264
#define L_GEQ 265
#define A_PLUS 266
#define A_MINUS 267
#define A_TIMES 268
#define A_DIV 269
#define A_IDIV 270
#define A_MOD 271
#define A_EXP 272
#define U_MINUS 273
#define LEX_ERROR 274
#define V_TRUE 275
#define V_FALSE 276
#define T_EOF 277
#define T_EOL 278
#define T_BAR 279
#define T_LPAR 280
#define T_RPAR 281
#define T_LBRA 282
#define T_RBRA 283
#define T_LSQB 284
#define T_RSQB 285
#define T_ASSIGN 286
#define T_COMMA 287
#define T_DOT 288
#define T_DOTDOT 289
#define T_COLON 290
#define T_SEMI 291
#define T_PP 292
#define T_MM 293
#define T_RA 294
#define K_BEGIN 295
#define K_CANCEL 296
#define K_DESCRIBE 297
#define K_ELSE 298
#define K_END 299
#define K_IF 300
#define K_INCLUDE 301
#define K_LIST 302
#define K_MACRO 303
#define K_PRINT 304
#define K_QUIT 305
#define K_THEN 306
#define K_BACKWARD 307
#define K_FORWARD 308
#define K_LOOP 309
#define K_OFF 310
#define K_ON 311
#define K_PALINDROME 312
#define K_PAUSE 313
#define K_PLAY 314
#define K_STEP 315
#define K_STOP 316
#define K_VCR 317
#define P_INTERRUPT 318
#define P_SYSTEM 319
#define P_ACK 320
#define P_MACRO 321
#define P_FOREGROUND 322
#define P_BACKGROUND 323
#define P_ERROR 324
#define P_MESSAGE 325
#define P_INFO 326
#define P_LINQ 327
#define P_SINQ 328
#define P_VINQ 329
#define P_LRESP 330
#define P_SRESP 331
#define P_VRESP 332
#define P_DATA 333
#define P_COMPLETE 334
#define P_IMPORT 335
#define P_IMPORTINFO 336
#define T_INT 337
#define T_FLOAT 338
#define T_STRING 339
#define T_ID 340
#define T_EXID 341
#define YYERRCODE 256
short yylhs[] = {                                        -1,
   58,    0,   54,   54,   54,   54,   54,   54,   54,   54,
   54,   54,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   56,   56,   60,   40,   62,   40,   64,   40,   66,
   40,   67,   40,   68,   40,   69,   40,   70,   40,   72,
   40,   74,   40,   76,   40,   78,   40,   80,   40,   82,
   40,   84,   40,   86,   40,   88,   40,   61,   63,   89,
   89,   90,   65,   38,   27,   27,   11,   11,   71,   73,
   75,   77,   77,   79,   79,   81,   83,   85,   87,   33,
   37,   37,   24,   24,   25,   25,   26,   26,   26,   12,
   49,   49,   48,   48,   47,   47,   47,    1,    1,   21,
   43,   43,   43,   44,   44,    6,    6,    5,    4,    4,
    3,    3,    2,   28,    9,    9,    8,    8,    7,    7,
   55,   20,   20,   19,   19,   19,   19,   10,   10,   10,
   10,   10,   10,   10,   10,   14,   14,   14,   14,   36,
   36,   36,   36,   36,   53,   53,   53,   53,   53,   53,
   52,   52,   46,   46,   46,   46,   46,   46,   51,   51,
   51,   45,   45,   45,   39,   39,   42,   42,   13,   13,
   13,   13,   41,   41,   35,   35,   34,   23,   23,   22,
   50,   59,   93,   94,   30,   18,   17,   32,   32,   31,
   31,   92,   92,   91,   29,   15,   16,
};
short yylen[] = {                                         2,
    0,    2,    1,    1,    1,    1,    2,    2,    1,    1,
    1,    1,    2,    2,    2,    2,    2,    2,    2,    3,
    3,    1,    1,    0,   10,    0,   10,    0,   10,    0,
   10,    0,   10,    0,   10,    0,   10,    0,   10,    0,
   10,    0,   10,    0,   10,    0,   10,    0,   10,    0,
   10,    0,   10,    0,   10,    0,   10,    1,    1,    1,
    3,    3,    3,    1,    1,    1,    1,    1,    1,    1,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    1,
   11,    7,    1,    1,    2,    4,    1,    3,    4,    3,
    1,    1,    1,    2,    1,    2,    2,    1,    1,    3,
    3,    2,    2,    1,    1,    1,    1,    3,    1,    1,
    1,    3,    3,    5,    1,    1,    1,    3,    1,    3,
    1,    1,    3,    1,    1,    3,    1,    3,    3,    3,
    3,    3,    3,    3,    2,    1,    1,    1,    1,    3,
    3,    3,    5,    7,    1,    2,    2,    3,    3,    4,
    3,    3,    1,    2,    2,    3,    3,    4,    1,    2,
    3,    1,    1,    1,    1,    2,    1,    1,    5,    5,
    5,    5,    9,    9,    1,    2,    1,    1,    2,    1,
    1,    1,    1,    1,    1,    1,    0,    1,    1,    2,
    4,    1,    3,    1,    1,    0,    0,
};
short yydefred[] = {                                      1,
    0,    0,   10,   11,    0,    0,  182,    0,    0,    9,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  185,
    0,   95,   98,    0,    0,    0,    4,    5,   99,    3,
    2,    6,   12,  177,    0,   91,   93,    0,    0,    7,
    8,    0,   19,   18,   23,   22,    0,    0,   14,   15,
   16,   17,   13,   96,   97,    0,    0,  102,  103,  107,
  190,  106,    0,    0,    0,   94,  184,   90,    0,   21,
   20,    0,    0,    0,    0,  180,  181,  117,    0,    0,
  127,  163,  124,  115,    0,  168,    0,  167,  138,  164,
  162,  136,  139,  137,  119,  111,    0,    0,  109,    0,
    0,    0,  100,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   83,    0,    0,    0,    0,  135,  125,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  153,
    0,  159,    0,  145,    0,    0,    0,    0,    0,  183,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  108,    0,    0,  191,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   85,    0,    0,    0,  126,    0,    0,
    0,  155,  147,    0,  178,  175,    0,    0,    0,  154,
  140,    0,  160,  142,    0,    0,  146,  141,  151,  152,
  118,  114,    0,    0,    0,    0,    0,    0,  128,  120,
  112,  113,    0,   24,   26,   28,   30,   32,   34,   36,
   38,   40,   42,   44,   46,   48,   50,   52,   54,   56,
    0,    0,    0,    0,   88,    0,    0,    0,    0,  179,
  176,    0,    0,  165,  156,    0,  157,  161,  148,    0,
  149,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   82,
   86,   89,    0,  172,  171,  170,    0,  169,  166,    0,
  143,  158,  150,    0,    0,    0,    0,    0,    0,  196,
  197,  197,    0,    0,    0,    0,    0,    0,    0,  197,
  188,    0,    0,    0,    0,    0,    0,    0,    0,   58,
    0,    0,    0,    0,   60,  194,    0,    0,   64,    0,
    0,   65,   66,   68,    0,   67,    0,   69,    0,   70,
    0,    0,  195,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   80,    0,    0,    0,
    0,  144,   25,    0,   27,    0,   29,  197,   31,   33,
   35,   37,   39,   41,    0,   43,    0,   45,    0,   47,
    0,   49,  197,   51,    0,   53,    0,   55,   57,    0,
    0,    0,   62,   61,   63,  186,  192,    0,    0,    0,
    0,    0,   76,   77,  104,    0,    0,  105,   78,   79,
   81,  174,  173,    0,    0,  193,
};
short yydgoto[] = {                                       1,
   21,   96,   97,   98,   60,   61,   78,   79,   80,   81,
  335,   22,   82,   83,  337,  338,   62,  397,  101,  102,
   23,   86,  133,  124,  125,  126,  331,   24,  342,  129,
   26,  314,  358,   88,  135,   89,   27,  330,  138,   28,
   90,   91,   29,  409,   92,  141,   30,   38,   39,   93,
  143,   94,  145,   31,   95,   47,   32,    2,   33,  262,
  321,  263,  323,  264,  327,  265,  266,  267,  268,  269,
  339,  270,  341,  271,  344,  272,  346,  273,  348,  274,
  350,  275,  352,  276,  354,  277,  356,  278,  324,  325,
  328,  398,  151,   68,
};
short yysindex[] = {                                      0,
    0,   53,    0,    0, -315, -240,    0, -268, -313,    0,
 -261, -261, -128, -128, -261, -261, -261, -261, -240,    0,
 -261,    0,    0, -261, -214,  -52,    0,    0,    0,    0,
    0,    0,    0,    0, -219,    0,    0, -240, -242,    0,
    0, -227,    0,    0,    0,    0, -261, -261,    0,    0,
    0,    0,    0,    0,    0, -108, -313,    0,    0,    0,
    0,    0, -108, -313,  292,    0,    0,    0, -313,    0,
    0, -108,  -34,  -20,    3,    0,    0,    0, -211, -195,
    0,    0,    0,    0,  329,    0, -191,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -179, -173,    0, -147,
  329, -122,    0, -107, -105,  -66,  -63,  -35,  -30,  -12,
   -7,   29,   33,   34,   42,   54,   55,   57,   69,   71,
   72,   78,    0, -195,   76, -105,   56,    0,    0, -108,
  362,    0,   84,    0,   90,  -72, -198,   70,    0,    0,
 -224,    0, -206,    0,    2,  -72,   35,   -9, -108,    0,
 -105, -108, -108, -108, -108, -108, -108, -108, -108, -313,
    0,   63, -108,    0, -315, -315, -315, -315, -315, -315,
 -315, -315, -315, -315, -315, -315, -315, -315, -315, -315,
 -315, -236, -313,    0,  -28,    0,    0,    0, -198, -198,
    0,    0,    0,  -75,    0,    0, -193, -120, -100,    0,
    0,  -57,    0,    0,  104, -238,    0,    0,    0,    0,
    0,    0,  176,  176,  118,  118,  118,  118,    0,    0,
    0,    0,  329,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  114,  115, -105,   63,    0, -197, -195, -195, -185,    0,
    0,  -75, -233,    0,    0, -120,    0,    0,    0,  104,
    0,  117,  119,  127,  128,  137,  138,  143,  144,  146,
  147,  155,  156,  158,  159,  160,  161,  163, -313,    0,
    0,    0, -249,    0,    0,    0, -234,    0,    0, -193,
    0,    0,    0, -315, -313, -315,  149,   96,  -41,    0,
    0,    0, -315, -315, -315, -315, -315, -315, -315,    0,
    0, -105,  173, -195,  130,  183, -315,  184, -242,    0,
  193,  187,  198,  191,    0,    0,  201,  194,    0,  202,
  204,    0,    0,    0,  206,    0,  222,    0,  224,    0,
  228,  216,    0,  230,  220,  232,  223,  236,  226,  241,
  231,  243,  233,  245,  237,  247,    0,  249, -105, -249,
 -234,    0,    0,   63,    0, -313,    0,    0,    0,    0,
    0,    0,    0,    0,  203,    0, -114,    0, -114,    0,
 -313,    0,    0,    0, -313,    0, -313,    0,    0,  115,
 -195, -195,    0,    0,    0,    0,    0,  259, -122,  259,
 -122,  259,    0,    0,    0, -115,    5,    0,    0,    0,
    0,    0,    0,  203, -108,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,  265,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   14,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  266,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  269,  262,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  269,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  272,    0,
    0,    0,    0,    0, -133,    0,  264,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  270,    0,    0,    0,
 -116, -244,    0,  227,  105,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  273,  -76,   65,    0,    0,    0,
    0,  271,    0,  293,    0,    0,    0,    0, -182,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  282,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  274,    0,    0,    0,  300,  322,    0,    0,    0,
    1,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  108,  238,  162,  188,  195,  221,    0,    0,
    0,    0,  -51,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -76,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  269,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -36,  -59,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  278,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  274,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  296,    0,    0,    0,  296,    0,  296,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  297,  298,  299,
  303,  304,    0,    0,    0,   14,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,  419,    0,    0,    0, -102,  435,    0,    0,    0,
    0, -226,    0, -157,    0, -237,   -5,  171,  -33, -118,
    0,  -62, -145,    0,    0,  421,    0,  523,  331,   -2,
 -270,  225,    0,   20, -158,    0,  305,    0, -184,    0,
    0,  -48,  -32,  218,  -37,  532,   -4,    0,    0,  -60,
    0,  -54,  533,    0,  467,  627,  344,    0,  403,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  279,
    0, -106, -112, -135,
};
#define YYTABLESIZE 645
short yytable[] = {                                      25,
   36,   37,  164,   25,  222,  201,   42,  204,  313,  208,
  132,  182,  253,  142,   53,  280,   25,  315,  188,  144,
  144,   34,   85,  184,   35,  139,   20,  245,  260,    7,
  247,  249,  317,   66,  101,   25,  140,  140,  128,  131,
   67,    6,  198,  246,  248,   75,  101,   57,  212,   67,
   84,   99,   69,   87,  100,  137,  290,  241,   67,   65,
  104,  105,  199,  123,  340,   56,  127,  186,  194,   57,
   40,   41,  357,  252,  195,  149,   67,   58,   59,  242,
  202,  193,  203,  150,  162,  150,  282,  191,   76,  283,
  207,  193,  134,  207,  159,  150,  128,  162,  192,   20,
  162,  287,   34,  200,  162,  319,  165,  160,  192,  200,
  313,  161,   34,   76,  407,   85,  407,  291,  213,  214,
  215,  216,  217,  218,  219,   85,  195,  195,  318,  223,
  395,  250,   77,  284,  285,  286,  288,  316,   34,   76,
  281,  258,  162,   34,   76,  404,   87,  121,  254,  187,
  259,  261,   72,  121,  162,  162,  196,  100,   72,  137,
  255,  257,  122,  411,  163,   73,  256,   74,   57,   75,
  122,   73,   56,   74,  122,   75,   58,   59,   57,  137,
  127,   45,   46,  362,  224,  225,  226,  227,  228,  229,
  230,  231,  232,  233,  234,  235,  236,  237,  238,  239,
  240,  359,  392,  289,  187,  293,  393,  137,  196,  196,
  187,   75,  165,  251,  391,  166,   34,   76,  292,  189,
  195,  189,   34,   76,   77,   20,  396,  123,   34,   76,
   77,   20,  130,   63,   64,  123,   34,   76,  244,  123,
    6,  254,  187,  167,  187,   73,  136,   74,  168,   75,
  187,  137,  250,   74,  334,   75,  390,  205,  399,  137,
  401,   34,   76,   75,   34,   76,  169,  162,  205,  146,
  400,  170,  402,  311,   75,  210,  312,  206,  412,  413,
  162,   77,  137,  162,   67,   75,   75,  162,  206,  166,
  415,   64,  322,  332,  336,   25,   25,  195,   20,  187,
  187,  198,   34,   76,   77,   20,  196,  171,   34,   76,
   77,  172,  173,  320,  137,  326,   34,   76,   77,  209,
  174,  199,  343,  343,  343,  343,  343,  343,  343,    3,
    4,    5,  175,  176,    6,  177,  251,  162,  162,   34,
   76,  185,  137,    7,   74,   87,   75,  178,   87,  179,
  180,   87,  408,    8,  408,    9,  181,   10,  197,   11,
   12,   13,  183,  322,   14,   15,   16,   17,   18,   19,
  189,   34,   76,  133,  133,  311,  190,    6,  312,  405,
  196,  405,  406,  187,  406,  187,  133,   75,  133,  158,
  187,  187,   20,  279,  133,  294,    6,  295,  133,   34,
   76,   77,   11,   12,   13,  296,  297,   14,   15,   16,
   17,   18,   19,   43,   44,  298,  299,   49,   50,   51,
   52,  300,  301,   54,  302,  303,   55,  129,  129,  129,
  129,  129,  129,  304,  305,   20,  306,  307,  308,  309,
  129,  310,  129,  154,  155,  156,  157,  158,  129,   70,
   71,    9,  129,  130,  130,  130,  130,  130,  130,   64,
  131,  131,  131,  131,  131,  131,  130,   76,  130,  360,
  361,  363,  364,  131,  130,  131,  365,  366,  130,  367,
  369,  131,  370,  368,  371,  131,  132,  132,  132,  132,
  132,  132,  125,  125,  125,  125,  125,  125,  125,  132,
  372,  132,  373,  134,  134,  375,  374,  132,  376,  377,
  378,  132,  379,  125,  380,  381,  134,  125,  134,  382,
  383,  384,  385,  386,  134,  388,  387,  389,  134,  125,
  125,  125,  125,  125,  125,  125,  168,  168,  168,  168,
  168,  168,  168,  396,  125,  414,  187,  187,   92,  187,
  125,  168,  116,   84,  110,  187,   59,  178,  167,  167,
  167,  167,  167,  167,  167,  168,  168,  168,  168,  168,
  168,  168,  187,  167,  187,   71,   72,   73,  221,  175,
  168,   74,   75,  211,  416,  103,  179,  167,  167,  167,
  167,  167,  167,  167,  152,  153,  154,  155,  156,  157,
  158,  329,  167,  243,  410,  403,  147,  148,  176,  106,
  107,  108,  109,  110,  111,  112,  113,  114,  115,  116,
  117,  118,  119,  120,  121,  220,  122,  152,  153,  154,
  155,  156,  157,  158,  345,  347,  349,  351,  353,  355,
   48,  333,  150,    0,  394,
};
short yycheck[] = {                                       2,
    6,    6,  105,    6,  162,  141,    9,  143,  279,  145,
   73,  124,  197,   74,   19,  242,   19,  267,  131,   74,
   75,  337,   56,  126,    5,   74,  340,  185,  267,  291,
  189,  190,  267,   38,  279,   38,   74,   75,   72,   73,
  283,  282,  267,  189,  190,  284,  291,  284,  151,  283,
   56,   57,  280,   56,   57,  280,  290,  294,  283,  279,
   63,   64,  287,   69,  302,  280,   69,  130,  267,  284,
  339,  340,  310,  267,  137,  287,  283,  292,  293,  182,
  287,  136,  143,  281,  267,  281,  244,  136,  338,  287,
  145,  146,   73,  148,  286,  281,  130,  280,  136,  340,
  283,  287,  337,  141,  287,  290,  289,  287,  146,  147,
  381,  285,  337,  338,  385,  149,  387,  253,  152,  153,
  154,  155,  156,  157,  158,  159,  189,  190,  287,  163,
  368,  194,  339,  246,  247,  248,  249,  283,  337,  338,
  243,  202,  290,  337,  338,  383,  149,  281,  197,  130,
  205,  206,  267,  287,  337,  338,  137,  160,  267,  280,
  198,  199,  279,  390,  287,  280,  267,  282,  284,  284,
  287,  280,  280,  282,  291,  284,  292,  293,  284,  280,
  183,  310,  311,  319,  165,  166,  167,  168,  169,  170,
  171,  172,  173,  174,  175,  176,  177,  178,  179,  180,
  181,  314,  361,  252,  281,  260,  364,  280,  189,  190,
  287,  284,  279,  194,  360,  279,  337,  338,  256,  279,
  283,  281,  337,  338,  339,  340,  341,  279,  337,  338,
  339,  340,  267,  286,  287,  287,  337,  338,  267,  291,
  282,  290,  279,  279,  281,  280,  267,  282,  279,  284,
  287,  280,  315,  282,  296,  284,  359,  267,  377,  280,
  379,  337,  338,  284,  337,  338,  279,  267,  267,  267,
  377,  279,  379,  279,  284,  285,  279,  287,  391,  392,
  280,  339,  280,  283,  283,  284,  284,  287,  287,  289,
  286,  287,  295,  298,  299,  298,  299,  360,  340,  286,
  287,  267,  337,  338,  339,  340,  287,  279,  337,  338,
  339,  279,  279,  294,  280,  296,  337,  338,  339,  285,
  279,  287,  303,  304,  305,  306,  307,  308,  309,  277,
  278,  279,  279,  279,  282,  279,  317,  337,  338,  337,
  338,  286,  280,  291,  282,  281,  284,  279,  284,  279,
  279,  287,  385,  301,  387,  303,  279,  305,  289,  307,
  308,  309,  287,  366,  312,  313,  314,  315,  316,  317,
  287,  337,  338,  266,  267,  381,  287,  282,  381,  385,
  361,  387,  385,  279,  387,  281,  279,  284,  281,  272,
  286,  287,  340,  280,  287,  279,  282,  279,  291,  337,
  338,  339,  307,  308,  309,  279,  279,  312,  313,  314,
  315,  316,  317,   11,   12,  279,  279,   15,   16,   17,
   18,  279,  279,   21,  279,  279,   24,  266,  267,  268,
  269,  270,  271,  279,  279,  340,  279,  279,  279,  279,
  279,  279,  281,  268,  269,  270,  271,  272,  287,   47,
   48,  303,  291,  266,  267,  268,  269,  270,  271,  287,
  266,  267,  268,  269,  270,  271,  279,  338,  281,  287,
  287,  279,  286,  279,  287,  281,  279,  287,  291,  279,
  279,  287,  279,  290,  279,  291,  266,  267,  268,  269,
  270,  271,  266,  267,  268,  269,  270,  271,  272,  279,
  279,  281,  279,  266,  267,  290,  279,  287,  279,  290,
  279,  291,  290,  287,  279,  290,  279,  291,  281,  279,
  290,  279,  290,  279,  287,  279,  290,  279,  291,  266,
  267,  268,  269,  270,  271,  272,  266,  267,  268,  269,
  270,  271,  272,  341,  281,  287,  285,  283,  283,  281,
  287,  281,  281,  281,  285,  282,  279,  287,  266,  267,
  268,  269,  270,  271,  272,  266,  267,  268,  269,  270,
  271,  272,  291,  281,  279,  279,  279,  279,  160,  287,
  281,  279,  279,  149,  414,   63,  287,  266,  267,  268,
  269,  270,  271,  272,  266,  267,  268,  269,  270,  271,
  272,  297,  281,  183,  387,  381,   75,   75,  287,  318,
  319,  320,  321,  322,  323,  324,  325,  326,  327,  328,
  329,  330,  331,  332,  333,  159,  335,  266,  267,  268,
  269,  270,  271,  272,  304,  305,  306,  307,  308,  309,
   14,  298,  281,   -1,  366,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 341
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"L_OR","L_AND","L_NOT","L_EQ",
"L_NEQ","L_LT","L_GT","L_LEQ","L_GEQ","A_PLUS","A_MINUS","A_TIMES","A_DIV",
"A_IDIV","A_MOD","A_EXP","U_MINUS","LEX_ERROR","V_TRUE","V_FALSE","T_EOF",
"T_EOL","T_BAR","T_LPAR","T_RPAR","T_LBRA","T_RBRA","T_LSQB","T_RSQB",
"T_ASSIGN","T_COMMA","T_DOT","T_DOTDOT","T_COLON","T_SEMI","T_PP","T_MM","T_RA",
"K_BEGIN","K_CANCEL","K_DESCRIBE","K_ELSE","K_END","K_IF","K_INCLUDE","K_LIST",
"K_MACRO","K_PRINT","K_QUIT","K_THEN","K_BACKWARD","K_FORWARD","K_LOOP","K_OFF",
"K_ON","K_PALINDROME","K_PAUSE","K_PLAY","K_STEP","K_STOP","K_VCR",
"P_INTERRUPT","P_SYSTEM","P_ACK","P_MACRO","P_FOREGROUND","P_BACKGROUND",
"P_ERROR","P_MESSAGE","P_INFO","P_LINQ","P_SINQ","P_VINQ","P_LRESP","P_SRESP",
"P_VRESP","P_DATA","P_COMPLETE","P_IMPORT","P_IMPORTINFO","T_INT","T_FLOAT",
"T_STRING","T_ID","T_EXID",
};
char *yyrule[] = {
"$accept : start",
"$$1 :",
"start : $$1 top",
"top : statement",
"top : macro",
"top : packet",
"top : vcr",
"top : K_INCLUDE T_STRING",
"top : K_INCLUDE T_ID",
"top : K_QUIT",
"top : T_EOF",
"top : T_EOL",
"top : semicolon",
"vcr : K_VCR statement",
"vcr : K_PAUSE semicolon",
"vcr : K_PLAY semicolon",
"vcr : K_STEP semicolon",
"vcr : K_STOP semicolon",
"vcr : K_FORWARD semicolon",
"vcr : K_BACKWARD semicolon",
"vcr : K_PALINDROME switch semicolon",
"vcr : K_LOOP switch semicolon",
"switch : K_ON",
"switch : K_OFF",
"$$2 :",
"packet : T_BAR int T_BAR P_INTERRUPT T_BAR int $$2 T_BAR interrupt_data T_BAR",
"$$3 :",
"packet : T_BAR int T_BAR P_SYSTEM T_BAR int $$3 T_BAR system_data T_BAR",
"$$4 :",
"packet : T_BAR int T_BAR P_ACK T_BAR int $$4 T_BAR ack_data T_BAR",
"$$5 :",
"packet : T_BAR int T_BAR P_MACRO T_BAR int $$5 T_BAR macro_data T_BAR",
"$$6 :",
"packet : T_BAR int T_BAR P_FOREGROUND T_BAR int $$6 T_BAR foreground_data T_BAR",
"$$7 :",
"packet : T_BAR int T_BAR P_BACKGROUND T_BAR int $$7 T_BAR background_data T_BAR",
"$$8 :",
"packet : T_BAR int T_BAR P_ERROR T_BAR int $$8 T_BAR error_data T_BAR",
"$$9 :",
"packet : T_BAR int T_BAR P_MESSAGE T_BAR int $$9 T_BAR message_data T_BAR",
"$$10 :",
"packet : T_BAR int T_BAR P_INFO T_BAR int $$10 T_BAR info_data T_BAR",
"$$11 :",
"packet : T_BAR int T_BAR P_LINQ T_BAR int $$11 T_BAR l_inquiry_data T_BAR",
"$$12 :",
"packet : T_BAR int T_BAR P_SINQ T_BAR int $$12 T_BAR s_inquiry_data T_BAR",
"$$13 :",
"packet : T_BAR int T_BAR P_VINQ T_BAR int $$13 T_BAR v_inquiry_data T_BAR",
"$$14 :",
"packet : T_BAR int T_BAR P_LRESP T_BAR int $$14 T_BAR l_response_data T_BAR",
"$$15 :",
"packet : T_BAR int T_BAR P_SRESP T_BAR int $$15 T_BAR s_response_data T_BAR",
"$$16 :",
"packet : T_BAR int T_BAR P_VRESP T_BAR int $$16 T_BAR v_response_data T_BAR",
"$$17 :",
"packet : T_BAR int T_BAR P_DATA T_BAR int $$17 T_BAR data_data T_BAR",
"$$18 :",
"packet : T_BAR int T_BAR P_IMPORT T_BAR int $$18 T_BAR import_data T_BAR",
"interrupt_data : int",
"system_data : system_s",
"system_s : system",
"system_s : system_s T_COMMA system",
"system : id T_ASSIGN constant",
"ack_data : message_id T_COLON data",
"macro_data : macro",
"foreground_data : statement",
"foreground_data : vcr",
"background_data : statement",
"background_data : K_CANCEL",
"message_data : data",
"info_data : data",
"l_inquiry_data : handle T_COLON ex_id_s",
"s_inquiry_data : handle T_COLON expression_s",
"s_inquiry_data : handle T_COLON ex_id_s",
"v_inquiry_data : handle T_COLON expression_s",
"v_inquiry_data : handle T_COLON ex_id_s",
"l_response_data : handle T_COLON id_s0",
"s_response_data : handle T_COLON data",
"v_response_data : handle T_COLON s_assignment_0",
"data_data : handle T_COLON s_assignment_0",
"import_data : data",
"macro : K_MACRO id T_LPAR formal_s0 rightparen T_RA T_LPAR id_s0 rightparen attributes_0 block",
"macro : K_MACRO id T_LPAR formal_s0 rightparen attributes_0 block",
"formal_s0 : empty",
"formal_s0 : formal_s",
"formal_s : formal attributes_0",
"formal_s : formal_s T_COMMA formal attributes_0",
"formal : id",
"formal : id T_ASSIGN constant",
"formal : id T_ASSIGN A_MINUS constant",
"block : T_LBRA statement_s0 rightbracket",
"statement_s0 : empty",
"statement_s0 : statement_s",
"statement_s : statement",
"statement_s : statement_s statement",
"statement : block",
"statement : assignment semicolon",
"statement : function_call semicolon",
"assignment : f_assignment",
"assignment : s_assignment",
"f_assignment : id_s T_ASSIGN function_call",
"s_assignment : id_s T_ASSIGN expression_s",
"s_assignment : id T_PP",
"s_assignment : id T_MM",
"s_assignment_0 : empty",
"s_assignment_0 : s_assignment",
"attributes_0 : empty",
"attributes_0 : attributes",
"attributes : T_LSQB attribute_s0 T_RSQB",
"attribute_s0 : empty",
"attribute_s0 : attribute_s",
"attribute_s : attribute",
"attribute_s : attribute_s T_COMMA attribute",
"attribute : id T_COLON constant",
"function_call : id T_LPAR argument_s0 rightparen attributes_0",
"argument_s0 : empty",
"argument_s0 : argument_s",
"argument_s : argument",
"argument_s : argument_s T_COMMA argument",
"argument : value",
"argument : id T_ASSIGN value",
"value : expression",
"expression_s : expression",
"expression_s : expression_s T_COMMA expression",
"expression : constant",
"expression : id",
"expression : T_LPAR expression rightparen",
"expression : arithmetic",
"arithmetic : expression A_EXP expression",
"arithmetic : expression A_TIMES expression",
"arithmetic : expression A_DIV expression",
"arithmetic : expression A_IDIV expression",
"arithmetic : expression A_MOD expression",
"arithmetic : expression A_PLUS expression",
"arithmetic : expression A_MINUS expression",
"arithmetic : A_MINUS expression",
"constant : scalar",
"constant : tensor",
"constant : list",
"constant : string",
"list : T_LBRA scalar_s rightbracket",
"list : T_LBRA tensor_s rightbracket",
"list : T_LBRA string_s rightbracket",
"list : T_LBRA nreal T_DOTDOT nreal rightbracket",
"list : T_LBRA nreal T_DOTDOT nreal T_COLON nreal rightbracket",
"tensor_s : tensor",
"tensor_s : tensor_s tensor",
"tensor_s : A_MINUS tensor",
"tensor_s : tensor_s A_MINUS tensor",
"tensor_s : tensor_s T_COMMA tensor",
"tensor_s : tensor_s T_COMMA A_MINUS tensor",
"tensor : T_LSQB scalar_s T_RSQB",
"tensor : T_LSQB tensor_s T_RSQB",
"scalar_s : scalar",
"scalar_s : scalar_s scalar",
"scalar_s : A_MINUS scalar",
"scalar_s : scalar_s A_MINUS scalar",
"scalar_s : scalar_s T_COMMA scalar",
"scalar_s : scalar_s T_COMMA A_MINUS scalar",
"string_s : string",
"string_s : string_s string",
"string_s : string_s T_COMMA string",
"scalar : real",
"scalar : complex",
"scalar : quaternion",
"nreal : real",
"nreal : A_MINUS real",
"real : int",
"real : float",
"complex : T_LPAR nint T_COMMA nint rightparen",
"complex : T_LPAR nint T_COMMA nfloat rightparen",
"complex : T_LPAR nfloat T_COMMA nint rightparen",
"complex : T_LPAR nfloat T_COMMA nfloat rightparen",
"quaternion : T_LPAR nint T_COMMA nint T_COMMA nint T_COMMA nint rightparen",
"quaternion : T_LPAR nfloat T_COMMA nfloat T_COMMA nfloat T_COMMA nfloat rightparen",
"nint : int",
"nint : A_MINUS int",
"int : T_INT",
"nfloat : float",
"nfloat : A_MINUS float",
"float : T_FLOAT",
"string : T_STRING",
"semicolon : T_SEMI",
"rightparen : T_RPAR",
"rightbracket : T_RBRA",
"id : T_ID",
"ex_id : T_EXID",
"empty :",
"id_s0 : empty",
"id_s0 : id_s",
"id_s : id attributes_0",
"id_s : id_s T_COMMA id attributes_0",
"ex_id_s : ex_id",
"ex_id_s : ex_id_s T_COMMA ex_id",
"message_id : int",
"handle : int",
"error_data :",
"data :",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 1631 "yuiif.y"

int
yyerror (char *s)
{
    static char prevfile[256];
    static int	prevline	= -1;
    int		new_line	= FALSE;
    char	*name;
    char	buf[8192];

    if (s == NULL)
    {
	prevline    = -1;
	prevfile[0] = '\000';
	return;
    }

    if (prevline == -1)
	prevfile[0] = '\000';

    name = fname[*fnum];
    _dxd_exParseError = TRUE;

    /*
     * ALWAYS suppress multiple messages about the same line.
     */

    if (prevline != yylineno || strcmp (prevfile, name))
    {
	strncpy (prevfile, name, 255);
	prevfile[255] = '\000';
	prevline = yylineno;
	yyText[yycharno] = '\000';
	new_line = TRUE;
    }

    /*
     * Send a 1 line message to the UI with column number, actually
     * draw out an arrow when talking directly to the user.
     */


    if (new_line)
    {
	if (! isprint (yyText[yycharno - 1]))
	{
	    sprintf (buf, "%s (non-printable character 0x%x)",
		     s, yyText[yycharno - 1]);
	    s = buf;
	}

	if (_dxd_exRemote)
	{
	    DXUIMessage ("ERROR", "%s[%d,%d]:  %s:  %s",
		       name, yylineno, yycharno, s, yyText);
	}
	else
	{
	    DXUIMessage ("ERROR", "%s[%d]: %s", name, yylineno, s);
	    _dxf_ExLexError ();
	}
    }

    /* in script mode running MP you will get 2 prompts on error
     * unless you flush out the newline after the error.
     */
    if (_dxd_exUIPacket)
	_dxf_ExUIFlushPacket ();
    else if(! _dxd_exRemote)
        _dxf_ExFlushNewLine();
}
#line 1174 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 585 "yuiif.y"
{
		    _dxd_exParseTree  = NULL;
		    _dxd_exParseMesg  = NULL;
		    _dxd_exParseError = FALSE;
		    _dxf_ExLexInit ();
		    _dxf_ExEvaluateConstants (FALSE);
		}
break;
case 2:
#line 593 "yuiif.y"
{
		    if (_dxd_exParseError)
		    {
			_dxd_exParseTree = NULL;
			if (_dxd_exParseMesg != NULL)
			    yyerror (_dxd_exParseMesg);
			YYABORT;
		    }
		    else
		    {
			_dxd_exParseTree = yyvsp[0].n;
			_dxf_ExEvaluateConstants (TRUE);
			YYACCEPT;
		    }
		}
break;
case 7:
#line 615 "yuiif.y"
{
		    _pushInput (yyvsp[0].s);
		    DXFree ((Pointer) yyvsp[0].s);
		    yyval.n = NULL;
		}
break;
case 8:
#line 621 "yuiif.y"
{
                    /* needed to zero out char count here because */
                    /* parser gets a bit confused                 */
                    yycharno = 0;
		    _pushInput (yyvsp[0].s);
		    DXFree ((Pointer) yyvsp[0].s);
		    yyval.n = NULL;
		}
break;
case 9:
#line 630 "yuiif.y"
{
		    *_dxd_exTerminating = TRUE;
		    _dxf_ExVCRCommand (VCR_C_FLAG, VCR_F_LOOP, 0);
		    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
		    yyval.n = NULL;
		}
break;
case 10:
#line 637 "yuiif.y"
{
		    /* if eof on stdin, exit cleanly */
		    if (_popInput ())
		    {
                        /* if we are connected to UI kill running graph */
                        if(_dxd_exRemote) {
                            _dxf_ExExecCommandStr ("kill");
                            _dxf_ExVCRCommand (VCR_C_STOP, 0, 0);
                        }
			*_dxd_exTerminating = TRUE;
			_dxf_ExVCRCommand (VCR_C_FLAG, VCR_F_LOOP, 0);
			_dxf_ExBackgroundCommand (BG_CANCEL, NULL);
		    }
		    yyval.n = NULL;
		}
break;
case 11:
#line 653 "yuiif.y"
{
		    yyval.n = NULL;
		}
break;
case 12:
#line 657 "yuiif.y"
{
		    yyval.n = NULL;
		}
break;
case 13:
#line 663 "yuiif.y"
{
		    _dxf_ExEvaluateConstants (TRUE);
		    _dxf_ExVCRCommand (VCR_C_TREE, (long) yyvsp[0].n, 0);
		    yyval.n = NULL;
		}
break;
case 14:
#line 669 "yuiif.y"
{
		    _dxf_ExExecCommandStr ("kill");
		    _dxf_ExVCRCommand (VCR_C_PAUSE, 0, 0);
#if 0
                   /* let UI handle this, removed 7/20/93 */
		    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
#endif
		    yyval.n = NULL;
		}
break;
case 15:
#line 679 "yuiif.y"
{
		    _dxf_ExVCRCommand (VCR_C_PLAY, 0, 0);
		    yyval.n = NULL;
		}
break;
case 16:
#line 684 "yuiif.y"
{
		    _dxf_ExVCRCommand (VCR_C_STEP, 0, 0);
		    yyval.n = NULL;
		}
break;
case 17:
#line 689 "yuiif.y"
{
		    _dxf_ExExecCommandStr ("kill");
		    _dxf_ExVCRCommand (VCR_C_STOP, 0, 0);
#if 0
                    /* let UI handle this, removed 7/20/93 */
		    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
#endif
		    yyval.n = NULL;
		}
break;
case 18:
#line 699 "yuiif.y"
{
		    _dxf_ExVCRCommand (VCR_C_DIR, VCR_D_FORWARD, 0);
		    yyval.n = NULL;
		}
break;
case 19:
#line 704 "yuiif.y"
{
		    _dxf_ExVCRCommand (VCR_C_DIR, VCR_D_BACKWARD, 0);
		    yyval.n = NULL;
		}
break;
case 20:
#line 709 "yuiif.y"
{
		    _dxf_ExVCRCommand (VCR_C_FLAG, VCR_F_PALIN, yyvsp[-1].i);
		    yyval.n = NULL;
		}
break;
case 21:
#line 714 "yuiif.y"
{
		    _dxf_ExVCRCommand (VCR_C_FLAG, VCR_F_LOOP, yyvsp[-1].i);
		    yyval.n = NULL;
		}
break;
case 22:
#line 721 "yuiif.y"
{
		    yyval.i = TRUE;
		}
break;
case 23:
#line 725 "yuiif.y"
{
		    yyval.i = FALSE;
		}
break;
case 24:
#line 732 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_INTERRUPT, yyvsp[0].i);
	}
break;
case 25:
#line 736 "yuiif.y"
{
	    _dxf_ExExecCommandStr ("kill");
	    _dxf_ExVCRCommand (VCR_C_STOP, 0, 0);
	    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
	    yyval.n = _dxf_ExPCreatePacket (PK_INTERRUPT, yyvsp[-8].i, yyvsp[-4].i, NULL);
	}
break;
case 26:
#line 744 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_SYSTEM, yyvsp[0].i);
	}
break;
case 27:
#line 748 "yuiif.y"
{
	    yyval.n = NULL;
	}
break;
case 28:
#line 753 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_ACK, yyvsp[0].i);
	}
break;
case 29:
#line 757 "yuiif.y"
{
	    yyval.n = NULL;
	}
break;
case 30:
#line 762 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_MACRO, yyvsp[0].i);
	}
break;
case 31:
#line 766 "yuiif.y"
{
	    yyval.n = _dxf_ExPCreatePacket (PK_MACRO, yyvsp[-8].i, yyvsp[-4].i, yyvsp[-1].n);
	}
break;
case 32:
#line 771 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_FOREGROUND, yyvsp[0].i);
	}
break;
case 33:
#line 775 "yuiif.y"
{
	    yyval.n = _dxf_ExPCreatePacket (PK_FOREGROUND, yyvsp[-8].i, yyvsp[-4].i, yyvsp[-1].n);
	}
break;
case 34:
#line 780 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_BACKGROUND, yyvsp[0].i);
	}
break;
case 35:
#line 784 "yuiif.y"
{
	    yyval.n = _dxf_ExPCreatePacket (PK_BACKGROUND, yyvsp[-8].i, yyvsp[-4].i, yyvsp[-1].n);
	}
break;
case 36:
#line 789 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_ERROR, yyvsp[0].i);
	    data_len = yyvsp[0].i;
	}
break;
case 37:
#line 794 "yuiif.y"
{
	    yyval.n = NULL;
	}
break;
case 38:
#line 799 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_MESSAGE, yyvsp[0].i);
	}
break;
case 39:
#line 803 "yuiif.y"
{
	    yyval.n = NULL;
	}
break;
case 40:
#line 808 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_INFO, yyvsp[0].i);
	}
break;
case 41:
#line 812 "yuiif.y"
{
	    yyval.n = NULL;
	}
break;
case 42:
#line 817 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_LINQ, yyvsp[0].i);
	}
break;
case 43:
#line 821 "yuiif.y"
{
	    yyval.n = NULL;
	}
break;
case 44:
#line 826 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_SINQ, yyvsp[0].i);
	}
break;
case 45:
#line 830 "yuiif.y"
{
	    yyval.n = NULL;
	}
break;
case 46:
#line 835 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_VINQ, yyvsp[0].i);
	}
break;
case 47:
#line 839 "yuiif.y"
{
	    yyval.n = NULL;
	}
break;
case 48:
#line 844 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_LRESP, yyvsp[0].i);
	}
break;
case 49:
#line 848 "yuiif.y"
{
	    yyval.n = NULL;
	}
break;
case 50:
#line 853 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_SRESP, yyvsp[0].i);
	}
break;
case 51:
#line 857 "yuiif.y"
{
	    yyval.n = NULL;
	}
break;
case 52:
#line 862 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_VRESP, yyvsp[0].i);
	}
break;
case 53:
#line 866 "yuiif.y"
{
	    yyval.n = NULL;
	}
break;
case 54:
#line 871 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_DATA, yyvsp[0].i);
	}
break;
case 55:
#line 875 "yuiif.y"
{
	    yyval.n = NULL;
	}
break;
case 56:
#line 880 "yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_IMPORT, yyvsp[0].i);
	    data_len = yyvsp[0].i;
	}
break;
case 57:
#line 885 "yuiif.y"
{
	    yyval.n = _dxf_ExPCreatePacket (PK_IMPORT, yyvsp[-8].i, yyvsp[-4].i, yyvsp[-1].n);
	}
break;
case 67:
#line 938 "yuiif.y"
{
		    _dxf_ExBackgroundCommand (BG_STATEMENT, yyvsp[0].n);
		    yyval.n = NULL;
		}
break;
case 68:
#line 943 "yuiif.y"
{
		    _dxf_ExExecCommandStr ("kill");
		    _dxf_ExVCRCommand (VCR_C_STOP, 0, 0);
		    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
		    yyval.n = NULL;
		}
break;
case 81:
#line 1012 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateMacro (yyvsp[-9].n, yyvsp[-7].n, yyvsp[-3].n, yyvsp[0].n);
		    yyval.n->attr = yyvsp[-1].n;
		}
break;
case 82:
#line 1018 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateMacro (yyvsp[-5].n, yyvsp[-3].n, NULL, yyvsp[0].n);
		    yyval.n->attr = yyvsp[-1].n;
		}
break;
case 85:
#line 1029 "yuiif.y"
{
		    yyvsp[-1].n->attr = yyvsp[0].n;
		    LIST_CREATE (yyvsp[-1].n);
		}
break;
case 86:
#line 1034 "yuiif.y"
{
		    yyvsp[-1].n->attr = yyvsp[0].n;
		    LIST_APPEND_CHECK (yyvsp[-3].n, yyvsp[-1].n);
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
break;
case 88:
#line 1044 "yuiif.y"
{
		    yyvsp[-2].n->v.id.dflt = yyvsp[0].n;
		}
break;
case 89:
#line 1048 "yuiif.y"
{
		    yyvsp[-3].n->v.id.dflt = _dxf_ExPNegateConst (yyvsp[0].n);
		}
break;
case 90:
#line 1059 "yuiif.y"
{
		    yyval.n = yyvsp[-1].n;
		}
break;
case 93:
#line 1073 "yuiif.y"
{
		    LIST_CREATE (yyvsp[0].n);
		}
break;
case 94:
#line 1077 "yuiif.y"
{
		    LIST_APPEND_CHECK (yyvsp[-1].n, yyvsp[0].n);
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
break;
case 96:
#line 1090 "yuiif.y"
{
		    LIST_CREATE (yyvsp[-1].n);
		}
break;
case 97:
#line 1094 "yuiif.y"
{
		    LIST_CREATE (yyvsp[-1].n);
		}
break;
case 100:
#line 1109 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateAssign (yyvsp[-2].n, yyvsp[0].n);
		}
break;
case 101:
#line 1115 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateAssign (yyvsp[-2].n, yyvsp[0].n);
		}
break;
case 102:
#line 1119 "yuiif.y"
{
		    node	*mm;
		    int		val = 1;

		    mm = _dxf_ExPCreateConst (TYPE_INT, CATEGORY_REAL,
				       1, (Pointer) &val);
		    mm = _dxf_ExPCreateArith (AO_PLUS, yyvsp[-1].n, mm);
		    EXO_reference ((EXO_Object) yyvsp[-1].n);
		    yyval.n = _dxf_ExPCreateAssign (yyvsp[-1].n, mm);
		}
break;
case 103:
#line 1130 "yuiif.y"
{
		    node	*mm;
		    int		val = 1;

		    mm = _dxf_ExPCreateConst (TYPE_INT, CATEGORY_REAL,
				       1, (Pointer) &val);
		    mm = _dxf_ExPCreateArith (AO_MINUS, yyvsp[-1].n, mm);
		    EXO_reference ((EXO_Object) yyvsp[-1].n);
		    yyval.n = _dxf_ExPCreateAssign (yyvsp[-1].n, mm);
		}
break;
case 108:
#line 1156 "yuiif.y"
{
		    yyval.n = yyvsp[-1].n;
		}
break;
case 111:
#line 1166 "yuiif.y"
{
		    LIST_CREATE (yyvsp[0].n);
		}
break;
case 112:
#line 1170 "yuiif.y"
{
		    LIST_APPEND_CHECK (yyvsp[-2].n, yyvsp[0].n);
		}
break;
case 113:
#line 1176 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateAttribute (yyvsp[-2].n, yyvsp[0].n);
		}
break;
case 114:
#line 1186 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateCall (yyvsp[-4].n, yyvsp[-2].n);
		    yyval.n->attr = yyvsp[0].n;
		}
break;
case 117:
#line 1201 "yuiif.y"
{
		    LIST_CREATE (yyvsp[0].n);
		}
break;
case 118:
#line 1205 "yuiif.y"
{
		    LIST_APPEND_CHECK (yyvsp[-2].n, yyvsp[0].n);
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
break;
case 119:
#line 1213 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArgument (NULL, yyvsp[0].n);
		}
break;
case 120:
#line 1217 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArgument (yyvsp[-2].n, yyvsp[0].n);
		}
break;
case 122:
#line 1230 "yuiif.y"
{
		    LIST_CREATE (yyvsp[0].n);
		}
break;
case 123:
#line 1234 "yuiif.y"
{
		    LIST_APPEND_CHECK (yyvsp[-2].n, yyvsp[0].n);
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
break;
case 126:
#line 1244 "yuiif.y"
{
		    yyval.n = yyvsp[-1].n;
		}
break;
case 128:
#line 1251 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_EXP, yyvsp[-2].n, yyvsp[0].n);
		}
break;
case 129:
#line 1255 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_TIMES, yyvsp[-2].n, yyvsp[0].n);
		}
break;
case 130:
#line 1259 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_DIV, yyvsp[-2].n, yyvsp[0].n);
		}
break;
case 131:
#line 1263 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_IDIV, yyvsp[-2].n, yyvsp[0].n);
		}
break;
case 132:
#line 1267 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_MOD, yyvsp[-2].n, yyvsp[0].n);
		}
break;
case 133:
#line 1271 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_PLUS, yyvsp[-2].n, yyvsp[0].n);
		}
break;
case 134:
#line 1275 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_MINUS, yyvsp[-2].n, yyvsp[0].n);
		}
break;
case 135:
#line 1279 "yuiif.y"
{
		    if (yyvsp[0].n->type == NT_CONSTANT)
			yyval.n = _dxf_ExPNegateConst (yyvsp[0].n);
		    else
			yyval.n = _dxf_ExPCreateArith (AO_NEGATE, yyvsp[0].n, NULL);
		}
break;
case 140:
#line 1298 "yuiif.y"
{
		    yyval.n = yyvsp[-1].n;
		}
break;
case 141:
#line 1302 "yuiif.y"
{
		    yyval.n = yyvsp[-1].n;
		}
break;
case 142:
#line 1306 "yuiif.y"
{
		    yyval.n = yyvsp[-1].n;
		}
break;
case 143:
#line 1310 "yuiif.y"
{
		    yyval.n = _dxf_ExPDotDotList (yyvsp[-3].n, yyvsp[-1].n, NULL);
		    _dxf_ExPDestroyNode (yyvsp[-3].n);
		    _dxf_ExPDestroyNode (yyvsp[-1].n);
		}
break;
case 144:
#line 1316 "yuiif.y"
{
		    yyval.n = _dxf_ExPDotDotList (yyvsp[-5].n, yyvsp[-3].n, yyvsp[-1].n);
		    _dxf_ExPDestroyNode (yyvsp[-5].n);
		    _dxf_ExPDestroyNode (yyvsp[-3].n);
		    _dxf_ExPDestroyNode (yyvsp[-1].n);
		}
break;
case 146:
#line 1326 "yuiif.y"
{
		    yyval.n = _dxf_ExAppendConst (yyvsp[-1].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
break;
case 147:
#line 1331 "yuiif.y"
{
		    yyval.n = _dxf_ExPNegateConst (yyvsp[0].n);
		}
break;
case 148:
#line 1335 "yuiif.y"
{
		    yyvsp[0].n = _dxf_ExPNegateConst (yyvsp[0].n);
		    yyval.n = _dxf_ExAppendConst (yyvsp[-2].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
break;
case 149:
#line 1341 "yuiif.y"
{
		    yyval.n = _dxf_ExAppendConst (yyvsp[-2].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
break;
case 150:
#line 1346 "yuiif.y"
{
		    yyvsp[0].n = _dxf_ExPNegateConst (yyvsp[0].n);
		    yyval.n = _dxf_ExAppendConst (yyvsp[-3].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
break;
case 151:
#line 1354 "yuiif.y"
{
		    yyval.n = _dxf_ExPExtendConst (yyvsp[-1].n);
		}
break;
case 152:
#line 1358 "yuiif.y"
{
		    yyval.n = _dxf_ExPExtendConst (yyvsp[-1].n);
		}
break;
case 154:
#line 1368 "yuiif.y"
{
		    yyval.n = _dxf_ExAppendConst (yyvsp[-1].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
break;
case 155:
#line 1373 "yuiif.y"
{
		    yyval.n = _dxf_ExPNegateConst (yyvsp[0].n);
		}
break;
case 156:
#line 1377 "yuiif.y"
{
		    yyvsp[0].n = _dxf_ExPNegateConst (yyvsp[0].n);
		    yyval.n = _dxf_ExAppendConst (yyvsp[-2].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
break;
case 157:
#line 1383 "yuiif.y"
{
		    yyval.n = _dxf_ExAppendConst (yyvsp[-2].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
break;
case 158:
#line 1388 "yuiif.y"
{
		    yyvsp[0].n = _dxf_ExPNegateConst (yyvsp[0].n);
		    yyval.n = _dxf_ExAppendConst (yyvsp[-3].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
break;
case 160:
#line 1397 "yuiif.y"
{
		    yyval.n = _dxf_ExAppendConst (yyvsp[-1].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
break;
case 161:
#line 1402 "yuiif.y"
{
		    yyval.n = _dxf_ExAppendConst (yyvsp[-2].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
break;
case 166:
#line 1415 "yuiif.y"
{
		    yyval.n = _dxf_ExPNegateConst (yyvsp[0].n);
		}
break;
case 167:
#line 1421 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateConst (TYPE_INT,   CATEGORY_REAL,
					1, (Pointer) &(yyvsp[0].i));
		}
break;
case 168:
#line 1426 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_REAL,
					1, (Pointer) &(yyvsp[0].f));
		}
break;
case 169:
#line 1433 "yuiif.y"
{
		    int		c[2];

		    c[0] = yyvsp[-3].i;
		    c[1] = yyvsp[-1].i;
		    yyval.n = _dxf_ExPCreateConst (TYPE_INT,   CATEGORY_COMPLEX,
					1, (Pointer) c);
		}
break;
case 170:
#line 1442 "yuiif.y"
{
		    float	c[2];

		    c[0] = (float) yyvsp[-3].i;
		    c[1] = yyvsp[-1].f;
		    yyval.n = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_COMPLEX,
					1, (Pointer) c);
		}
break;
case 171:
#line 1451 "yuiif.y"
{
		    float	c[2];

		    c[0] = yyvsp[-3].f;
		    c[1] = (float) yyvsp[-1].i;
		    yyval.n = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_COMPLEX,
					1, (Pointer) c);
		}
break;
case 172:
#line 1460 "yuiif.y"
{
		    float	c[2];

		    c[0] = yyvsp[-3].f;
		    c[1] = yyvsp[-1].f;
		    yyval.n = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_COMPLEX,
					1, (Pointer) c);
		}
break;
case 173:
#line 1471 "yuiif.y"
{
		    int		c[4];

		    c[0] = yyvsp[-7].i;
		    c[1] = yyvsp[-5].i;
		    c[2] = yyvsp[-3].i;
		    c[3] = yyvsp[-1].i;
		    yyval.n = _dxf_ExPCreateConst (TYPE_INT,   CATEGORY_QUATERNION,
				       1, (Pointer) c);
		}
break;
case 174:
#line 1482 "yuiif.y"
{
		    float	c[4];

		    c[0] = yyvsp[-7].f;
		    c[1] = yyvsp[-5].f;
		    c[2] = yyvsp[-3].f;
		    c[3] = yyvsp[-1].f;
		    yyval.n = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_QUATERNION,
				       1, (Pointer) c);
		}
break;
case 176:
#line 1496 "yuiif.y"
{
		    yyval.i = - yyvsp[0].i;
		}
break;
case 179:
#line 1506 "yuiif.y"
{
		    yyval.f = - yyvsp[0].f;
		}
break;
case 181:
#line 1515 "yuiif.y"
{
                    /* should this be TYPE_STRING eventually? */
		    yyval.n = _dxf_ExPCreateConst (TYPE_UBYTE, CATEGORY_REAL,
				       yyLeng + 1, (Pointer) yyvsp[0].s);
		    DXFree ((Pointer) yyvsp[0].s);
		}
break;
case 182:
#line 1525 "yuiif.y"
{
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
break;
case 183:
#line 1531 "yuiif.y"
{
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
break;
case 184:
#line 1537 "yuiif.y"
{
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
break;
case 185:
#line 1543 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateId (yyvsp[0].s);
		}
break;
case 186:
#line 1549 "yuiif.y"
{
		    yyval.n = _dxf_ExPCreateExid (yyvsp[0].s);
		}
break;
case 187:
#line 1555 "yuiif.y"
{
		    yyval.n = NULL;
		}
break;
case 190:
#line 1569 "yuiif.y"
{
		    yyvsp[-1].n->attr = yyvsp[0].n;
		    LIST_CREATE (yyvsp[-1].n);
		}
break;
case 191:
#line 1574 "yuiif.y"
{
		    yyvsp[-1].n->attr = yyvsp[0].n;
		    LIST_APPEND_CHECK (yyvsp[-3].n, yyvsp[-1].n);
		}
break;
case 196:
#line 1594 "yuiif.y"
{
		    Pointer buffer;

		    if (data_len)
		    {
		        buffer = DXAllocate (data_len + 1);
			yygrabdata (buffer, data_len);
			DXUIMessage("ERROR", buffer);
			DXFree(buffer);
		    }
		    else
		    {
			_dxd_exParseError = TRUE;
		    }
		    yyval.n = NULL;
		}
break;
case 197:
#line 1613 "yuiif.y"
{
		    Pointer buffer;

		    buffer = DXAllocate (data_len + 1);
		    if (buffer)
		    {
			yygrabdata (buffer, data_len);
			yyval.n = _dxf_ExPCreateData (buffer, data_len);
		    }
		    else
		    {
			_dxd_exParseError = TRUE;
			yyval.n = NULL;
		    }
		}
break;
#line 2286 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
