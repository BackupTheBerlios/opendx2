/* A Bison parser, made from ./yuiif.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	L_OR	257
# define	L_AND	258
# define	L_NOT	259
# define	L_EQ	260
# define	L_NEQ	261
# define	L_LT	262
# define	L_GT	263
# define	L_LEQ	264
# define	L_GEQ	265
# define	A_PLUS	266
# define	A_MINUS	267
# define	A_TIMES	268
# define	A_DIV	269
# define	A_IDIV	270
# define	A_MOD	271
# define	A_EXP	272
# define	U_MINUS	273
# define	LEX_ERROR	274
# define	V_TRUE	275
# define	V_FALSE	276
# define	T_EOF	277
# define	T_EOL	278
# define	T_BAR	279
# define	T_LPAR	280
# define	T_RPAR	281
# define	T_LBRA	282
# define	T_RBRA	283
# define	T_LSQB	284
# define	T_RSQB	285
# define	T_ASSIGN	286
# define	T_COMMA	287
# define	T_DOT	288
# define	T_DOTDOT	289
# define	T_COLON	290
# define	T_SEMI	291
# define	T_PP	292
# define	T_MM	293
# define	T_RA	294
# define	K_BEGIN	295
# define	K_CANCEL	296
# define	K_DESCRIBE	297
# define	K_ELSE	298
# define	K_END	299
# define	K_IF	300
# define	K_INCLUDE	301
# define	K_LIST	302
# define	K_MACRO	303
# define	K_PRINT	304
# define	K_QUIT	305
# define	K_THEN	306
# define	K_BACKWARD	307
# define	K_FORWARD	308
# define	K_LOOP	309
# define	K_OFF	310
# define	K_ON	311
# define	K_PALINDROME	312
# define	K_PAUSE	313
# define	K_PLAY	314
# define	K_STEP	315
# define	K_STOP	316
# define	K_VCR	317
# define	P_INTERRUPT	318
# define	P_SYSTEM	319
# define	P_ACK	320
# define	P_MACRO	321
# define	P_FOREGROUND	322
# define	P_BACKGROUND	323
# define	P_ERROR	324
# define	P_MESSAGE	325
# define	P_INFO	326
# define	P_LINQ	327
# define	P_SINQ	328
# define	P_VINQ	329
# define	P_LRESP	330
# define	P_SRESP	331
# define	P_VRESP	332
# define	P_DATA	333
# define	P_COMPLETE	334
# define	P_IMPORT	335
# define	P_IMPORTINFO	336
# define	T_INT	337
# define	T_FLOAT	338
# define	T_STRING	339
# define	T_ID	340
# define	T_EXID	341

#line 1 "./yuiif.y"

/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/


#define DXD_ENABLE_SOCKET_POINTERS	/* define SFILE in arch.h, os2 */
#include <dx/dx.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#if defined(HAVE_UNISTD_H)
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
#include "config.h"
#include "parse.h"
#include "vcr.h"
#include "log.h"
#include "background.h"
#include "lex.h"
#include "command.h"

#include "sfile.h"

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

SFILE		*_dxd_exBaseFD = NULL;

int		_dxd_exParseError = 0;
node		*_dxd_exParseTree = NULL;
char		*_dxd_exParseMesg = NULL;

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
_dxf_ExParseInit (char *name, SFILE *sf)
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
    fps[*fnum] = sf;
    yyin = fps[*fnum];
    _dxd_exBaseFD = sf;

    /*
     * can do .rc file processing here.
     * Unlicensed PC's will always load dxrc files here since they don't get "license" message.
     */
    _dxf_ExReadDXRCFiles ();

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

void
_dxf_ExBeginInput()
{
    yyin = fps[*fnum];
    yylineno = linenum[*fnum];
    yycharno = charnum[*fnum];
}

void
_dxf_ExEndInput()
{
    linenum[*fnum] = yylineno;
    charnum[*fnum] = yycharno;
}


static int
_pushInput (char *name)
{
    static int		initme = TRUE;
    static int		npaths = 0;
    static IPath	*ipaths	= NULL;
    int			i;
    int			len;
    SFILE		*sf;
    FILE		*fptr;
    char		buf[4096];

    while (initme)
    {
	char		*tmp1;
	char		*tmp2;
	int		size;

	buf[0] = 0;

	initme = FALSE;

	tmp1 = (char *) getenv ("DXINCLUDE");
        tmp2 = (char *) getenv ("DXMACROS");
	buf[0]='\0';
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
	return ERROR;
    }

    fptr = fopen (name, "r");
    for (i = 0; fptr == NULL && i < npaths; i++)
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
	fptr = fopen (buf, "r");
    }

    if (fptr == NULL && getenv("DXROOT"))
    {
#if  defined(DXD_NON_UNIX_DIR_SEPARATOR)
	sprintf(buf, "%s\\lib\\%s", getenv("DXROOT"), name);
#else
	sprintf(buf, "%s/lib/%s", getenv("DXROOT"), name);
#endif
	fptr = fopen (buf, "r");
    }

    if (fptr != NULL)
    {
        sf = FILEToSFILE(fptr);

	linenum[*fnum] = yylineno;
	charnum[*fnum] = yycharno;
	(*fnum)++;
	linenum[*fnum] = 1;
	charnum[*fnum] = 0;
	strncpy (fname[*fnum], name, 128);
	fname[*fnum][127] = '\0';
	fps[*fnum] = sf;
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

    return OK;
}

static char PopMessage[] = "< INCLUDED FILE > ";

static int
_popInput()
{
    char	*cp;
    char	*mp;
    int		i;

    yyerror (NULL);		/* reset error file name and line number */

    if (*fnum > 0)
    {
	closeSFILE(yyin);
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


#line 419 "./yuiif.y"
#ifndef YYSTYPE
typedef union
{
    char		c;
    int			i;
    float		f;
    char		*s;
    void		*v;
    node		*n;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		418
#define	YYFLAG		-32768
#define	YYNTBASE	88

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 341 ? yytranslate[x] : 183)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     6,     8,    10,    12,    15,    18,
      20,    22,    24,    26,    29,    32,    35,    38,    41,    44,
      47,    51,    55,    57,    59,    60,    71,    72,    83,    84,
      95,    96,   107,   108,   119,   120,   131,   132,   143,   144,
     155,   156,   167,   168,   179,   180,   191,   192,   203,   204,
     215,   216,   227,   228,   239,   240,   251,   252,   263,   265,
     267,   269,   273,   277,   281,   283,   285,   287,   289,   291,
     293,   295,   299,   303,   307,   311,   315,   319,   323,   327,
     331,   333,   345,   353,   355,   357,   360,   365,   367,   371,
     376,   380,   382,   384,   386,   389,   391,   394,   397,   399,
     401,   405,   409,   412,   415,   417,   419,   421,   423,   427,
     429,   431,   433,   437,   441,   447,   449,   451,   453,   457,
     459,   463,   465,   467,   471,   473,   475,   479,   481,   485,
     489,   493,   497,   501,   505,   509,   512,   514,   516,   518,
     520,   524,   528,   532,   538,   546,   548,   551,   554,   558,
     562,   567,   571,   575,   577,   580,   583,   587,   591,   596,
     598,   601,   605,   607,   609,   611,   613,   616,   618,   620,
     626,   632,   638,   644,   654,   664,   666,   669,   671,   673,
     676,   678,   680,   682,   684,   686,   688,   690,   691,   693,
     695,   698,   703,   705,   709,   711,   713,   714
};
static const short yyrhs[] =
{
      -1,    89,    90,     0,   136,     0,   129,     0,    93,     0,
      91,     0,    47,    85,     0,    47,    86,     0,    51,     0,
      23,     0,    24,     0,   170,     0,    63,   136,     0,    59,
     170,     0,    60,   170,     0,    61,   170,     0,    62,   170,
       0,    54,   170,     0,    53,   170,     0,    58,    92,   170,
       0,    55,    92,   170,     0,    57,     0,    56,     0,     0,
      25,   166,    25,    64,    25,   166,    94,    25,   111,    25,
       0,     0,    25,   166,    25,    65,    25,   166,    95,    25,
     112,    25,     0,     0,    25,   166,    25,    66,    25,   166,
      96,    25,   115,    25,     0,     0,    25,   166,    25,    67,
      25,   166,    97,    25,   116,    25,     0,     0,    25,   166,
      25,    68,    25,   166,    98,    25,   117,    25,     0,     0,
      25,   166,    25,    69,    25,   166,    99,    25,   118,    25,
       0,     0,    25,   166,    25,    70,    25,   166,   100,    25,
     181,    25,     0,     0,    25,   166,    25,    71,    25,   166,
     101,    25,   119,    25,     0,     0,    25,   166,    25,    72,
      25,   166,   102,    25,   120,    25,     0,     0,    25,   166,
      25,    73,    25,   166,   103,    25,   121,    25,     0,     0,
      25,   166,    25,    74,    25,   166,   104,    25,   122,    25,
       0,     0,    25,   166,    25,    75,    25,   166,   105,    25,
     123,    25,     0,     0,    25,   166,    25,    76,    25,   166,
     106,    25,   124,    25,     0,     0,    25,   166,    25,    77,
      25,   166,   107,    25,   125,    25,     0,     0,    25,   166,
      25,    78,    25,   166,   108,    25,   126,    25,     0,     0,
      25,   166,    25,    79,    25,   166,   109,    25,   127,    25,
       0,     0,    25,   166,    25,    81,    25,   166,   110,    25,
     128,    25,     0,   166,     0,   113,     0,   114,     0,   113,
      33,   114,     0,   173,    32,   154,     0,   179,    36,   182,
       0,   129,     0,   136,     0,    91,     0,   136,     0,    42,
       0,   182,     0,   182,     0,   180,    36,   178,     0,   180,
      36,   151,     0,   180,    36,   178,     0,   180,    36,   151,
       0,   180,    36,   178,     0,   180,    36,   176,     0,   180,
      36,   182,     0,   180,    36,   140,     0,   180,    36,   140,
       0,   182,     0,    49,   173,    26,   130,   171,    40,    26,
     176,   171,   141,   133,     0,    49,   173,    26,   130,   171,
     141,   133,     0,   175,     0,   131,     0,   132,   141,     0,
     131,    33,   132,   141,     0,   173,     0,   173,    32,   154,
       0,   173,    32,    13,   154,     0,    28,   134,   172,     0,
     175,     0,   135,     0,   136,     0,   135,   136,     0,   133,
       0,   137,   170,     0,   146,   170,     0,   138,     0,   139,
       0,   177,    32,   146,     0,   177,    32,   151,     0,   173,
      38,     0,   173,    39,     0,   175,     0,   139,     0,   175,
       0,   142,     0,    30,   143,    31,     0,   175,     0,   144,
       0,   145,     0,   144,    33,   145,     0,   173,    36,   154,
       0,   173,    26,   147,   171,   141,     0,   175,     0,   148,
       0,   149,     0,   148,    33,   149,     0,   150,     0,   173,
      32,   150,     0,   152,     0,   152,     0,   151,    33,   152,
       0,   154,     0,   173,     0,    26,   152,   171,     0,   153,
       0,   152,    18,   152,     0,   152,    14,   152,     0,   152,
      15,   152,     0,   152,    16,   152,     0,   152,    17,   152,
       0,   152,    12,   152,     0,   152,    13,   152,     0,    13,
     152,     0,   160,     0,   157,     0,   155,     0,   169,     0,
      28,   158,   172,     0,    28,   156,   172,     0,    28,   159,
     172,     0,    28,   161,    35,   161,   172,     0,    28,   161,
      35,   161,    36,   161,   172,     0,   157,     0,   156,   157,
       0,    13,   157,     0,   156,    13,   157,     0,   156,    33,
     157,     0,   156,    33,    13,   157,     0,    30,   158,    31,
       0,    30,   156,    31,     0,   160,     0,   158,   160,     0,
      13,   160,     0,   158,    13,   160,     0,   158,    33,   160,
       0,   158,    33,    13,   160,     0,   169,     0,   159,   169,
       0,   159,    33,   169,     0,   162,     0,   163,     0,   164,
       0,   162,     0,    13,   162,     0,   166,     0,   168,     0,
      26,   165,    33,   165,   171,     0,    26,   165,    33,   167,
     171,     0,    26,   167,    33,   165,   171,     0,    26,   167,
      33,   167,   171,     0,    26,   165,    33,   165,    33,   165,
      33,   165,   171,     0,    26,   167,    33,   167,    33,   167,
      33,   167,   171,     0,   166,     0,    13,   166,     0,    83,
       0,   168,     0,    13,   168,     0,    84,     0,    85,     0,
      37,     0,    27,     0,    29,     0,    86,     0,    87,     0,
       0,   175,     0,   177,     0,   173,   141,     0,   177,    33,
     173,   141,     0,   174,     0,   178,    33,   174,     0,   166,
       0,   166,     0,     0,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   610,   610,   636,   637,   638,   639,   640,   646,   655,
     662,   678,   682,   688,   694,   704,   709,   714,   724,   729,
     734,   739,   746,   750,   757,   757,   769,   769,   778,   778,
     787,   787,   796,   796,   805,   805,   814,   814,   824,   824,
     833,   833,   842,   842,   851,   851,   860,   860,   869,   869,
     878,   878,   887,   887,   896,   896,   905,   905,   920,   927,
     930,   931,   934,   941,   948,   955,   956,   963,   968,   981,
     988,   995,   998,   999,  1002,  1003,  1010,  1013,  1016,  1023,
    1026,  1035,  1042,  1050,  1051,  1054,  1059,  1068,  1069,  1073,
    1084,  1094,  1095,  1098,  1102,  1114,  1115,  1119,  1130,  1131,
    1134,  1140,  1144,  1155,  1168,  1169,  1177,  1178,  1181,  1187,
    1188,  1191,  1195,  1201,  1211,  1222,  1223,  1226,  1230,  1238,
    1242,  1248,  1255,  1259,  1267,  1268,  1269,  1273,  1276,  1280,
    1284,  1288,  1292,  1296,  1300,  1304,  1317,  1318,  1319,  1320,
    1323,  1327,  1331,  1335,  1341,  1350,  1351,  1356,  1360,  1366,
    1371,  1379,  1383,  1392,  1393,  1398,  1402,  1408,  1413,  1421,
    1422,  1427,  1434,  1435,  1436,  1439,  1440,  1446,  1451,  1458,
    1467,  1476,  1485,  1496,  1507,  1520,  1521,  1527,  1530,  1531,
    1537,  1540,  1550,  1557,  1564,  1571,  1577,  1583,  1593,  1594,
    1597,  1602,  1609,  1610,  1613,  1616,  1622,  1641
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "L_OR", "L_AND", "L_NOT", "L_EQ", "L_NEQ", 
  "L_LT", "L_GT", "L_LEQ", "L_GEQ", "A_PLUS", "A_MINUS", "A_TIMES", 
  "A_DIV", "A_IDIV", "A_MOD", "A_EXP", "U_MINUS", "LEX_ERROR", "V_TRUE", 
  "V_FALSE", "T_EOF", "T_EOL", "T_BAR", "T_LPAR", "T_RPAR", "T_LBRA", 
  "T_RBRA", "T_LSQB", "T_RSQB", "T_ASSIGN", "T_COMMA", "T_DOT", 
  "T_DOTDOT", "T_COLON", "T_SEMI", "T_PP", "T_MM", "T_RA", "K_BEGIN", 
  "K_CANCEL", "K_DESCRIBE", "K_ELSE", "K_END", "K_IF", "K_INCLUDE", 
  "K_LIST", "K_MACRO", "K_PRINT", "K_QUIT", "K_THEN", "K_BACKWARD", 
  "K_FORWARD", "K_LOOP", "K_OFF", "K_ON", "K_PALINDROME", "K_PAUSE", 
  "K_PLAY", "K_STEP", "K_STOP", "K_VCR", "P_INTERRUPT", "P_SYSTEM", 
  "P_ACK", "P_MACRO", "P_FOREGROUND", "P_BACKGROUND", "P_ERROR", 
  "P_MESSAGE", "P_INFO", "P_LINQ", "P_SINQ", "P_VINQ", "P_LRESP", 
  "P_SRESP", "P_VRESP", "P_DATA", "P_COMPLETE", "P_IMPORT", 
  "P_IMPORTINFO", "T_INT", "T_FLOAT", "T_STRING", "T_ID", "T_EXID", 
  "start", "@1", "top", "vcr", "switch", "packet", "@2", "@3", "@4", "@5", 
  "@6", "@7", "@8", "@9", "@10", "@11", "@12", "@13", "@14", "@15", "@16", 
  "@17", "@18", "interrupt_data", "system_data", "system_s", "system", 
  "ack_data", "macro_data", "foreground_data", "background_data", 
  "message_data", "info_data", "l_inquiry_data", "s_inquiry_data", 
  "v_inquiry_data", "l_response_data", "s_response_data", 
  "v_response_data", "data_data", "import_data", "macro", "formal_s0", 
  "formal_s", "formal", "block", "statement_s0", "statement_s", 
  "statement", "assignment", "f_assignment", "s_assignment", 
  "s_assignment_0", "attributes_0", "attributes", "attribute_s0", 
  "attribute_s", "attribute", "function_call", "argument_s0", 
  "argument_s", "argument", "value", "expression_s", "expression", 
  "arithmetic", "constant", "list", "tensor_s", "tensor", "scalar_s", 
  "string_s", "scalar", "nreal", "real", "complex", "quaternion", "nint", 
  "int", "nfloat", "float", "string", "semicolon", "rightparen", 
  "rightbracket", "id", "ex_id", "empty", "id_s0", "id_s", "ex_id_s", 
  "message_id", "handle", "error_data", "data", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    89,    88,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    92,    92,    94,    93,    95,    93,    96,    93,
      97,    93,    98,    93,    99,    93,   100,    93,   101,    93,
     102,    93,   103,    93,   104,    93,   105,    93,   106,    93,
     107,    93,   108,    93,   109,    93,   110,    93,   111,   112,
     113,   113,   114,   115,   116,   117,   117,   118,   118,   119,
     120,   121,   122,   122,   123,   123,   124,   125,   126,   127,
     128,   129,   129,   130,   130,   131,   131,   132,   132,   132,
     133,   134,   134,   135,   135,   136,   136,   136,   137,   137,
     138,   139,   139,   139,   140,   140,   141,   141,   142,   143,
     143,   144,   144,   145,   146,   147,   147,   148,   148,   149,
     149,   150,   151,   151,   152,   152,   152,   152,   153,   153,
     153,   153,   153,   153,   153,   153,   154,   154,   154,   154,
     155,   155,   155,   155,   155,   156,   156,   156,   156,   156,
     156,   157,   157,   158,   158,   158,   158,   158,   158,   159,
     159,   159,   160,   160,   160,   161,   161,   162,   162,   163,
     163,   163,   163,   164,   164,   165,   165,   166,   167,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   176,
     177,   177,   178,   178,   179,   180,   181,   182
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     1,     1,     1,     1,     2,     2,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       3,     3,     1,     1,     0,    10,     0,    10,     0,    10,
       0,    10,     0,    10,     0,    10,     0,    10,     0,    10,
       0,    10,     0,    10,     0,    10,     0,    10,     0,    10,
       0,    10,     0,    10,     0,    10,     0,    10,     1,     1,
       1,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,    11,     7,     1,     1,     2,     4,     1,     3,     4,
       3,     1,     1,     1,     2,     1,     2,     2,     1,     1,
       3,     3,     2,     2,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     3,     5,     1,     1,     1,     3,     1,
       3,     1,     1,     3,     1,     1,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     1,
       3,     3,     3,     5,     7,     1,     2,     2,     3,     3,
       4,     3,     3,     1,     2,     2,     3,     3,     4,     1,
       2,     3,     1,     1,     1,     1,     2,     1,     1,     5,
       5,     5,     5,     9,     9,     1,     2,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       2,     4,     1,     3,     1,     1,     0,     0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,    10,    11,     0,   187,   182,     0,     0,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   185,
       2,     6,     5,     4,    95,     3,     0,    98,    99,     0,
      12,   187,     0,   177,     0,     0,    92,    93,    91,     7,
       8,     0,    19,    18,    23,    22,     0,     0,    14,    15,
      16,    17,    13,    96,    97,   187,   187,   102,   103,   190,
     107,   106,     0,     0,     0,   184,    90,    94,   187,    21,
      20,     0,     0,     0,     0,   180,   181,     0,   116,   117,
     119,   121,   127,   124,   138,   137,   136,   162,   163,   164,
     167,   168,   139,   125,   115,     0,   110,   111,     0,   109,
     100,   101,   122,   125,   187,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    84,   187,    87,    83,   135,   125,     0,
       0,     0,   167,     0,   168,     0,     0,     0,   145,     0,
       0,   153,     0,   162,   159,     0,     0,     0,   183,   187,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,     0,     0,   191,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   187,     0,    85,     0,   167,   168,   126,     0,     0,
     147,   155,   162,     0,   175,   178,     0,     0,   146,   141,
       0,     0,   154,   140,     0,   160,   142,     0,   152,   151,
     114,   118,   133,   134,   129,   130,   131,   132,   128,   120,
     112,   113,   123,    24,    26,    28,    30,    32,    34,    36,
      38,    40,    42,    44,    46,    48,    50,    52,    54,    56,
       0,     0,   187,     0,    88,     0,     0,     0,     0,   176,
     179,   148,     0,   149,   156,     0,   157,   161,     0,     0,
     165,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   187,    82,
      86,    89,     0,   169,   170,   171,     0,   172,   150,   158,
     166,     0,   143,     0,     0,     0,     0,     0,     0,   196,
     197,   197,     0,     0,     0,     0,     0,     0,     0,   197,
     187,   188,     0,   189,     0,     0,     0,     0,     0,     0,
      58,     0,    59,    60,     0,     0,   194,     0,     0,    64,
      66,     0,    65,    68,     0,    67,     0,     0,    69,     0,
      70,     0,   195,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    80,   187,     0,
       0,   144,    25,    27,     0,     0,    29,   197,    31,    33,
      35,    37,    39,    41,    43,     0,    45,     0,    47,     0,
      49,   187,    51,   197,    53,   187,    55,   187,    57,     0,
       0,     0,    61,    62,    63,   186,   192,    71,    72,    73,
      74,    75,    76,    77,   105,    78,   187,   104,     0,    79,
      81,   173,   174,     0,     0,   193,     0,     0,     0
};

static const short yydefgoto[] =
{
     416,     1,    20,    21,    46,    22,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   319,   321,   322,   323,   325,   328,   331,
     334,   337,   339,   341,   344,   346,   348,   350,   352,   354,
     356,    23,   122,   123,   124,    24,    35,    36,    25,    26,
      27,    28,   405,    59,    60,    95,    96,    97,    29,    77,
      78,    79,    80,   101,   102,    82,    83,    84,   137,    85,
     139,   140,    86,   142,    87,    88,    89,   131,    90,   133,
      91,    92,    30,   149,    66,   128,   396,    61,   312,    32,
     397,   327,   343,   336,   338
};

static const short yypact[] =
{
  -32768,   306,-32768,-32768,   -63,    -7,-32768,    45,   -40,-32768,
      32,    32,    27,    27,    32,    32,    32,    32,    -7,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,    32,-32768,-32768,    32,
  -32768,   237,   120,-32768,    33,    36,    -7,-32768,-32768,-32768,
  -32768,    68,-32768,-32768,-32768,-32768,    32,    32,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,   203,   -40,-32768,-32768,-32768,
  -32768,-32768,   203,   -40,   343,-32768,-32768,-32768,   -40,-32768,
  -32768,   203,   219,    40,   226,-32768,-32768,    70,    86,-32768,
  -32768,   424,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,   107,-32768,   136,   169,-32768,   168,-32768,
  -32768,   173,   424,   183,   187,   194,   195,   197,   202,   205,
     213,   215,   216,   217,   218,   221,   229,   239,   240,   265,
     266,   267,    70,   190,   187,   212,-32768,-32768,-32768,   203,
     417,   247,   273,   278,   280,   152,    28,   315,-32768,   224,
      52,-32768,   263,   285,-32768,   152,    26,   235,-32768,   187,
     203,   203,   203,   203,   203,   203,   203,   203,   203,-32768,
     -40,   232,   203,-32768,   -63,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,
     -63,    -2,   -40,-32768,    73,   299,   304,-32768,    28,    28,
  -32768,-32768,   303,    78,-32768,-32768,   270,    96,-32768,-32768,
      61,    34,-32768,-32768,   166,-32768,-32768,    58,-32768,-32768,
  -32768,-32768,   255,   255,   328,   328,   328,   328,-32768,-32768,
  -32768,-32768,   424,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
     321,   322,   187,   232,-32768,    80,    70,    70,   127,-32768,
  -32768,-32768,   270,-32768,-32768,    61,-32768,-32768,    78,   -17,
  -32768,   324,   327,   331,   333,   337,   348,   349,   350,   351,
     354,   357,   360,   362,   363,   364,   365,   366,   -40,-32768,
  -32768,-32768,    17,-32768,-32768,-32768,    21,-32768,-32768,-32768,
  -32768,    58,-32768,   -63,   -40,   -63,   344,   342,    35,-32768,
  -32768,-32768,   -63,   -63,   -63,   -63,   -63,   -63,   -63,-32768,
     187,-32768,    70,   361,   -63,   373,   314,   390,    36,   374,
  -32768,   400,   393,-32768,   395,   418,-32768,   415,   427,-32768,
  -32768,   428,-32768,-32768,   429,-32768,   430,   431,-32768,   432,
  -32768,   433,-32768,   423,   435,   425,   437,   434,   438,   436,
     439,   440,   441,   442,   443,   444,   446,-32768,   187,    17,
      21,-32768,-32768,-32768,   -40,   232,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,   378,-32768,   198,-32768,   198,
  -32768,   -40,-32768,-32768,-32768,   -40,-32768,   -40,-32768,   322,
      70,    70,-32768,-32768,-32768,-32768,-32768,   448,   173,   448,
     173,   448,-32768,-32768,-32768,-32768,    10,-32768,   181,-32768,
  -32768,-32768,-32768,   378,   203,-32768,   467,   469,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,   176,   461,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   111,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   186,-32768,-32768,   295,  -238,-32768,-32768,    -3,-32768,
  -32768,  -313,    92,   -99,-32768,-32768,-32768,   323,   422,-32768,
  -32768,   335,   329,  -284,    18,-32768,  -155,-32768,   412,   -31,
     414,-32768,   -37,  -199,   -57,-32768,-32768,  -144,    19,  -157,
     -61,   -64,   325,  -112,  -113,    -1,    76,    -4,   109,  -265,
    -200,-32768,   142,-32768,  -287
};


#define	YYLAST		490


static const short yytable[] =
{
      31,    38,    37,   279,    31,   163,   221,    41,   259,   144,
     181,   134,    65,   313,   340,    52,   143,    31,   187,   291,
      33,     5,   357,    34,   199,   183,   203,   206,    56,   244,
     314,   246,   248,    67,   316,    31,   141,   141,   240,   196,
      56,   193,   138,   138,   245,   247,    19,   255,    57,    58,
     210,    94,    99,   135,    93,    98,    74,   208,    64,   197,
     136,   103,   104,     5,   126,    65,   136,   125,   186,     6,
      74,   258,   404,    81,   404,   195,   205,   333,   192,    19,
     394,    65,   241,    44,    45,   204,   243,   136,   281,   127,
     130,   132,   318,   398,    68,   400,   403,   148,   191,   136,
      33,    73,   202,    74,   190,    75,   198,   148,   191,   252,
     202,    33,    75,   282,   190,   198,   313,    33,    75,   150,
     408,    19,   408,    33,    75,    76,    74,   195,   195,   317,
      39,    40,   250,   283,   284,   285,   287,    76,   315,   158,
     257,    33,    75,   280,    33,    75,   292,   127,   185,    93,
     260,   410,    62,    63,   148,   194,    33,    75,    76,    98,
     286,    33,    75,   254,   256,   251,   253,   159,    81,   212,
     213,   214,   215,   216,   217,   218,    81,   399,   136,   401,
     222,   125,    74,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     358,   290,   160,   391,   161,   361,   162,   194,   194,    55,
     393,    71,   249,   414,    63,   390,    71,    56,   289,   164,
     165,   288,   166,   182,    72,   195,    73,   167,    74,    72,
     168,    73,   129,    74,   260,    33,    75,   200,   169,   145,
     170,   171,   172,   173,   184,    72,   174,    73,   200,    74,
     136,    76,   136,    65,   175,   250,    74,   201,   136,   389,
      73,   136,    74,    55,   176,   177,   209,    56,   201,   153,
     154,   155,   156,   157,   311,    57,    58,   310,   411,   412,
     188,    33,    75,    76,    19,   395,    33,    75,    76,    19,
     178,   179,   180,   324,   332,   335,    31,    31,   207,   195,
      74,   194,    33,    75,    76,    19,  -175,    33,    75,    33,
      75,   189,   320,  -178,   326,    33,    75,    76,    33,    75,
    -165,   342,   342,   342,   342,   342,   342,   342,   196,     2,
       3,     4,  -176,   249,     5,    42,    43,  -179,  -166,    48,
      49,    50,    51,     6,    65,    74,   157,   278,   197,   293,
       5,    53,   294,     7,    54,     8,   295,     9,   296,    10,
      11,    12,   297,   324,    13,    14,    15,    16,    17,    18,
       5,    69,    70,   298,   299,   300,   301,   311,   194,   302,
     310,   407,   303,   407,   406,   304,   406,   305,   306,   307,
     308,   309,    19,     8,    63,    10,    11,    12,    75,   362,
      13,    14,    15,    16,    17,    18,   359,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   360,   121,   363,   364,   365,    19,   151,
     152,   153,   154,   155,   156,   157,   151,   152,   153,   154,
     155,   156,   157,   366,   148,   345,   347,   349,   351,   353,
     355,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   380,   382,   395,   384,   417,   386,   418,
     379,   388,   381,   330,    47,   392,   383,   242,   385,   409,
     387,   413,   329,   220,   100,   211,   146,   219,   147,   415,
     402
};

static const short yycheck[] =
{
       1,     5,     5,   241,     5,   104,   161,     8,   207,    73,
     122,    72,    29,   278,   301,    18,    73,    18,   130,    36,
      83,    28,   309,     4,   137,   124,   139,   140,    30,   184,
      13,   188,   189,    36,    13,    36,    73,    74,    40,    13,
      30,    13,    73,    74,   188,   189,    86,    13,    38,    39,
     149,    55,    56,    13,    55,    56,    30,    31,    25,    33,
      26,    62,    63,    28,    68,    29,    26,    68,   129,    37,
      30,    13,   385,    55,   387,   136,   140,    42,   135,    86,
     367,    29,   181,    56,    57,    33,    13,    26,   243,    71,
      72,    72,   291,   377,    26,   379,   383,    27,   135,    26,
      83,    28,   139,    30,   135,    84,   137,    27,   145,    13,
     147,    83,    84,    33,   145,   146,   381,    83,    84,    33,
     385,    86,   387,    83,    84,    85,    30,   188,   189,   286,
      85,    86,   193,   245,   246,   247,   248,    85,   282,    32,
     204,    83,    84,   242,    83,    84,   259,   129,   129,   150,
     207,   389,    32,    33,    27,   136,    83,    84,    85,   160,
      33,    83,    84,   200,   201,   196,   197,    31,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   377,    26,   379,
     162,   182,    30,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     312,   258,    33,   360,    36,   318,    33,   188,   189,    26,
     365,    13,   193,    32,    33,   359,    13,    30,   255,    25,
      25,   252,    25,    33,    26,   286,    28,    25,    30,    26,
      25,    28,    13,    30,   291,    83,    84,    13,    25,    13,
      25,    25,    25,    25,    32,    26,    25,    28,    13,    30,
      26,    85,    26,    29,    25,   316,    30,    33,    26,   358,
      28,    26,    30,    26,    25,    25,    31,    30,    33,    14,
      15,    16,    17,    18,   278,    38,    39,   278,   390,   391,
      33,    83,    84,    85,    86,    87,    83,    84,    85,    86,
      25,    25,    25,   294,   297,   298,   297,   298,    35,   360,
      30,   282,    83,    84,    85,    86,    33,    83,    84,    83,
      84,    33,   293,    33,   295,    83,    84,    85,    83,    84,
      35,   302,   303,   304,   305,   306,   307,   308,    13,    23,
      24,    25,    33,   314,    28,    10,    11,    33,    35,    14,
      15,    16,    17,    37,    29,    30,    18,    26,    33,    25,
      28,    26,    25,    47,    29,    49,    25,    51,    25,    53,
      54,    55,    25,   364,    58,    59,    60,    61,    62,    63,
      28,    46,    47,    25,    25,    25,    25,   381,   359,    25,
     381,   385,    25,   387,   385,    25,   387,    25,    25,    25,
      25,    25,    86,    49,    33,    53,    54,    55,    84,    25,
      58,    59,    60,    61,    62,    63,    33,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    33,    81,    25,    33,    32,    86,    12,
      13,    14,    15,    16,    17,    18,    12,    13,    14,    15,
      16,    17,    18,    25,    27,   303,   304,   305,   306,   307,
     308,    36,    25,    25,    25,    25,    25,    25,    25,    36,
      25,    36,    25,    25,    25,    87,    25,     0,    25,     0,
      36,    25,    36,   297,    13,   364,    36,   182,    36,   387,
      36,    33,   296,   160,    62,   150,    74,   158,    74,   413,
     381
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/local/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 611 "./yuiif.y"
{
		    _dxd_exParseTree  = NULL;
		    _dxd_exParseMesg  = NULL;
		    _dxd_exParseError = FALSE;
		    _dxf_ExLexInit ();
		    _dxf_ExEvaluateConstants (FALSE);
		}
    break;
case 2:
#line 619 "./yuiif.y"
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
#line 641 "./yuiif.y"
{
		    _pushInput (yyvsp[0].s);
		    DXFree ((Pointer) yyvsp[0].s);
		    yyval.n = NULL;
		}
    break;
case 8:
#line 647 "./yuiif.y"
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
#line 656 "./yuiif.y"
{
		    *_dxd_exTerminating = TRUE;
		    _dxf_ExVCRCommand (VCR_C_FLAG, VCR_F_LOOP, 0);
		    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
		    yyval.n = NULL;
		}
    break;
case 10:
#line 663 "./yuiif.y"
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
#line 679 "./yuiif.y"
{
		    yyval.n = NULL;
		}
    break;
case 12:
#line 683 "./yuiif.y"
{
		    yyval.n = NULL;
		}
    break;
case 13:
#line 689 "./yuiif.y"
{
		    _dxf_ExEvaluateConstants (TRUE);
		    _dxf_ExVCRCommand (VCR_C_TREE, (long) yyvsp[0].n, 0);
		    yyval.n = NULL;
		}
    break;
case 14:
#line 695 "./yuiif.y"
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
#line 705 "./yuiif.y"
{
		    _dxf_ExVCRCommand (VCR_C_PLAY, 0, 0);
		    yyval.n = NULL;
		}
    break;
case 16:
#line 710 "./yuiif.y"
{
		    _dxf_ExVCRCommand (VCR_C_STEP, 0, 0);
		    yyval.n = NULL;
		}
    break;
case 17:
#line 715 "./yuiif.y"
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
#line 725 "./yuiif.y"
{
		    _dxf_ExVCRCommand (VCR_C_DIR, VCR_D_FORWARD, 0);
		    yyval.n = NULL;
		}
    break;
case 19:
#line 730 "./yuiif.y"
{
		    _dxf_ExVCRCommand (VCR_C_DIR, VCR_D_BACKWARD, 0);
		    yyval.n = NULL;
		}
    break;
case 20:
#line 735 "./yuiif.y"
{
		    _dxf_ExVCRCommand (VCR_C_FLAG, VCR_F_PALIN, yyvsp[-1].i);
		    yyval.n = NULL;
		}
    break;
case 21:
#line 740 "./yuiif.y"
{
		    _dxf_ExVCRCommand (VCR_C_FLAG, VCR_F_LOOP, yyvsp[-1].i);
		    yyval.n = NULL;
		}
    break;
case 22:
#line 747 "./yuiif.y"
{
		    yyval.i = TRUE;
		}
    break;
case 23:
#line 751 "./yuiif.y"
{
		    yyval.i = FALSE;
		}
    break;
case 24:
#line 758 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_INTERRUPT, yyvsp[0].i);
	}
    break;
case 25:
#line 762 "./yuiif.y"
{
	    _dxf_ExExecCommandStr ("kill");
	    _dxf_ExVCRCommand (VCR_C_STOP, 0, 0);
	    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
	    yyval.n = _dxf_ExPCreatePacket (PK_INTERRUPT, yyvsp[-8].i, yyvsp[-4].i, NULL);
	}
    break;
case 26:
#line 770 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_SYSTEM, yyvsp[0].i);
	}
    break;
case 27:
#line 774 "./yuiif.y"
{
	    yyval.n = NULL;
	}
    break;
case 28:
#line 779 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_ACK, yyvsp[0].i);
	}
    break;
case 29:
#line 783 "./yuiif.y"
{
	    yyval.n = NULL;
	}
    break;
case 30:
#line 788 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_MACRO, yyvsp[0].i);
	}
    break;
case 31:
#line 792 "./yuiif.y"
{
	    yyval.n = _dxf_ExPCreatePacket (PK_MACRO, yyvsp[-8].i, yyvsp[-4].i, yyvsp[-1].n);
	}
    break;
case 32:
#line 797 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_FOREGROUND, yyvsp[0].i);
	}
    break;
case 33:
#line 801 "./yuiif.y"
{
	    yyval.n = _dxf_ExPCreatePacket (PK_FOREGROUND, yyvsp[-8].i, yyvsp[-4].i, yyvsp[-1].n);
	}
    break;
case 34:
#line 806 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_BACKGROUND, yyvsp[0].i);
	}
    break;
case 35:
#line 810 "./yuiif.y"
{
	    yyval.n = _dxf_ExPCreatePacket (PK_BACKGROUND, yyvsp[-8].i, yyvsp[-4].i, yyvsp[-1].n);
	}
    break;
case 36:
#line 815 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_ERROR, yyvsp[0].i);
	    data_len = yyvsp[0].i;
	}
    break;
case 37:
#line 820 "./yuiif.y"
{
	    yyval.n = NULL;
	}
    break;
case 38:
#line 825 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_MESSAGE, yyvsp[0].i);
	}
    break;
case 39:
#line 829 "./yuiif.y"
{
	    yyval.n = NULL;
	}
    break;
case 40:
#line 834 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_INFO, yyvsp[0].i);
	}
    break;
case 41:
#line 838 "./yuiif.y"
{
	    yyval.n = NULL;
	}
    break;
case 42:
#line 843 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_LINQ, yyvsp[0].i);
	}
    break;
case 43:
#line 847 "./yuiif.y"
{
	    yyval.n = NULL;
	}
    break;
case 44:
#line 852 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_SINQ, yyvsp[0].i);
	}
    break;
case 45:
#line 856 "./yuiif.y"
{
	    yyval.n = NULL;
	}
    break;
case 46:
#line 861 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_VINQ, yyvsp[0].i);
	}
    break;
case 47:
#line 865 "./yuiif.y"
{
	    yyval.n = NULL;
	}
    break;
case 48:
#line 870 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_LRESP, yyvsp[0].i);
	}
    break;
case 49:
#line 874 "./yuiif.y"
{
	    yyval.n = NULL;
	}
    break;
case 50:
#line 879 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_SRESP, yyvsp[0].i);
	}
    break;
case 51:
#line 883 "./yuiif.y"
{
	    yyval.n = NULL;
	}
    break;
case 52:
#line 888 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_VRESP, yyvsp[0].i);
	}
    break;
case 53:
#line 892 "./yuiif.y"
{
	    yyval.n = NULL;
	}
    break;
case 54:
#line 897 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_DATA, yyvsp[0].i);
	}
    break;
case 55:
#line 901 "./yuiif.y"
{
	    yyval.n = NULL;
	}
    break;
case 56:
#line 906 "./yuiif.y"
{
	    _dxf_ExUIPacketActive (yyvsp[-4].i, PK_IMPORT, yyvsp[0].i);
	    data_len = yyvsp[0].i;
	}
    break;
case 57:
#line 911 "./yuiif.y"
{
	    yyval.n = _dxf_ExPCreatePacket (PK_IMPORT, yyvsp[-8].i, yyvsp[-4].i, yyvsp[-1].n);
	}
    break;
case 67:
#line 964 "./yuiif.y"
{
		    _dxf_ExBackgroundCommand (BG_STATEMENT, yyvsp[0].n);
		    yyval.n = NULL;
		}
    break;
case 68:
#line 969 "./yuiif.y"
{
		    _dxf_ExExecCommandStr ("kill");
		    _dxf_ExVCRCommand (VCR_C_STOP, 0, 0);
		    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
		    yyval.n = NULL;
		}
    break;
case 81:
#line 1038 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateMacro (yyvsp[-9].n, yyvsp[-7].n, yyvsp[-3].n, yyvsp[0].n);
		    yyval.n->attr = yyvsp[-1].n;
		}
    break;
case 82:
#line 1044 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateMacro (yyvsp[-5].n, yyvsp[-3].n, NULL, yyvsp[0].n);
		    yyval.n->attr = yyvsp[-1].n;
		}
    break;
case 85:
#line 1055 "./yuiif.y"
{
		    yyvsp[-1].n->attr = yyvsp[0].n;
		    LIST_CREATE (yyvsp[-1].n);
		}
    break;
case 86:
#line 1060 "./yuiif.y"
{
		    yyvsp[-1].n->attr = yyvsp[0].n;
		    LIST_APPEND_CHECK (yyvsp[-3].n, yyvsp[-1].n);
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
    break;
case 88:
#line 1070 "./yuiif.y"
{
		    yyvsp[-2].n->v.id.dflt = yyvsp[0].n;
		}
    break;
case 89:
#line 1074 "./yuiif.y"
{
		    yyvsp[-3].n->v.id.dflt = _dxf_ExPNegateConst (yyvsp[0].n);
		}
    break;
case 90:
#line 1085 "./yuiif.y"
{
		    yyval.n = yyvsp[-1].n;
		}
    break;
case 93:
#line 1099 "./yuiif.y"
{
		    LIST_CREATE (yyvsp[0].n);
		}
    break;
case 94:
#line 1103 "./yuiif.y"
{
		    LIST_APPEND_CHECK (yyvsp[-1].n, yyvsp[0].n);
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
    break;
case 96:
#line 1116 "./yuiif.y"
{
		    LIST_CREATE (yyvsp[-1].n);
		}
    break;
case 97:
#line 1120 "./yuiif.y"
{
		    LIST_CREATE (yyvsp[-1].n);
		}
    break;
case 100:
#line 1135 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateAssign (yyvsp[-2].n, yyvsp[0].n);
		}
    break;
case 101:
#line 1141 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateAssign (yyvsp[-2].n, yyvsp[0].n);
		}
    break;
case 102:
#line 1145 "./yuiif.y"
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
#line 1156 "./yuiif.y"
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
#line 1182 "./yuiif.y"
{
		    yyval.n = yyvsp[-1].n;
		}
    break;
case 111:
#line 1192 "./yuiif.y"
{
		    LIST_CREATE (yyvsp[0].n);
		}
    break;
case 112:
#line 1196 "./yuiif.y"
{
		    LIST_APPEND_CHECK (yyvsp[-2].n, yyvsp[0].n);
		}
    break;
case 113:
#line 1202 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateAttribute (yyvsp[-2].n, yyvsp[0].n);
		}
    break;
case 114:
#line 1212 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateCall (yyvsp[-4].n, yyvsp[-2].n);
		    yyval.n->attr = yyvsp[0].n;
		}
    break;
case 117:
#line 1227 "./yuiif.y"
{
		    LIST_CREATE (yyvsp[0].n);
		}
    break;
case 118:
#line 1231 "./yuiif.y"
{
		    LIST_APPEND_CHECK (yyvsp[-2].n, yyvsp[0].n);
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
    break;
case 119:
#line 1239 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArgument (NULL, yyvsp[0].n);
		}
    break;
case 120:
#line 1243 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArgument (yyvsp[-2].n, yyvsp[0].n);
		}
    break;
case 122:
#line 1256 "./yuiif.y"
{
		    LIST_CREATE (yyvsp[0].n);
		}
    break;
case 123:
#line 1260 "./yuiif.y"
{
		    LIST_APPEND_CHECK (yyvsp[-2].n, yyvsp[0].n);
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
    break;
case 126:
#line 1270 "./yuiif.y"
{
		    yyval.n = yyvsp[-1].n;
		}
    break;
case 128:
#line 1277 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_EXP, yyvsp[-2].n, yyvsp[0].n);
		}
    break;
case 129:
#line 1281 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_TIMES, yyvsp[-2].n, yyvsp[0].n);
		}
    break;
case 130:
#line 1285 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_DIV, yyvsp[-2].n, yyvsp[0].n);
		}
    break;
case 131:
#line 1289 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_IDIV, yyvsp[-2].n, yyvsp[0].n);
		}
    break;
case 132:
#line 1293 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_MOD, yyvsp[-2].n, yyvsp[0].n);
		}
    break;
case 133:
#line 1297 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_PLUS, yyvsp[-2].n, yyvsp[0].n);
		}
    break;
case 134:
#line 1301 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateArith (AO_MINUS, yyvsp[-2].n, yyvsp[0].n);
		}
    break;
case 135:
#line 1305 "./yuiif.y"
{
		    if (yyvsp[0].n->type == NT_CONSTANT)
			yyval.n = _dxf_ExPNegateConst (yyvsp[0].n);
		    else
			yyval.n = _dxf_ExPCreateArith (AO_NEGATE, yyvsp[0].n, NULL);
		}
    break;
case 140:
#line 1324 "./yuiif.y"
{
		    yyval.n = yyvsp[-1].n;
		}
    break;
case 141:
#line 1328 "./yuiif.y"
{
		    yyval.n = yyvsp[-1].n;
		}
    break;
case 142:
#line 1332 "./yuiif.y"
{
		    yyval.n = yyvsp[-1].n;
		}
    break;
case 143:
#line 1336 "./yuiif.y"
{
		    yyval.n = _dxf_ExPDotDotList (yyvsp[-3].n, yyvsp[-1].n, NULL);
		    _dxf_ExPDestroyNode (yyvsp[-3].n);
		    _dxf_ExPDestroyNode (yyvsp[-1].n);
		}
    break;
case 144:
#line 1342 "./yuiif.y"
{
		    yyval.n = _dxf_ExPDotDotList (yyvsp[-5].n, yyvsp[-3].n, yyvsp[-1].n);
		    _dxf_ExPDestroyNode (yyvsp[-5].n);
		    _dxf_ExPDestroyNode (yyvsp[-3].n);
		    _dxf_ExPDestroyNode (yyvsp[-1].n);
		}
    break;
case 146:
#line 1352 "./yuiif.y"
{
		    yyval.n = _dxf_ExAppendConst (yyvsp[-1].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
    break;
case 147:
#line 1357 "./yuiif.y"
{
		    yyval.n = _dxf_ExPNegateConst (yyvsp[0].n);
		}
    break;
case 148:
#line 1361 "./yuiif.y"
{
		    yyvsp[0].n = _dxf_ExPNegateConst (yyvsp[0].n);
		    yyval.n = _dxf_ExAppendConst (yyvsp[-2].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
    break;
case 149:
#line 1367 "./yuiif.y"
{
		    yyval.n = _dxf_ExAppendConst (yyvsp[-2].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
    break;
case 150:
#line 1372 "./yuiif.y"
{
		    yyvsp[0].n = _dxf_ExPNegateConst (yyvsp[0].n);
		    yyval.n = _dxf_ExAppendConst (yyvsp[-3].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
    break;
case 151:
#line 1380 "./yuiif.y"
{
		    yyval.n = _dxf_ExPExtendConst (yyvsp[-1].n);
		}
    break;
case 152:
#line 1384 "./yuiif.y"
{
		    yyval.n = _dxf_ExPExtendConst (yyvsp[-1].n);
		}
    break;
case 154:
#line 1394 "./yuiif.y"
{
		    yyval.n = _dxf_ExAppendConst (yyvsp[-1].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
    break;
case 155:
#line 1399 "./yuiif.y"
{
		    yyval.n = _dxf_ExPNegateConst (yyvsp[0].n);
		}
    break;
case 156:
#line 1403 "./yuiif.y"
{
		    yyvsp[0].n = _dxf_ExPNegateConst (yyvsp[0].n);
		    yyval.n = _dxf_ExAppendConst (yyvsp[-2].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
    break;
case 157:
#line 1409 "./yuiif.y"
{
		    yyval.n = _dxf_ExAppendConst (yyvsp[-2].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
    break;
case 158:
#line 1414 "./yuiif.y"
{
		    yyvsp[0].n = _dxf_ExPNegateConst (yyvsp[0].n);
		    yyval.n = _dxf_ExAppendConst (yyvsp[-3].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
    break;
case 160:
#line 1423 "./yuiif.y"
{
		    yyval.n = _dxf_ExAppendConst (yyvsp[-1].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
    break;
case 161:
#line 1428 "./yuiif.y"
{
		    yyval.n = _dxf_ExAppendConst (yyvsp[-2].n, yyvsp[0].n);
		    _dxf_ExPDestroyNode (yyvsp[0].n);
		}
    break;
case 166:
#line 1441 "./yuiif.y"
{
		    yyval.n = _dxf_ExPNegateConst (yyvsp[0].n);
		}
    break;
case 167:
#line 1447 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateConst (TYPE_INT,   CATEGORY_REAL,
					1, (Pointer) &(yyvsp[0].i));
		}
    break;
case 168:
#line 1452 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_REAL,
					1, (Pointer) &(yyvsp[0].f));
		}
    break;
case 169:
#line 1459 "./yuiif.y"
{
		    int		c[2];

		    c[0] = yyvsp[-3].i;
		    c[1] = yyvsp[-1].i;
		    yyval.n = _dxf_ExPCreateConst (TYPE_INT,   CATEGORY_COMPLEX,
					1, (Pointer) c);
		}
    break;
case 170:
#line 1468 "./yuiif.y"
{
		    float	c[2];

		    c[0] = (float) yyvsp[-3].i;
		    c[1] = yyvsp[-1].f;
		    yyval.n = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_COMPLEX,
					1, (Pointer) c);
		}
    break;
case 171:
#line 1477 "./yuiif.y"
{
		    float	c[2];

		    c[0] = yyvsp[-3].f;
		    c[1] = (float) yyvsp[-1].i;
		    yyval.n = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_COMPLEX,
					1, (Pointer) c);
		}
    break;
case 172:
#line 1486 "./yuiif.y"
{
		    float	c[2];

		    c[0] = yyvsp[-3].f;
		    c[1] = yyvsp[-1].f;
		    yyval.n = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_COMPLEX,
					1, (Pointer) c);
		}
    break;
case 173:
#line 1497 "./yuiif.y"
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
#line 1508 "./yuiif.y"
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
#line 1522 "./yuiif.y"
{
		    yyval.i = - yyvsp[0].i;
		}
    break;
case 179:
#line 1532 "./yuiif.y"
{
		    yyval.f = - yyvsp[0].f;
		}
    break;
case 181:
#line 1541 "./yuiif.y"
{
                    /* should this be TYPE_STRING eventually? */
		    yyval.n = _dxf_ExPCreateConst (TYPE_UBYTE, CATEGORY_REAL,
				       yyLeng + 1, (Pointer) yyvsp[0].s);
		    DXFree ((Pointer) yyvsp[0].s);
		}
    break;
case 182:
#line 1551 "./yuiif.y"
{
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
    break;
case 183:
#line 1558 "./yuiif.y"
{
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
    break;
case 184:
#line 1565 "./yuiif.y"
{
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
    break;
case 185:
#line 1572 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateId (yyvsp[0].s);
		}
    break;
case 186:
#line 1578 "./yuiif.y"
{
		    yyval.n = _dxf_ExPCreateExid (yyvsp[0].s);
		}
    break;
case 187:
#line 1584 "./yuiif.y"
{
		    yyval.n = NULL;
		}
    break;
case 190:
#line 1598 "./yuiif.y"
{
		    yyvsp[-1].n->attr = yyvsp[0].n;
		    LIST_CREATE (yyvsp[-1].n);
		}
    break;
case 191:
#line 1603 "./yuiif.y"
{
		    yyvsp[-1].n->attr = yyvsp[0].n;
		    LIST_APPEND_CHECK (yyvsp[-3].n, yyvsp[-1].n);
		}
    break;
case 196:
#line 1623 "./yuiif.y"
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
#line 1642 "./yuiif.y"
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
}

#line 705 "/usr/local/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 1659 "./yuiif.y"


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
	return ERROR;
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

    return ERROR;
}
