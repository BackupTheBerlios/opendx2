#ifndef lint
static char _dxfccsccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define _CCBYACC 1
#define _CCMAJOR 1
#define _CCMINOR 9
#define _dxfccclearin (_dxfccchar=(-1))
#define _dxfccerrok (_dxfccerrflag=0)
#define _CCRECOVERING (_dxfccerrflag!=0)
#define _CCPREFIX "_dxfcc"
#line 13 "_compparse.y"
#include <math.h>
#include <string.h>
#include <dx/dx.h>
#include "_compute.h"
#include "_compputils.h"



int _dxdparseError = 0;		/* Only shared with _compputils.c */
PTreeNode * _dxfMakeFunCall(char *func, PTreeNode *args);


#line 29 "_compparse.y"
typedef union {
#define MAX_PARSE_STRING_SIZE 512
    char s[MAX_PARSE_STRING_SIZE];
    int i;
    float f;
    double d;
    PTreeNode *a;
} _CCSTYPE;
#line 34 "y.tab.c"
#define T_NAME 257
#define T_FLOAT 258
#define T_DOUBLE 259
#define T_INT 260
#define T_INPUT 261
#define T_ID 262
#define T_STRING 263
#define T_EOF 264
#define T_LPAR 265
#define T_RPAR 266
#define T_LBRA 267
#define T_RBRA 268
#define T_LSQB 269
#define T_RSQB 270
#define T_COMMA 271
#define T_PERIOD 272
#define T_COLON 273
#define T_LOR 274
#define T_LAND 275
#define T_LNOT 276
#define T_LT 277
#define T_LE 278
#define T_GT 279
#define T_GE 280
#define T_EQ 281
#define T_NE 282
#define T_QUEST 283
#define T_CROSS 284
#define T_DOT 285
#define T_PLUS 286
#define T_MINUS 287
#define T_EXP 288
#define T_TIMES 289
#define T_DIV 290
#define T_MOD 291
#define T_ASSIGN 292
#define T_SEMI 293
#define U_MINUS 294
#define U_PLUS 295
#define U_LNOT 296
#define _CCERRCODE 256
short _dxfcclhs[] = {                                        -1,
    8,    0,    2,    2,    2,    2,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    6,    6,
    7,    7,    5,    5,    3,    4,    4,    4,    4,
};
short _dxfcclen[] = {                                         2,
    0,    3,    1,    2,    3,    2,    1,    3,    3,    1,
    3,    3,    4,    4,    4,    4,    5,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    2,    2,    2,    3,    1,    0,    1,
    1,    3,    1,    3,    1,    1,    1,    1,    1,
};
short _dxfccdefred[] = {                                      1,
    0,    0,    0,   47,   48,   46,    7,   49,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   10,
   45,    0,    0,    0,    0,    0,   36,    0,    0,   35,
   34,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    2,    0,    0,    0,    0,    0,   11,   12,    0,
    0,    0,    0,    9,    8,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   13,    0,    0,   16,   15,   14,    0,
    0,    0,
};
short _dxfccdgoto[] = {                                       1,
   54,   19,   20,   21,   26,   55,   56,    2,
};
short _dxfccsindex[] = {                                      0,
    0, -195, -238,    0,    0,    0,    0,    0, -158, -158,
 -158, -260, -247, -158, -158, -242, -195,  286, -263,    0,
    0, -158, -158,  246,  286, -199,    0, -158, -158,    0,
    0, -158, -283,  247, -158, -158, -158, -158, -158, -158,
 -158, -158, -158, -158, -158, -158, -158, -158, -158, -158,
 -158,    0, -158,  286, -211, -243,  286,    0,    0, -158,
 -193, -191, -188,    0,    0,  306,  326,  355,  355,  355,
  355,  346,  346,  266,  375, -266,  366,  366, -205, -268,
 -268, -268,  286,    0, -158,  286,    0,    0,    0, -158,
  286,  286,
};
short _dxfccrindex[] = {                                      0,
    0,    0, -134,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -262,    0,    0,
    0, -184,    0,    0, -194,    0,    0, -184, -184,    0,
    0, -184, -178,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -261, -255,    0, -179, -151,    0,    0,    0,
    0,    0,    0,    0,    0,  218, -214,  106,  127,  148,
  169,  190,  204,    0,   34,  -78,   58,   82, -106,  -50,
  -22,    6, -240,    0,    0, -186,    0,    0,    0,    0,
 -252,  229,
};
short _dxfccgindex[] = {                                      0,
   -2,   63,   59,    0,    0,   -3,    0,    0,
};
#define _CCTABLESIZE 666
short _dxfcctable[] = {                                      18,
   52,    3,    6,   34,   28,   34,   24,   25,   27,   53,
   41,   30,   31,   42,   18,   41,   45,   29,   42,   48,
   57,   48,   32,    5,   61,   62,   22,   85,   63,   53,
    3,    6,   66,   67,   68,   69,   70,   71,   72,   73,
   74,   75,   76,   77,   78,   79,   80,   81,   82,   18,
   83,   18,    5,   23,   84,   18,   18,   86,   18,   18,
   18,    3,    4,    5,    6,    7,   34,    8,   18,    9,
   59,   60,   87,   10,   88,   43,   43,   89,   18,   33,
   11,   39,   91,   44,   44,    4,   40,   92,   12,   13,
   14,   15,   65,    0,    0,   16,    0,   17,    3,    4,
    5,    6,    7,    0,    8,    0,    9,    0,    0,    0,
   10,    0,   37,    0,   37,    0,    0,   11,   37,   37,
    0,   37,    0,    0,    0,   12,   13,   14,   15,   38,
    0,   38,   16,    0,    0,   38,   38,   38,   38,   38,
   38,   37,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   38,   38,   38,   38,   38,   38,   33,   38,   33,
    0,    0,    0,   33,   33,    0,   33,   33,   33,    0,
   33,   33,   33,   33,   33,   33,   33,   33,   33,   33,
   33,   33,   33,   33,   33,   31,   33,   31,    0,    0,
    0,   31,   31,    0,   31,   31,   31,    0,   31,   31,
   31,   31,   31,   31,   31,   31,   31,   31,   31,    0,
   31,   31,   31,   28,   31,   28,    0,    0,    0,   28,
   28,    0,   28,   28,   28,    0,   28,   28,   28,   28,
   28,   28,   28,   28,    0,   28,   28,    0,   28,   28,
   28,   29,   28,   29,    0,    0,    0,   29,   29,    0,
   29,   29,   29,    0,   29,   29,   29,   29,   29,   29,
   29,   29,    0,   29,   29,    0,   29,   29,   29,   30,
   29,   30,    0,    0,    0,   30,   30,    0,   30,   30,
   30,    0,   30,   30,   30,   30,   30,   30,   30,   30,
    0,   30,   30,    0,   30,   30,   30,   32,   30,   32,
    0,    0,    0,   32,   32,    0,   32,   32,   32,    0,
   32,   32,   32,   32,   32,   32,   32,   32,    0,   32,
   32,   26,    0,   26,    0,    0,   32,   26,   26,    0,
   26,   26,   26,    0,   26,   26,   26,   26,   26,   26,
   26,    0,    0,   26,   26,   27,    0,   27,    0,    0,
   26,   27,   27,    0,   27,   27,   27,    0,   27,   27,
   27,   27,   27,   27,   27,    0,    0,   27,   27,   22,
    0,   22,    0,    0,   27,   22,   22,    0,   22,   22,
   22,    0,   22,   22,   22,   22,   22,   22,   22,    0,
   23,    0,   23,    0,    0,    0,   23,   23,   22,   23,
   23,   23,    0,   23,   23,   23,   23,   23,   23,   23,
    0,   20,    0,   20,    0,    0,    0,   20,   20,   23,
   20,   20,   20,    0,   20,   20,   20,   20,   20,   20,
   20,    0,   21,    0,   21,    0,    0,    0,   21,   21,
   20,   21,   21,   21,    0,   21,   21,   21,   21,   21,
   21,   21,    0,   24,    0,   24,    0,    0,    0,   24,
   24,   21,   24,   24,   24,    0,    0,   25,    0,   25,
   24,   24,   24,   25,   25,    0,   25,   25,   25,    0,
    0,   19,   24,   19,   25,   25,   25,   19,   19,    0,
   19,   19,   17,    0,   17,    0,   25,    0,   17,   17,
   19,   17,    0,   64,    4,    5,    6,    0,    0,    8,
   19,   58,    0,    0,    0,    0,    0,   34,    0,   35,
   36,   17,   37,   38,   39,   40,   41,   42,   43,   44,
   45,   46,   47,   48,   49,   50,   51,   34,   90,   35,
   36,    0,   37,   38,   39,   40,   41,   42,   43,   44,
   45,   46,   47,   48,   49,   50,   51,   34,    0,   35,
   36,    0,   37,   38,   39,   40,   41,   42,   43,   44,
   45,   46,   47,   48,   49,   50,   51,   34,    0,    0,
   36,    0,   37,   38,   39,   40,   41,   42,    0,   44,
   45,   46,   47,   48,   49,   50,   51,   34,    0,    0,
    0,    0,   37,   38,   39,   40,   41,   42,    0,   44,
   45,   46,   47,   48,   49,   50,   51,   34,    0,    0,
    0,    0,   37,   38,   39,   40,   34,    0,    0,   44,
   45,   46,   47,   48,   49,   50,   51,   34,   44,   45,
   46,   47,   48,   49,   50,   51,   34,    0,    0,   44,
   45,    0,    0,   48,   49,   50,   51,    0,    0,   45,
    0,    0,   48,   49,   50,   51,
};
short _dxfcccheck[] = {                                       2,
  264,  264,  264,  272,  265,  272,    9,   10,   11,  293,
  266,   14,   15,  266,   17,  271,  285,  265,  271,  288,
   23,  288,  265,  264,   28,   29,  265,  271,   32,  293,
  293,  293,   35,   36,   37,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,   51,  264,
   53,  266,  293,  292,  266,  270,  271,   60,  273,  274,
  275,  257,  258,  259,  260,  261,  272,  263,  283,  265,
  270,  271,  266,  269,  266,  270,  271,  266,  293,   17,
  276,  266,   85,  270,  271,  264,  266,   90,  284,  285,
  286,  287,   34,   -1,   -1,  291,   -1,  293,  257,  258,
  259,  260,  261,   -1,  263,   -1,  265,   -1,   -1,   -1,
  269,   -1,  264,   -1,  266,   -1,   -1,  276,  270,  271,
   -1,  273,   -1,   -1,   -1,  284,  285,  286,  287,  264,
   -1,  266,  291,   -1,   -1,  270,  271,  272,  273,  274,
  275,  293,  277,  278,  279,  280,  281,  282,  283,  284,
  285,  286,  287,  288,  289,  290,  291,  264,  293,  266,
   -1,   -1,   -1,  270,  271,   -1,  273,  274,  275,   -1,
  277,  278,  279,  280,  281,  282,  283,  284,  285,  286,
  287,  288,  289,  290,  291,  264,  293,  266,   -1,   -1,
   -1,  270,  271,   -1,  273,  274,  275,   -1,  277,  278,
  279,  280,  281,  282,  283,  284,  285,  286,  287,   -1,
  289,  290,  291,  264,  293,  266,   -1,   -1,   -1,  270,
  271,   -1,  273,  274,  275,   -1,  277,  278,  279,  280,
  281,  282,  283,  284,   -1,  286,  287,   -1,  289,  290,
  291,  264,  293,  266,   -1,   -1,   -1,  270,  271,   -1,
  273,  274,  275,   -1,  277,  278,  279,  280,  281,  282,
  283,  284,   -1,  286,  287,   -1,  289,  290,  291,  264,
  293,  266,   -1,   -1,   -1,  270,  271,   -1,  273,  274,
  275,   -1,  277,  278,  279,  280,  281,  282,  283,  284,
   -1,  286,  287,   -1,  289,  290,  291,  264,  293,  266,
   -1,   -1,   -1,  270,  271,   -1,  273,  274,  275,   -1,
  277,  278,  279,  280,  281,  282,  283,  284,   -1,  286,
  287,  264,   -1,  266,   -1,   -1,  293,  270,  271,   -1,
  273,  274,  275,   -1,  277,  278,  279,  280,  281,  282,
  283,   -1,   -1,  286,  287,  264,   -1,  266,   -1,   -1,
  293,  270,  271,   -1,  273,  274,  275,   -1,  277,  278,
  279,  280,  281,  282,  283,   -1,   -1,  286,  287,  264,
   -1,  266,   -1,   -1,  293,  270,  271,   -1,  273,  274,
  275,   -1,  277,  278,  279,  280,  281,  282,  283,   -1,
  264,   -1,  266,   -1,   -1,   -1,  270,  271,  293,  273,
  274,  275,   -1,  277,  278,  279,  280,  281,  282,  283,
   -1,  264,   -1,  266,   -1,   -1,   -1,  270,  271,  293,
  273,  274,  275,   -1,  277,  278,  279,  280,  281,  282,
  283,   -1,  264,   -1,  266,   -1,   -1,   -1,  270,  271,
  293,  273,  274,  275,   -1,  277,  278,  279,  280,  281,
  282,  283,   -1,  264,   -1,  266,   -1,   -1,   -1,  270,
  271,  293,  273,  274,  275,   -1,   -1,  264,   -1,  266,
  281,  282,  283,  270,  271,   -1,  273,  274,  275,   -1,
   -1,  264,  293,  266,  281,  282,  283,  270,  271,   -1,
  273,  274,  264,   -1,  266,   -1,  293,   -1,  270,  271,
  283,  273,   -1,  257,  258,  259,  260,   -1,   -1,  263,
  293,  266,   -1,   -1,   -1,   -1,   -1,  272,   -1,  274,
  275,  293,  277,  278,  279,  280,  281,  282,  283,  284,
  285,  286,  287,  288,  289,  290,  291,  272,  273,  274,
  275,   -1,  277,  278,  279,  280,  281,  282,  283,  284,
  285,  286,  287,  288,  289,  290,  291,  272,   -1,  274,
  275,   -1,  277,  278,  279,  280,  281,  282,  283,  284,
  285,  286,  287,  288,  289,  290,  291,  272,   -1,   -1,
  275,   -1,  277,  278,  279,  280,  281,  282,   -1,  284,
  285,  286,  287,  288,  289,  290,  291,  272,   -1,   -1,
   -1,   -1,  277,  278,  279,  280,  281,  282,   -1,  284,
  285,  286,  287,  288,  289,  290,  291,  272,   -1,   -1,
   -1,   -1,  277,  278,  279,  280,  272,   -1,   -1,  284,
  285,  286,  287,  288,  289,  290,  291,  272,  284,  285,
  286,  287,  288,  289,  290,  291,  272,   -1,   -1,  284,
  285,   -1,   -1,  288,  289,  290,  291,   -1,   -1,  285,
   -1,   -1,  288,  289,  290,  291,
};
#define _CCFINAL 1
#ifndef _CCDEBUG
#define _CCDEBUG 0
#endif
#define _CCMAXTOKEN 296
#if _CCDEBUG
char *_dxfccname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"T_NAME","T_FLOAT","T_DOUBLE",
"T_INT","T_INPUT","T_ID","T_STRING","T_EOF","T_LPAR","T_RPAR","T_LBRA","T_RBRA",
"T_LSQB","T_RSQB","T_COMMA","T_PERIOD","T_COLON","T_LOR","T_LAND","T_LNOT",
"T_LT","T_LE","T_GT","T_GE","T_EQ","T_NE","T_QUEST","T_CROSS","T_DOT","T_PLUS",
"T_MINUS","T_EXP","T_TIMES","T_DIV","T_MOD","T_ASSIGN","T_SEMI","U_MINUS",
"U_PLUS","U_LNOT",
};
char *_dxfccrule[] = {
"$accept : top",
"$$1 :",
"top : $$1 statement_list T_EOF",
"statement_list : expr",
"statement_list : T_SEMI statement_list",
"statement_list : statement_list T_SEMI expr",
"statement_list : statement_list T_SEMI",
"expr : T_INPUT",
"expr : expr T_PERIOD constant",
"expr : expr T_PERIOD T_NAME",
"expr : constant",
"expr : T_LPAR expr T_RPAR",
"expr : T_LSQB list T_RSQB",
"expr : T_NAME T_LPAR optional_argument_list T_RPAR",
"expr : T_MOD T_LPAR optional_argument_list T_RPAR",
"expr : T_DOT T_LPAR optional_argument_list T_RPAR",
"expr : T_CROSS T_LPAR optional_argument_list T_RPAR",
"expr : expr T_QUEST expr T_COLON expr",
"expr : expr T_LAND expr",
"expr : expr T_LOR expr",
"expr : expr T_GT expr",
"expr : expr T_GE expr",
"expr : expr T_LT expr",
"expr : expr T_LE expr",
"expr : expr T_EQ expr",
"expr : expr T_NE expr",
"expr : expr T_PLUS expr",
"expr : expr T_MINUS expr",
"expr : expr T_TIMES expr",
"expr : expr T_DIV expr",
"expr : expr T_MOD expr",
"expr : expr T_DOT expr",
"expr : expr T_CROSS expr",
"expr : expr T_EXP expr",
"expr : T_MINUS expr",
"expr : T_PLUS expr",
"expr : T_LNOT expr",
"expr : T_NAME T_ASSIGN expr",
"expr : T_NAME",
"optional_argument_list :",
"optional_argument_list : argument_list",
"argument_list : expr",
"argument_list : argument_list T_COMMA expr",
"list : expr",
"list : list T_COMMA expr",
"constant : real",
"real : T_INT",
"real : T_FLOAT",
"real : T_DOUBLE",
"real : T_STRING",
};
#endif
#ifdef _CCSTACKSIZE
#undef _CCMAXDEPTH
#define _CCMAXDEPTH _CCSTACKSIZE
#else
#ifdef _CCMAXDEPTH
#define _CCSTACKSIZE _CCMAXDEPTH
#else
#define _CCSTACKSIZE 500
#define _CCMAXDEPTH 500
#endif
#endif
int _dxfccdebug;
int _dxfccnerrs;
int _dxfccerrflag;
int _dxfccchar;
short *_dxfccssp;
_CCSTYPE *_dxfccvsp;
_CCSTYPE _dxfccval;
_CCSTYPE _dxfcclval;
short _dxfccss[_CCSTACKSIZE];
_CCSTYPE _dxfccvs[_CCSTACKSIZE];
#define _dxfccstacksize _CCSTACKSIZE
#line 427 "_compparse.y"

_dxfccerror(char *s)
{
    if (DXGetError() == ERROR_NONE) {
	DXSetError(ERROR_BAD_PARAMETER, "#12100", s, _dxfcclexerror());
    }
    _dxdparseError++;
}
#line 375 "y.tab.c"
#define _CCABORT goto _dxfccabort
#define _CCREJECT goto _dxfccabort
#define _CCACCEPT goto _dxfccaccept
#define _CCERROR goto _dxfccerrlab
int
_dxfccparse()
{
    register int _dxfccm, _dxfccn, _dxfccstate;
#if _CCDEBUG
    register char *_dxfccs;
    extern char *getenv();

    if (_dxfccs = getenv("_CCDEBUG"))
    {
        _dxfccn = *_dxfccs;
        if (_dxfccn >= '0' && _dxfccn <= '9')
            _dxfccdebug = _dxfccn - '0';
    }
#endif

    _dxfccnerrs = 0;
    _dxfccerrflag = 0;
    _dxfccchar = (-1);

    _dxfccssp = _dxfccss;
    _dxfccvsp = _dxfccvs;
    *_dxfccssp = _dxfccstate = 0;

_dxfccloop:
    if (_dxfccn = _dxfccdefred[_dxfccstate]) goto _dxfccreduce;
    if (_dxfccchar < 0)
    {
        if ((_dxfccchar = _dxfcclex()) < 0) _dxfccchar = 0;
#if _CCDEBUG
        if (_dxfccdebug)
        {
            _dxfccs = 0;
            if (_dxfccchar <= _CCMAXTOKEN) _dxfccs = _dxfccname[_dxfccchar];
            if (!_dxfccs) _dxfccs = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    _CCPREFIX, _dxfccstate, _dxfccchar, _dxfccs);
        }
#endif
    }
    if ((_dxfccn = _dxfccsindex[_dxfccstate]) && (_dxfccn += _dxfccchar) >= 0 &&
            _dxfccn <= _CCTABLESIZE && _dxfcccheck[_dxfccn] == _dxfccchar)
    {
#if _CCDEBUG
        if (_dxfccdebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    _CCPREFIX, _dxfccstate, _dxfcctable[_dxfccn]);
#endif
        if (_dxfccssp >= _dxfccss + _dxfccstacksize - 1)
        {
            goto _dxfccoverflow;
        }
        *++_dxfccssp = _dxfccstate = _dxfcctable[_dxfccn];
        *++_dxfccvsp = _dxfcclval;
        _dxfccchar = (-1);
        if (_dxfccerrflag > 0)  --_dxfccerrflag;
        goto _dxfccloop;
    }
    if ((_dxfccn = _dxfccrindex[_dxfccstate]) && (_dxfccn += _dxfccchar) >= 0 &&
            _dxfccn <= _CCTABLESIZE && _dxfcccheck[_dxfccn] == _dxfccchar)
    {
        _dxfccn = _dxfcctable[_dxfccn];
        goto _dxfccreduce;
    }
    if (_dxfccerrflag) goto _dxfccinrecovery;
#ifdef lint
    goto _dxfccnewerror;
#endif
_dxfccnewerror:
    _dxfccerror("syntax error");
#ifdef lint
    goto _dxfccerrlab;
#endif
_dxfccerrlab:
    ++_dxfccnerrs;
_dxfccinrecovery:
    if (_dxfccerrflag < 3)
    {
        _dxfccerrflag = 3;
        for (;;)
        {
            if ((_dxfccn = _dxfccsindex[*_dxfccssp]) && (_dxfccn += _CCERRCODE) >= 0 &&
                    _dxfccn <= _CCTABLESIZE && _dxfcccheck[_dxfccn] == _CCERRCODE)
            {
#if _CCDEBUG
                if (_dxfccdebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", _CCPREFIX, *_dxfccssp, _dxfcctable[_dxfccn]);
#endif
                if (_dxfccssp >= _dxfccss + _dxfccstacksize - 1)
                {
                    goto _dxfccoverflow;
                }
                *++_dxfccssp = _dxfccstate = _dxfcctable[_dxfccn];
                *++_dxfccvsp = _dxfcclval;
                goto _dxfccloop;
            }
            else
            {
#if _CCDEBUG
                if (_dxfccdebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            _CCPREFIX, *_dxfccssp);
#endif
                if (_dxfccssp <= _dxfccss) goto _dxfccabort;
                --_dxfccssp;
                --_dxfccvsp;
            }
        }
    }
    else
    {
        if (_dxfccchar == 0) goto _dxfccabort;
#if _CCDEBUG
        if (_dxfccdebug)
        {
            _dxfccs = 0;
            if (_dxfccchar <= _CCMAXTOKEN) _dxfccs = _dxfccname[_dxfccchar];
            if (!_dxfccs) _dxfccs = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    _CCPREFIX, _dxfccstate, _dxfccchar, _dxfccs);
        }
#endif
        _dxfccchar = (-1);
        goto _dxfccloop;
    }
_dxfccreduce:
#if _CCDEBUG
    if (_dxfccdebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                _CCPREFIX, _dxfccstate, _dxfccn, _dxfccrule[_dxfccn]);
#endif
    _dxfccm = _dxfcclen[_dxfccn];
    _dxfccval = _dxfccvsp[1-_dxfccm];
    switch (_dxfccn)
    {
case 1:
#line 117 "_compparse.y"
{ _dxdparseError = 0; }
break;
case 2:
#line 119 "_compparse.y"
{
	    if (_dxdparseError)
	    {
		if (_dxfccvsp[-1].a) {
		    _dxfComputeFreeTree(_dxfccvsp[-1].a);
		}
		_dxdcomputeTree = NULL;
		_CCABORT;
	    }

	    _dxdcomputeTree = _dxfMakeList(NT_TOP, _dxfccvsp[-1].a);
	    _CCACCEPT;
	}
break;
case 3:
#line 136 "_compparse.y"
{
	    _dxfccval.a->next = NULL;
	}
break;
case 4:
#line 140 "_compparse.y"
{
	    _dxfccval.a = _dxfccvsp[0].a;
	}
break;
case 5:
#line 144 "_compparse.y"
{
	    PTreeNode *t = _dxfccvsp[-2].a;
	    while (t->next != NULL)
		t = t->next;
	    t->next = _dxfccvsp[0].a;
	    _dxfccval.a = _dxfccvsp[-2].a;
	}
break;
case 6:
#line 152 "_compparse.y"
{
	    PTreeNode *t = _dxfccvsp[-1].a;
	    while (t->next != NULL)
		t = t->next;
	    t->next = NULL;
	    _dxfccval.a = _dxfccvsp[-1].a;
	}
break;
case 7:
#line 163 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeInput(_dxfccvsp[0].i);
	}
break;
case 8:
#line 167 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeBinOp(OPER_PERIOD, _dxfccvsp[-2].a, _dxfccvsp[0].a);
	}
break;
case 9:
#line 171 "_compparse.y"
{
	    PTreeNode *pt;
	    pt = _dxfMakeArg(NT_CONSTANT);
	    pt->metaType.items = 1;
	    pt->metaType.type = TYPE_INT;
	    pt->metaType.category = CATEGORY_REAL;
	    if (strcmp (_dxfccvsp[0].s, "x") == 0) {
		pt->u.i = 0;
	    }
	    else if (strcmp (_dxfccvsp[0].s, "y") == 0) {
		pt->u.i = 1;
	    }
	    else if (strcmp (_dxfccvsp[0].s, "z") == 0) {
		pt->u.i = 2;
	    }
	    else {
		DXSetError(ERROR_BAD_PARAMETER, "#12100",
		    "syntax error");
		_dxdparseError++;
		_CCERROR;
	    }
	    _dxfccval.a = _dxfMakeBinOp(OPER_PERIOD, _dxfccvsp[-2].a, pt);
	}
break;
case 11:
#line 196 "_compparse.y"
{
	    _dxfccval.a = _dxfccvsp[-1].a;
	}
break;
case 12:
#line 200 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeList (NT_CONSTRUCT, _dxfccvsp[-1].a);
	}
break;
case 13:
#line 205 "_compparse.y"
{
	    /* It must be a function id */
	    if (_dxfComputeLookupFunction (_dxfccvsp[-3].s) == NT_ERROR) {
		DXSetError(ERROR_BAD_PARAMETER, "#12090", _dxfccvsp[-3].s);
		_dxdparseError++;
		_CCERROR;
	    }
	    else
	    {
		_dxfccval.a = _dxfMakeFunCall(_dxfccvsp[-3].s, _dxfccvsp[-1].a);
		if (_dxfccval.a == NULL) {
		    _dxdparseError++;
		    _CCERROR;
		}
	    }
	}
break;
case 14:
#line 223 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeFunCall("mod", _dxfccvsp[-1].a);
	    if (_dxfccval.a == NULL) {
		_dxdparseError++;
		_CCERROR;
	    }
	}
break;
case 15:
#line 232 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeFunCall("dot", _dxfccvsp[-1].a);
	    if (_dxfccval.a == NULL) {
		_dxdparseError++;
		_CCERROR;
	    }
	}
break;
case 16:
#line 241 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeFunCall("cross", _dxfccvsp[-1].a);
	    if (_dxfccval.a == NULL) {
		_dxdparseError++;
		_CCERROR;
	    }
	}
break;
case 17:
#line 249 "_compparse.y"
{
            _dxfccval.a = _dxfMakeConditional(_dxfccvsp[-4].a, _dxfccvsp[-2].a, _dxfccvsp[0].a);
        }
break;
case 18:
#line 253 "_compparse.y"
{
            _dxfccval.a = _dxfMakeBinOp(OPER_AND, _dxfccvsp[-2].a, _dxfccvsp[0].a);
        }
break;
case 19:
#line 257 "_compparse.y"
{
            _dxfccval.a = _dxfMakeBinOp(OPER_OR, _dxfccvsp[-2].a, _dxfccvsp[0].a);
        }
break;
case 20:
#line 261 "_compparse.y"
{
            _dxfccval.a = _dxfMakeBinOp(OPER_GT, _dxfccvsp[-2].a, _dxfccvsp[0].a);
        }
break;
case 21:
#line 265 "_compparse.y"
{
            _dxfccval.a = _dxfMakeBinOp(OPER_GE, _dxfccvsp[-2].a, _dxfccvsp[0].a);
        }
break;
case 22:
#line 269 "_compparse.y"
{
            _dxfccval.a = _dxfMakeBinOp(OPER_LT, _dxfccvsp[-2].a, _dxfccvsp[0].a);
        }
break;
case 23:
#line 273 "_compparse.y"
{
            _dxfccval.a = _dxfMakeBinOp(OPER_LE, _dxfccvsp[-2].a, _dxfccvsp[0].a);
        }
break;
case 24:
#line 277 "_compparse.y"
{
            _dxfccval.a = _dxfMakeBinOp(OPER_EQ, _dxfccvsp[-2].a, _dxfccvsp[0].a);
        }
break;
case 25:
#line 281 "_compparse.y"
{
            _dxfccval.a = _dxfMakeBinOp(OPER_NE, _dxfccvsp[-2].a, _dxfccvsp[0].a);
        }
break;
case 26:
#line 285 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeBinOp(OPER_PLUS, _dxfccvsp[-2].a, _dxfccvsp[0].a);
	}
break;
case 27:
#line 289 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeBinOp(OPER_MINUS, _dxfccvsp[-2].a, _dxfccvsp[0].a);
	}
break;
case 28:
#line 293 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeBinOp(OPER_MUL, _dxfccvsp[-2].a, _dxfccvsp[0].a);
	}
break;
case 29:
#line 297 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeBinOp(OPER_DIV, _dxfccvsp[-2].a, _dxfccvsp[0].a);
	}
break;
case 30:
#line 301 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeBinOp(OPER_MOD, _dxfccvsp[-2].a, _dxfccvsp[0].a);
	}
break;
case 31:
#line 305 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeBinOp(OPER_DOT, _dxfccvsp[-2].a, _dxfccvsp[0].a);
	}
break;
case 32:
#line 309 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeBinOp(OPER_CROSS, _dxfccvsp[-2].a, _dxfccvsp[0].a);
	}
break;
case 33:
#line 313 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeBinOp(OPER_EXP, _dxfccvsp[-2].a, _dxfccvsp[0].a);
	}
break;
case 34:
#line 317 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeUnOp(OPER_MINUS, _dxfccvsp[0].a);
	}
break;
case 35:
#line 321 "_compparse.y"
{
	    _dxfccval.a = _dxfccvsp[0].a;
	}
break;
case 36:
#line 325 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeUnOp (OPER_NOT, _dxfccvsp[0].a);
	}
break;
case 37:
#line 329 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeAssignment (_dxfccvsp[-2].s, _dxfccvsp[0].a);
	}
break;
case 38:
#line 333 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeVariable (_dxfccvsp[0].s);
	}
break;
case 39:
#line 340 "_compparse.y"
{
	    _dxfccval.a = NULL;
	}
break;
case 41:
#line 348 "_compparse.y"
{
	    _dxfccval.a->next = NULL;
	}
break;
case 42:
#line 352 "_compparse.y"
{
	    PTreeNode *t = _dxfccvsp[-2].a;
	    while (t->next != NULL)
		t = t->next;
	    t->next = _dxfccvsp[0].a;
	    _dxfccval.a = _dxfccvsp[-2].a;
	}
break;
case 43:
#line 364 "_compparse.y"
{ 
	    _dxfccval.a->next = NULL;
	}
break;
case 44:
#line 368 "_compparse.y"
{
	    PTreeNode *t = _dxfccvsp[-2].a;
	    while (t->next != NULL)
		t = t->next;
	    t->next = _dxfccvsp[0].a;
	    _dxfccval.a = _dxfccvsp[-2].a;
	}
break;
case 46:
#line 391 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeArg(NT_CONSTANT);
	    _dxfccval.a->metaType.items = 1;
	    _dxfccval.a->metaType.type = TYPE_INT;
	    _dxfccval.a->metaType.category = CATEGORY_REAL;
	    _dxfccval.a->u.i = _dxfccvsp[0].i;
	}
break;
case 47:
#line 399 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeArg(NT_CONSTANT);
	    _dxfccval.a->metaType.items = 1;
	    _dxfccval.a->metaType.type = TYPE_FLOAT;
	    _dxfccval.a->metaType.category = CATEGORY_REAL;
	    _dxfccval.a->u.f = _dxfccvsp[0].f;
	}
break;
case 48:
#line 407 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeArg(NT_CONSTANT);
	    _dxfccval.a->metaType.items = 1;
	    _dxfccval.a->metaType.type = TYPE_DOUBLE;
	    _dxfccval.a->metaType.category = CATEGORY_REAL;
	    _dxfccval.a->u.d = _dxfccvsp[0].d;
	}
break;
case 49:
#line 415 "_compparse.y"
{
	    _dxfccval.a = _dxfMakeArg(NT_CONSTANT);
	    _dxfccval.a->metaType.items = 1;
	    _dxfccval.a->metaType.type = TYPE_STRING;
	    _dxfccval.a->metaType.category = CATEGORY_REAL;
	    _dxfccval.a->metaType.rank = 1;
	    _dxfccval.a->metaType.shape[0] = strlen(_dxfccvsp[0].s)+1;
	    strcpy(_dxfccval.a->u.s, _dxfccvsp[0].s);
	}
break;
#line 879 "y.tab.c"
    }
    _dxfccssp -= _dxfccm;
    _dxfccstate = *_dxfccssp;
    _dxfccvsp -= _dxfccm;
    _dxfccm = _dxfcclhs[_dxfccn];
    if (_dxfccstate == 0 && _dxfccm == 0)
    {
#if _CCDEBUG
        if (_dxfccdebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", _CCPREFIX, _CCFINAL);
#endif
        _dxfccstate = _CCFINAL;
        *++_dxfccssp = _CCFINAL;
        *++_dxfccvsp = _dxfccval;
        if (_dxfccchar < 0)
        {
            if ((_dxfccchar = _dxfcclex()) < 0) _dxfccchar = 0;
#if _CCDEBUG
            if (_dxfccdebug)
            {
                _dxfccs = 0;
                if (_dxfccchar <= _CCMAXTOKEN) _dxfccs = _dxfccname[_dxfccchar];
                if (!_dxfccs) _dxfccs = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        _CCPREFIX, _CCFINAL, _dxfccchar, _dxfccs);
            }
#endif
        }
        if (_dxfccchar == 0) goto _dxfccaccept;
        goto _dxfccloop;
    }
    if ((_dxfccn = _dxfccgindex[_dxfccm]) && (_dxfccn += _dxfccstate) >= 0 &&
            _dxfccn <= _CCTABLESIZE && _dxfcccheck[_dxfccn] == _dxfccstate)
        _dxfccstate = _dxfcctable[_dxfccn];
    else
        _dxfccstate = _dxfccdgoto[_dxfccm];
#if _CCDEBUG
    if (_dxfccdebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", _CCPREFIX, *_dxfccssp, _dxfccstate);
#endif
    if (_dxfccssp >= _dxfccss + _dxfccstacksize - 1)
    {
        goto _dxfccoverflow;
    }
    *++_dxfccssp = _dxfccstate;
    *++_dxfccvsp = _dxfccval;
    goto _dxfccloop;
_dxfccoverflow:
    _dxfccerror("yacc stack overflow");
_dxfccabort:
    return (1);
_dxfccaccept:
    return (0);
}
