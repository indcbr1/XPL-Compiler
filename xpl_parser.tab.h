#define tINTEGER 257
#define tFLOAT 258
#define tIDENTIFIER 259
#define tSTRING 260
#define tINTEGER_T 261
#define tREAL_T 262
#define tSTRING_T 263
#define tWHILE 264
#define tIF 265
#define tPRINTLN 266
#define tSTOP 267
#define tRETURN 268
#define tNEXT 269
#define tPROCEDURE_T 270
#define tUSE 271
#define tPUBLIC 272
#define tELSIF 273
#define tSWEEP 274
#define tNULL 275
#define tFROM 276
#define tTO 277
#define tAPPLY 278
#define tELSE 279
#define tEQ 280
#define tNE 281
#define tGE 282
#define tLE 283
#define tUNARY 284
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  int                   i;	/* integer value */
  double                d;      /* 8 byte float  */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;
  xpl::block_node      *block;
  basic_type      *type;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
