/* A Bison parser, made from ./_compparse.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse _dxfccparse
#define yylex _dxfcclex
#define yyerror _dxfccerror
#define yylval _dxfcclval
#define yychar _dxfccchar
#define yydebug _dxfccdebug
#define yynerrs _dxfccnerrs
# define	T_NAME	257
# define	T_FLOAT	258
# define	T_DOUBLE	259
# define	T_INT	260
# define	T_INPUT	261
# define	T_ID	262
# define	T_STRING	263
# define	T_EOF	264
# define	T_LPAR	265
# define	T_RPAR	266
# define	T_LBRA	267
# define	T_RBRA	268
# define	T_LSQB	269
# define	T_RSQB	270
# define	T_COMMA	271
# define	T_PERIOD	272
# define	T_COLON	273
# define	T_LOR	274
# define	T_LAND	275
# define	T_LNOT	276
# define	T_LT	277
# define	T_LE	278
# define	T_GT	279
# define	T_GE	280
# define	T_EQ	281
# define	T_NE	282
# define	T_QUEST	283
# define	T_CROSS	284
# define	T_DOT	285
# define	T_PLUS	286
# define	T_MINUS	287
# define	T_EXP	288
# define	T_TIMES	289
# define	T_DIV	290
# define	T_MOD	291
# define	T_ASSIGN	292
# define	T_SEMI	293
# define	U_MINUS	294
# define	U_PLUS	295
# define	U_LNOT	296

#line 10 "./_compparse.y"

#include <math.h>
#include <string.h>
#include <dx/dx.h>
#include "_compute.h"
#include "_compputils.h"



int _dxdparseError = 0;		/* Only shared with _compputils.c */
PTreeNode * _dxfMakeFunCall(char *func, PTreeNode *args);



#line 27 "./_compparse.y"
#ifndef YYSTYPE
typedef union {
#define MAX_PARSE_STRING_SIZE 512
    char s[MAX_PARSE_STRING_SIZE];
    int i;
    float f;
    double d;
    PTreeNode *a;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		94
#define	YYFLAG		-32768
#define	YYNTBASE	43

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 296 ? yytranslate[x] : 52)

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
      36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     5,     7,    10,    14,    17,    19,    23,
      27,    29,    33,    37,    42,    47,    52,    57,    63,    67,
      71,    75,    79,    83,    87,    91,    95,    99,   103,   107,
     111,   115,   119,   123,   127,   130,   133,   136,   140,   142,
     143,   145,   147,   151,   153,   157,   159,   161,   163,   165
};
static const short yyrhs[] =
{
      -1,    44,    45,    10,     0,    46,     0,    39,    45,     0,
      45,    39,    46,     0,    45,    39,     0,     7,     0,    46,
      18,    50,     0,    46,    18,     3,     0,    50,     0,    11,
      46,    12,     0,    15,    49,    16,     0,     3,    11,    47,
      12,     0,    37,    11,    47,    12,     0,    31,    11,    47,
      12,     0,    30,    11,    47,    12,     0,    46,    29,    46,
      19,    46,     0,    46,    21,    46,     0,    46,    20,    46,
       0,    46,    25,    46,     0,    46,    26,    46,     0,    46,
      23,    46,     0,    46,    24,    46,     0,    46,    27,    46,
       0,    46,    28,    46,     0,    46,    32,    46,     0,    46,
      33,    46,     0,    46,    35,    46,     0,    46,    36,    46,
       0,    46,    37,    46,     0,    46,    31,    46,     0,    46,
      30,    46,     0,    46,    34,    46,     0,    33,    46,     0,
      32,    46,     0,    22,    46,     0,     3,    38,    46,     0,
       3,     0,     0,    48,     0,    46,     0,    48,    17,    46,
       0,    46,     0,    49,    17,    46,     0,    51,     0,     6,
       0,     4,     0,     5,     0,     9,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   118,   118,   136,   140,   144,   152,   163,   167,   171,
     195,   196,   200,   204,   222,   231,   240,   249,   253,   257,
     261,   265,   269,   273,   277,   281,   285,   289,   293,   297,
     301,   305,   309,   313,   317,   321,   325,   329,   333,   340,
     344,   348,   352,   364,   368,   387,   391,   399,   407,   415
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "T_NAME", "T_FLOAT", "T_DOUBLE", "T_INT", 
  "T_INPUT", "T_ID", "T_STRING", "T_EOF", "T_LPAR", "T_RPAR", "T_LBRA", 
  "T_RBRA", "T_LSQB", "T_RSQB", "T_COMMA", "T_PERIOD", "T_COLON", "T_LOR", 
  "T_LAND", "T_LNOT", "T_LT", "T_LE", "T_GT", "T_GE", "T_EQ", "T_NE", 
  "T_QUEST", "T_CROSS", "T_DOT", "T_PLUS", "T_MINUS", "T_EXP", "T_TIMES", 
  "T_DIV", "T_MOD", "T_ASSIGN", "T_SEMI", "U_MINUS", "U_PLUS", "U_LNOT", 
  "top", "@1", "statement_list", "expr", "optional_argument_list", 
  "argument_list", "list", "constant", "real", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    44,    43,    45,    45,    45,    45,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    47,
      47,    48,    48,    49,    49,    50,    51,    51,    51,    51
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     3,     1,     2,     3,     2,     1,     3,     3,
       1,     3,     3,     4,     4,     4,     4,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     3,     1,     0,
       1,     1,     3,     1,     3,     1,     1,     1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,    38,    47,    48,    46,     7,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    10,
      45,    39,     0,     0,    43,     0,    36,    39,    39,    35,
      34,    39,     4,     2,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    41,     0,    40,    37,    11,    12,     0,
       0,     0,     0,     5,     9,     8,    19,    18,    22,    23,
      20,    21,    24,    25,     0,    32,    31,    26,    27,    33,
      28,    29,    30,    13,     0,    44,    16,    15,    14,     0,
      42,    17,     0,     0,     0
};

static const short yydefgoto[] =
{
      92,     1,    17,    53,    54,    55,    25,    19,    20
};

static const short yypact[] =
{
  -32768,    59,    -7,-32768,-32768,-32768,-32768,-32768,    96,    96,
      96,     0,     3,    96,    96,     6,    59,    -9,   158,-32768,
  -32768,    96,    96,   118,   158,   -11,-32768,    96,    96,-32768,
  -32768,    96,   -19,-32768,    96,    51,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,   158,    20,    17,   158,-32768,-32768,    96,
      40,    49,    55,   158,-32768,-32768,   178,   198,    -8,    -8,
      -8,    -8,   218,   218,   138,    79,   -16,    41,    41,    35,
     -15,   -15,   -15,-32768,    96,   158,-32768,-32768,-32768,    96,
     158,   158,    69,    73,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,    63,    -1,    81,-32768,-32768,    45,-32768
};


#define	YYLAST		255


static const short yytable[] =
{
      18,    33,    35,    35,    21,    58,    59,    23,    24,    26,
      35,    27,    29,    30,    28,    18,    46,    31,    49,    49,
      34,    56,    45,    46,    47,    48,    49,    50,    51,    52,
      34,    22,    83,    63,    84,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    86,    35,    64,     3,     4,     5,    85,    35,
       7,    87,     2,     3,     4,     5,     6,    88,     7,    93,
       8,    45,    46,    94,     9,    49,    50,    51,    52,    32,
      65,    10,     0,    90,     0,     0,     0,     0,    91,    11,
      12,    13,    14,     0,     0,     0,    15,    35,    16,     2,
       3,     4,     5,     6,     0,     7,     0,     8,    60,    61,
      46,     9,    62,    49,    50,    51,    52,     0,    10,     0,
       0,     0,     0,     0,     0,     0,    11,    12,    13,    14,
      57,     0,     0,    15,     0,     0,    35,     0,    36,    37,
       0,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    35,    89,    36,    37,
       0,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    35,     0,    36,    37,
       0,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    35,     0,     0,    37,
       0,    38,    39,    40,    41,    42,    43,     0,    45,    46,
      47,    48,    49,    50,    51,    52,    35,     0,     0,     0,
       0,    38,    39,    40,    41,    42,    43,     0,    45,    46,
      47,    48,    49,    50,    51,    52,    35,     0,     0,     0,
       0,    38,    39,    40,    41,     0,     0,     0,    45,    46,
      47,    48,    49,    50,    51,    52
};

static const short yycheck[] =
{
       1,    10,    18,    18,    11,    16,    17,     8,     9,    10,
      18,    11,    13,    14,    11,    16,    31,    11,    34,    34,
      39,    22,    30,    31,    32,    33,    34,    35,    36,    37,
      39,    38,    12,    34,    17,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    12,    18,     3,     4,     5,     6,    59,    18,
       9,    12,     3,     4,     5,     6,     7,    12,     9,     0,
      11,    30,    31,     0,    15,    34,    35,    36,    37,    16,
      35,    22,    -1,    84,    -1,    -1,    -1,    -1,    89,    30,
      31,    32,    33,    -1,    -1,    -1,    37,    18,    39,     3,
       4,     5,     6,     7,    -1,     9,    -1,    11,    27,    28,
      31,    15,    31,    34,    35,    36,    37,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      12,    -1,    -1,    37,    -1,    -1,    18,    -1,    20,    21,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    18,    19,    20,    21,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    18,    -1,    20,    21,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    18,    -1,    -1,    21,
      -1,    23,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    18,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    18,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    37
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
#line 118 "./_compparse.y"
{ _dxdparseError = 0; }
    break;
case 2:
#line 120 "./_compparse.y"
{
	    if (_dxdparseError)
	    {
		if (yyvsp[-1].a) {
		    _dxfComputeFreeTree(yyvsp[-1].a);
		}
		_dxdcomputeTree = NULL;
		YYABORT;
	    }

	    _dxdcomputeTree = _dxfMakeList(NT_TOP, yyvsp[-1].a);
	    YYACCEPT;
	}
    break;
case 3:
#line 137 "./_compparse.y"
{
	    yyval.a->next = NULL;
	}
    break;
case 4:
#line 141 "./_compparse.y"
{
	    yyval.a = yyvsp[0].a;
	}
    break;
case 5:
#line 145 "./_compparse.y"
{
	    PTreeNode *t = yyvsp[-2].a;
	    while (t->next != NULL)
		t = t->next;
	    t->next = yyvsp[0].a;
	    yyval.a = yyvsp[-2].a;
	}
    break;
case 6:
#line 153 "./_compparse.y"
{
	    PTreeNode *t = yyvsp[-1].a;
	    while (t->next != NULL)
		t = t->next;
	    t->next = NULL;
	    yyval.a = yyvsp[-1].a;
	}
    break;
case 7:
#line 164 "./_compparse.y"
{
	    yyval.a = _dxfMakeInput(yyvsp[0].i);
	}
    break;
case 8:
#line 168 "./_compparse.y"
{
	    yyval.a = _dxfMakeBinOp(OPER_PERIOD, yyvsp[-2].a, yyvsp[0].a);
	}
    break;
case 9:
#line 172 "./_compparse.y"
{
	    PTreeNode *pt;
	    pt = _dxfMakeArg(NT_CONSTANT);
	    pt->metaType.items = 1;
	    pt->metaType.type = TYPE_INT;
	    pt->metaType.category = CATEGORY_REAL;
	    if (strcmp (yyvsp[0].s, "x") == 0) {
		pt->u.i = 0;
	    }
	    else if (strcmp (yyvsp[0].s, "y") == 0) {
		pt->u.i = 1;
	    }
	    else if (strcmp (yyvsp[0].s, "z") == 0) {
		pt->u.i = 2;
	    }
	    else {
		DXSetError(ERROR_BAD_PARAMETER, "#12100",
		    "syntax error");
		_dxdparseError++;
		YYERROR;
	    }
	    yyval.a = _dxfMakeBinOp(OPER_PERIOD, yyvsp[-2].a, pt);
	}
    break;
case 11:
#line 197 "./_compparse.y"
{
	    yyval.a = yyvsp[-1].a;
	}
    break;
case 12:
#line 201 "./_compparse.y"
{
	    yyval.a = _dxfMakeList (NT_CONSTRUCT, yyvsp[-1].a);
	}
    break;
case 13:
#line 206 "./_compparse.y"
{
	    /* It must be a function id */
	    if (_dxfComputeLookupFunction (yyvsp[-3].s) == NT_ERROR) {
		DXSetError(ERROR_BAD_PARAMETER, "#12090", yyvsp[-3].s);
		_dxdparseError++;
		YYERROR;
	    }
	    else
	    {
		yyval.a = _dxfMakeFunCall(yyvsp[-3].s, yyvsp[-1].a);
		if (yyval.a == NULL) {
		    _dxdparseError++;
		    YYERROR;
		}
	    }
	}
    break;
case 14:
#line 224 "./_compparse.y"
{
	    yyval.a = _dxfMakeFunCall("mod", yyvsp[-1].a);
	    if (yyval.a == NULL) {
		_dxdparseError++;
		YYERROR;
	    }
	}
    break;
case 15:
#line 233 "./_compparse.y"
{
	    yyval.a = _dxfMakeFunCall("dot", yyvsp[-1].a);
	    if (yyval.a == NULL) {
		_dxdparseError++;
		YYERROR;
	    }
	}
    break;
case 16:
#line 242 "./_compparse.y"
{
	    yyval.a = _dxfMakeFunCall("cross", yyvsp[-1].a);
	    if (yyval.a == NULL) {
		_dxdparseError++;
		YYERROR;
	    }
	}
    break;
case 17:
#line 250 "./_compparse.y"
{
            yyval.a = _dxfMakeConditional(yyvsp[-4].a, yyvsp[-2].a, yyvsp[0].a);
        }
    break;
case 18:
#line 254 "./_compparse.y"
{
            yyval.a = _dxfMakeBinOp(OPER_AND, yyvsp[-2].a, yyvsp[0].a);
        }
    break;
case 19:
#line 258 "./_compparse.y"
{
            yyval.a = _dxfMakeBinOp(OPER_OR, yyvsp[-2].a, yyvsp[0].a);
        }
    break;
case 20:
#line 262 "./_compparse.y"
{
            yyval.a = _dxfMakeBinOp(OPER_GT, yyvsp[-2].a, yyvsp[0].a);
        }
    break;
case 21:
#line 266 "./_compparse.y"
{
            yyval.a = _dxfMakeBinOp(OPER_GE, yyvsp[-2].a, yyvsp[0].a);
        }
    break;
case 22:
#line 270 "./_compparse.y"
{
            yyval.a = _dxfMakeBinOp(OPER_LT, yyvsp[-2].a, yyvsp[0].a);
        }
    break;
case 23:
#line 274 "./_compparse.y"
{
            yyval.a = _dxfMakeBinOp(OPER_LE, yyvsp[-2].a, yyvsp[0].a);
        }
    break;
case 24:
#line 278 "./_compparse.y"
{
            yyval.a = _dxfMakeBinOp(OPER_EQ, yyvsp[-2].a, yyvsp[0].a);
        }
    break;
case 25:
#line 282 "./_compparse.y"
{
            yyval.a = _dxfMakeBinOp(OPER_NE, yyvsp[-2].a, yyvsp[0].a);
        }
    break;
case 26:
#line 286 "./_compparse.y"
{
	    yyval.a = _dxfMakeBinOp(OPER_PLUS, yyvsp[-2].a, yyvsp[0].a);
	}
    break;
case 27:
#line 290 "./_compparse.y"
{
	    yyval.a = _dxfMakeBinOp(OPER_MINUS, yyvsp[-2].a, yyvsp[0].a);
	}
    break;
case 28:
#line 294 "./_compparse.y"
{
	    yyval.a = _dxfMakeBinOp(OPER_MUL, yyvsp[-2].a, yyvsp[0].a);
	}
    break;
case 29:
#line 298 "./_compparse.y"
{
	    yyval.a = _dxfMakeBinOp(OPER_DIV, yyvsp[-2].a, yyvsp[0].a);
	}
    break;
case 30:
#line 302 "./_compparse.y"
{
	    yyval.a = _dxfMakeBinOp(OPER_MOD, yyvsp[-2].a, yyvsp[0].a);
	}
    break;
case 31:
#line 306 "./_compparse.y"
{
	    yyval.a = _dxfMakeBinOp(OPER_DOT, yyvsp[-2].a, yyvsp[0].a);
	}
    break;
case 32:
#line 310 "./_compparse.y"
{
	    yyval.a = _dxfMakeBinOp(OPER_CROSS, yyvsp[-2].a, yyvsp[0].a);
	}
    break;
case 33:
#line 314 "./_compparse.y"
{
	    yyval.a = _dxfMakeBinOp(OPER_EXP, yyvsp[-2].a, yyvsp[0].a);
	}
    break;
case 34:
#line 318 "./_compparse.y"
{
	    yyval.a = _dxfMakeUnOp(OPER_MINUS, yyvsp[0].a);
	}
    break;
case 35:
#line 322 "./_compparse.y"
{
	    yyval.a = yyvsp[0].a;
	}
    break;
case 36:
#line 326 "./_compparse.y"
{
	    yyval.a = _dxfMakeUnOp (OPER_NOT, yyvsp[0].a);
	}
    break;
case 37:
#line 330 "./_compparse.y"
{
	    yyval.a = _dxfMakeAssignment (yyvsp[-2].s, yyvsp[0].a);
	}
    break;
case 38:
#line 334 "./_compparse.y"
{
	    yyval.a = _dxfMakeVariable (yyvsp[0].s);
	}
    break;
case 39:
#line 341 "./_compparse.y"
{
	    yyval.a = NULL;
	}
    break;
case 41:
#line 349 "./_compparse.y"
{
	    yyval.a->next = NULL;
	}
    break;
case 42:
#line 353 "./_compparse.y"
{
	    PTreeNode *t = yyvsp[-2].a;
	    while (t->next != NULL)
		t = t->next;
	    t->next = yyvsp[0].a;
	    yyval.a = yyvsp[-2].a;
	}
    break;
case 43:
#line 365 "./_compparse.y"
{ 
	    yyval.a->next = NULL;
	}
    break;
case 44:
#line 369 "./_compparse.y"
{
	    PTreeNode *t = yyvsp[-2].a;
	    while (t->next != NULL)
		t = t->next;
	    t->next = yyvsp[0].a;
	    yyval.a = yyvsp[-2].a;
	}
    break;
case 46:
#line 392 "./_compparse.y"
{
	    yyval.a = _dxfMakeArg(NT_CONSTANT);
	    yyval.a->metaType.items = 1;
	    yyval.a->metaType.type = TYPE_INT;
	    yyval.a->metaType.category = CATEGORY_REAL;
	    yyval.a->u.i = yyvsp[0].i;
	}
    break;
case 47:
#line 400 "./_compparse.y"
{
	    yyval.a = _dxfMakeArg(NT_CONSTANT);
	    yyval.a->metaType.items = 1;
	    yyval.a->metaType.type = TYPE_FLOAT;
	    yyval.a->metaType.category = CATEGORY_REAL;
	    yyval.a->u.f = yyvsp[0].f;
	}
    break;
case 48:
#line 408 "./_compparse.y"
{
	    yyval.a = _dxfMakeArg(NT_CONSTANT);
	    yyval.a->metaType.items = 1;
	    yyval.a->metaType.type = TYPE_DOUBLE;
	    yyval.a->metaType.category = CATEGORY_REAL;
	    yyval.a->u.d = yyvsp[0].d;
	}
    break;
case 49:
#line 416 "./_compparse.y"
{
	    yyval.a = _dxfMakeArg(NT_CONSTANT);
	    yyval.a->metaType.items = 1;
	    yyval.a->metaType.type = TYPE_STRING;
	    yyval.a->metaType.category = CATEGORY_REAL;
	    yyval.a->metaType.rank = 1;
	    yyval.a->metaType.shape[0] = strlen(yyvsp[0].s)+1;
	    strcpy(yyval.a->u.s, yyvsp[0].s);
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
#line 427 "./_compparse.y"


int yyerror(char *s)
{
    if (DXGetError() == ERROR_NONE) {
	DXSetError(ERROR_BAD_PARAMETER, "#12100", s, _dxfcclexerror());
    }
    _dxdparseError++;
    return 0;            /*  Return a value to keep the compiler happy  */
}
