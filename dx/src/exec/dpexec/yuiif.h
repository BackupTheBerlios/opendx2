#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

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


#endif /* not BISON_Y_TAB_H */
