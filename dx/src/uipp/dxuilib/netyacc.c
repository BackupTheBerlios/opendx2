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
#line 2 "net.yacc"

/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*****************************************************************************/
/* uin.yacc -								     */
/* Contains SVS script language grammar for yacc.			     */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/netyacc.c,v 1.1 1999/03/24 15:18:19 gda Exp $
 */

#include "Parse.h"

#line 29 "net.yacc"
typedef union
{
    char                c;
    int                 i;
    float               f;
    char                s[4096];	/* 4096 == YYLMAX in net.lex */
} YYSTYPE;
#line 46 "y.tab.c"
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
#define V_TRUE 274
#define V_FALSE 275
#define T_BAR 276
#define T_LPAR 277
#define T_RPAR 278
#define T_LBRA 279
#define T_RBRA 280
#define T_LSQB 281
#define T_RSQB 282
#define T_ASSIGN 283
#define T_COMMA 284
#define T_COLON 285
#define T_SEMI 286
#define T_PP 287
#define T_MM 288
#define T_RA 289
#define T_DOTDOT 290
#define T_COMMENT 291
#define T_ID 292
#define T_EXID 293
#define T_INT 294
#define T_STRING 295
#define T_FLOAT 296
#define K_BACKWARD 297
#define K_CANCEL 298
#define K_ELSE 299
#define K_FOR 300
#define K_FORWARD 301
#define K_IF 302
#define K_INCLUDE 303
#define K_LOOP 304
#define K_MACRO 305
#define K_MODULE 306
#define K_NULL 307
#define K_OFF 308
#define K_ON 309
#define K_PALINDROME 310
#define K_PAUSE 311
#define K_PLAY 312
#define K_QUIT 313
#define K_REPEAT 314
#define K_RESUME 315
#define K_SEQUENCE 316
#define K_STEP 317
#define K_STOP 318
#define K_SUSPEND 319
#define K_THEN 320
#define K_UNTIL 321
#define K_WHILE 322
#define P_INTERRUPT 323
#define P_SYSTEM 324
#define P_ACK 325
#define P_MACRO 326
#define P_FOREGROUND 327
#define P_BACKGROUND 328
#define P_ERROR 329
#define P_MESSAGE 330
#define P_INFO 331
#define P_LINQ 332
#define P_SINQ 333
#define P_VINQ 334
#define P_LRESP 335
#define P_SRESP 336
#define P_VRESP 337
#define P_DATA 338
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    2,    1,    1,    1,    4,    4,    6,    6,    9,
    9,   10,   10,   10,   10,    8,   12,   12,   13,   13,
    3,    3,    3,    3,    3,   16,   14,   14,   19,   20,
   20,   20,    7,    7,   23,   24,   24,   25,   25,   26,
   26,   28,   15,   29,   29,   30,   30,   31,   31,   32,
   32,   17,   22,   22,   33,   33,   33,   11,   11,   11,
   11,   11,   37,   37,   37,   37,   37,   39,   39,   39,
   36,   36,   38,   38,   38,   35,   35,   35,   41,   41,
   42,   42,   43,   43,   27,   44,   40,   40,   40,   18,
   45,   45,   46,   46,   21,   21,   47,   34,    5,
};
short yylen[] = {                                         2,
    2,    0,    1,    1,    1,   11,    7,    1,    1,    2,
    4,    1,    3,    3,    5,    3,    1,    1,    1,    2,
    1,    3,    3,    1,    1,    2,    1,    1,    3,    3,
    2,    2,    1,    1,    3,    1,    1,    1,    3,    3,
    3,    0,    5,    1,    1,    1,    3,    1,    3,    1,
    1,    1,    1,    3,    1,    1,    3,    1,    1,    1,
    1,    1,    3,    3,    3,    5,    7,    1,    2,    3,
    3,    3,    1,    2,    3,    1,    1,    1,    1,    1,
    5,    5,    9,    9,    1,    1,    1,    2,    3,    1,
    1,    1,    2,    4,    2,    4,    1,    1,    0,
};
short yydefred[] = {                                      0,
    0,   52,    0,    0,    0,    0,    2,    3,    4,    5,
   21,    0,    0,   24,   25,   27,   28,    0,    0,   19,
   17,    0,    0,   31,   32,    0,   90,   26,    0,    1,
    0,   33,    0,   34,    0,    0,    0,   95,   16,   20,
    0,    0,    0,   36,    0,    0,   38,   22,   23,    0,
    0,    0,    0,   85,   86,   62,   55,   29,   61,    0,
   79,   53,   56,   58,   59,   60,   76,   77,   78,   80,
   97,    0,    0,    0,   44,   50,    0,    0,   46,   48,
    0,    8,    0,    0,    0,    0,   35,    0,   98,    0,
    0,    0,   87,   73,   68,    0,    0,    0,    0,    0,
    0,    0,   96,    0,    0,    0,   43,    0,    0,    0,
    0,   10,   40,   41,   39,    0,   57,    0,   63,    0,
   74,   64,    0,   69,   65,    0,   88,    0,   71,   72,
   54,   51,   49,   47,    0,   14,    0,    0,    0,    0,
    0,   75,   70,   89,    0,    0,    0,    7,   11,   81,
    0,   82,    0,   66,    0,   15,    0,    0,    0,    0,
    0,    0,    0,   67,    0,    0,    0,    6,   83,   84,
};
short yydgoto[] = {                                       6,
    7,   30,    8,    9,   32,   83,   33,   11,   84,   85,
   57,   22,   23,   12,   13,   14,   15,   59,   16,   17,
   18,   60,   34,   45,   46,   47,   61,   26,   77,   78,
   79,   80,   62,   63,   64,   65,   66,   96,   97,   98,
   67,   68,   69,   70,    0,    0,   19,
};
short yysindex[] = {                                   -254,
 -193,    0, -142, -249, -239,    0,    0,    0,    0,    0,
    0, -223, -223,    0,    0,    0,    0, -119, -223,    0,
    0, -209, -193,    0,    0, -199,    0,    0, -189,    0,
 -201,    0, -173,    0, -158, -260, -139,    0,    0,    0,
 -227, -131, -144,    0, -106,  -88,    0,    0,    0, -192,
 -202, -255,    0,    0,    0,    0,    0,    0,    0,  -87,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -223, -121,  -85,    0,    0,  -79,  -84,    0,    0,
  -82,    0,  -76,  -81, -223, -100,    0, -201,    0,  -80,
  -73,  -78,    0,    0,    0, -126,  -91, -264,  -83, -125,
 -151, -192,    0,  -80,  -78, -160,    0, -227, -152, -226,
 -131,    0,    0,    0,    0,  -86,    0,  -77,    0, -232,
    0,    0,  -72,    0,    0, -249,    0, -121,    0,    0,
    0,    0,    0,    0,  -71,    0,  -67,  -68, -223, -188,
 -177,    0,    0,    0, -262, -157, -131,    0,    0,    0,
  -86,    0,  -77,    0, -121,    0,  -65,  -70,  -69,  -64,
 -223,  -86,  -77,    0,  -68,  -61,  -60,    0,    0,    0,
};
short yyrindex[] = {                                    220,
  -59,    0,  -97,    0,    0,    0,    0,    0,    0,    0,
    0,  -63,  -63,    0,    0,    0,    0,    0,  -92,    0,
    0,    0,  -58,    0,    0,    0,    0,    0,    0,    0,
  -57,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -54,  -54,    0,    0,    0,  -56,    0,    0,    0,    0,
    0,    0, -103,    0,    0,    0,    0,    0,    0, -257,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -92,    0, -122,    0,    0,    0,  -51,    0,    0,
 -172,    0,    0,  -50, -112,    0,    0,    0,    0,  -49,
    0,  -48,    0,    0,    0,    0,    0,    0, -117,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -47,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -96,    0,    0,    0, -112,    0,
    0,    0,    0,    0,    0,    0,  -54,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -47,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,    0,    7,    0,    2,   84,  -13, -123,    0,  122,
  -32,    0,    0,    0,  198,    0,    0,   -3,    0,    0,
    0,    0,    0,    0,    0,  147,  -46,    0,    0,    0,
  128,  131,  -36,    0,  -39,  -41,    0,  186,  187,    0,
  -44,    0,    0,  -45,    0,    0,  203,
};
#define YYTABLESIZE 240
short yytable[] = {                                      35,
   28,   10,   21,   90,   92,   38,   99,   20,   76,   95,
   95,   94,   94,   91,  148,  125,   50,  154,   51,  126,
   52,   73,  155,   30,    1,   52,  104,  105,   30,   40,
   27,   53,   44,   54,   27,   55,    2,    3,   54,  114,
   55,  168,   75,   82,   73,   27,   56,   93,    4,   73,
    5,   51,   29,   52,   31,  124,  121,   31,  103,  124,
  121,   54,  137,   55,   74,  131,   54,   27,   55,  140,
   39,  112,  141,   76,   73,   76,  136,   41,   52,   56,
  142,  143,  113,  145,   50,    1,   51,   42,   52,  150,
   43,   54,   27,   55,  127,  151,  138,    2,    3,   89,
  152,   54,   27,   55,  158,   12,  153,  159,   12,    4,
  160,   12,   48,  156,   56,  166,   73,  167,   51,   73,
   52,   51,  144,   52,   73,  149,   51,   49,   52,   52,
  130,  132,  123,   54,   27,   55,   54,   27,   55,  135,
   86,   54,   27,   55,   24,   25,   56,  165,   82,   56,
   73,   73,   71,  119,   56,   51,  129,  120,  120,   76,
   81,   51,   76,   36,   37,   99,   76,   54,   54,   55,
   55,   99,   54,   42,   55,   87,   76,   98,   76,   42,
   98,   13,   98,   97,   13,   97,   97,   13,  122,   52,
   99,   99,  123,   54,   27,   88,  102,  106,  107,  108,
  109,  110,  111,  116,  117,  118,  128,   54,   52,  147,
    1,  146,  161,  162,  163,  164,  169,  170,   55,   99,
   99,   18,   99,   99,   99,   37,   45,    9,   79,   80,
  157,   99,  139,   58,  115,  134,  133,  100,  101,   72,
};
short yycheck[] = {                                      13,
    4,    0,    1,   50,   50,   19,   51,    1,   41,   51,
   52,   51,   52,   50,  138,  280,  277,  280,  279,  284,
  281,  277,  285,  281,  279,  281,   73,   73,  286,   23,
  295,  292,   31,  294,  295,  296,  291,  292,  294,   86,
  296,  165,   41,   42,  277,  295,  307,   51,  303,  277,
  305,  279,  292,  281,  281,   97,   96,  281,   72,  101,
  100,  294,  289,  296,  292,  102,  294,  295,  296,  116,
  280,   85,  118,  106,  277,  108,  109,  277,  281,  307,
  120,  123,   86,  128,  277,  279,  279,  277,  281,  278,
  292,  294,  295,  296,   98,  284,  110,  291,  292,  292,
  278,  294,  295,  296,  151,  278,  284,  153,  281,  303,
  155,  284,  286,  146,  307,  162,  277,  163,  279,  277,
  281,  279,  126,  281,  277,  139,  279,  286,  281,  281,
  282,  292,  284,  294,  295,  296,  294,  295,  296,  292,
  285,  294,  295,  296,  287,  288,  307,  161,  147,  307,
  277,  277,  292,  280,  307,  278,  282,  284,  284,  277,
  292,  284,  280,  283,  284,  278,  284,  294,  294,  296,
  296,  284,  294,  277,  296,  282,  294,  281,  296,  277,
  284,  278,  286,  281,  281,  283,  284,  284,  280,  281,
  283,  284,  284,  294,  295,  284,  284,  283,  278,  284,
  283,  278,  284,  284,  278,  284,  290,  294,  281,  277,
  279,  283,  278,  284,  284,  280,  278,  278,  296,    0,
  280,  280,  286,  278,  282,  282,  278,  278,  278,  278,
  147,  279,  111,   36,   88,  108,  106,   52,   52,   37,
};
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 338
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
"A_IDIV","A_MOD","A_EXP","U_MINUS","V_TRUE","V_FALSE","T_BAR","T_LPAR","T_RPAR",
"T_LBRA","T_RBRA","T_LSQB","T_RSQB","T_ASSIGN","T_COMMA","T_COLON","T_SEMI",
"T_PP","T_MM","T_RA","T_DOTDOT","T_COMMENT","T_ID","T_EXID","T_INT","T_STRING",
"T_FLOAT","K_BACKWARD","K_CANCEL","K_ELSE","K_FOR","K_FORWARD","K_IF",
"K_INCLUDE","K_LOOP","K_MACRO","K_MODULE","K_NULL","K_OFF","K_ON",
"K_PALINDROME","K_PAUSE","K_PLAY","K_QUIT","K_REPEAT","K_RESUME","K_SEQUENCE",
"K_STEP","K_STOP","K_SUSPEND","K_THEN","K_UNTIL","K_WHILE","P_INTERRUPT",
"P_SYSTEM","P_ACK","P_MACRO","P_FOREGROUND","P_BACKGROUND","P_ERROR",
"P_MESSAGE","P_INFO","P_LINQ","P_SINQ","P_VINQ","P_LRESP","P_SRESP","P_VRESP",
"P_DATA",
};
char *yyrule[] = {
"$accept : start",
"start : top c_0",
"c_0 :",
"top : statement",
"top : macro",
"top : empty",
"macro : K_MACRO T_ID T_LPAR formal_s0 T_RPAR T_RA T_LPAR formal_s0 T_RPAR attributes_0 block",
"macro : K_MACRO T_ID T_LPAR formal_s0 T_RPAR attributes_0 block",
"formal_s0 : empty",
"formal_s0 : formal_s",
"formal_s : formal attributes_0",
"formal_s : formal_s T_COMMA formal attributes_0",
"formal : T_ID",
"formal : T_ID T_ASSIGN T_ID",
"formal : T_ID T_ASSIGN constant",
"formal : T_ID T_ASSIGN T_ID T_ASSIGN constant",
"block : T_LBRA statement_s0 T_RBRA",
"statement_s0 : empty",
"statement_s0 : statement_s",
"statement_s : statement",
"statement_s : statement_s statement",
"statement : block",
"statement : assignment attributes_0 T_SEMI",
"statement : function_call attributes_0 T_SEMI",
"statement : include",
"statement : comment",
"include : K_INCLUDE string",
"assignment : f_assignment",
"assignment : s_assignment",
"f_assignment : l_value_s T_ASSIGN function_call",
"s_assignment : l_value_s T_ASSIGN expression_s",
"s_assignment : T_ID T_PP",
"s_assignment : T_ID T_MM",
"attributes_0 : empty",
"attributes_0 : attributes",
"attributes : T_LSQB attribute_s0 T_RSQB",
"attribute_s0 : empty",
"attribute_s0 : attribute_s",
"attribute_s : attribute",
"attribute_s : attribute_s T_COMMA attribute",
"attribute : T_ID T_COLON string",
"attribute : T_ID T_COLON int",
"$$1 :",
"function_call : T_ID $$1 T_LPAR argument_s0 T_RPAR",
"argument_s0 : empty",
"argument_s0 : argument_s",
"argument_s : argument",
"argument_s : argument_s T_COMMA argument",
"argument : value",
"argument : T_ID T_ASSIGN value",
"value : constant",
"value : T_ID",
"comment : T_COMMENT",
"expression_s : expression",
"expression_s : expression_s T_COMMA expression",
"expression : constant",
"expression : r_value",
"expression : T_LPAR expression T_RPAR",
"constant : scalar",
"constant : tensor",
"constant : list",
"constant : string",
"constant : K_NULL",
"list : T_LBRA scalar_s T_RBRA",
"list : T_LBRA tensor_s T_RBRA",
"list : T_LBRA string_s T_RBRA",
"list : T_LBRA real T_DOTDOT real T_RBRA",
"list : T_LBRA real T_DOTDOT real T_COLON real T_RBRA",
"tensor_s : tensor",
"tensor_s : tensor_s tensor",
"tensor_s : tensor_s T_COMMA tensor",
"tensor : T_LSQB scalar_s T_RSQB",
"tensor : T_LSQB tensor_s T_RSQB",
"scalar_s : scalar",
"scalar_s : scalar_s scalar",
"scalar_s : scalar_s T_COMMA scalar",
"scalar : real",
"scalar : complex",
"scalar : quaternion",
"real : int",
"real : float",
"complex : T_LPAR int T_COMMA int T_RPAR",
"complex : T_LPAR float T_COMMA float T_RPAR",
"quaternion : T_LPAR int T_COMMA int T_COMMA int T_COMMA int T_RPAR",
"quaternion : T_LPAR float T_COMMA float T_COMMA float T_COMMA float T_RPAR",
"int : T_INT",
"float : T_FLOAT",
"string_s : string",
"string_s : string_s string",
"string_s : string_s T_COMMA string",
"string : T_STRING",
"id_s0 : empty",
"id_s0 : id_s",
"id_s : T_ID attributes_0",
"id_s : id_s T_COMMA T_ID attributes_0",
"l_value_s : l_value attributes_0",
"l_value_s : l_value_s T_COMMA l_value attributes_0",
"l_value : T_ID",
"r_value : T_ID",
"empty :",
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
#line 423 "net.yacc"


#include "netlex.c"
#line 433 "y.tab.c"
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
case 2:
#line 140 "net.yacc"
{ return (0); }
break;
case 6:
#line 155 "net.yacc"
{
		    ParseEndOfMacroDefinition();
		}
break;
case 7:
#line 161 "net.yacc"
{
		    ParseEndOfMacroDefinition();
		}
break;
case 40:
#line 258 "net.yacc"
{
			ParseStringAttribute(yyvsp[-2].s, yyvsp[0].s);
		    }
break;
case 41:
#line 264 "net.yacc"
{
			ParseIntAttribute(yyvsp[-2].s, yyvsp[0].i);
		    }
break;
case 42:
#line 274 "net.yacc"
{
	            ParseFunctionID(yyvsp[0].s);
	        }
break;
case 50:
#line 297 "net.yacc"
{
	            ParseArgument(yyvsp[0].s,0);
	        }
break;
case 51:
#line 301 "net.yacc"
{
	            ParseArgument(yyvsp[0].s,1);
	        }
break;
case 52:
#line 311 "net.yacc"
{
	            ParseComment(yyvsp[0].s);
	        }
break;
case 97:
#line 408 "net.yacc"
{
		    ParseLValue(yyvsp[0].s);
		}
break;
case 98:
#line 414 "net.yacc"
{
		    ParseRValue(yyvsp[0].s);
		}
break;
#line 638 "y.tab.c"
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
