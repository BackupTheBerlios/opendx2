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
typedef union {
#define MAX_PARSE_STRING_SIZE 512
    char s[MAX_PARSE_STRING_SIZE];
    int i;
    float f;
    double d;
    PTreeNode *a;
} _CCSTYPE;
extern _CCSTYPE _dxfcclval;
