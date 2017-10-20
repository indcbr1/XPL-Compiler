/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20150711

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "xpl_parser.y"
/* $Id: xpl_parser.y,v 1.10 2017/05/17 23:59:36 ist181271 Exp $*/
/*-- don't change *any* of these: if you do, you'll break the compiler.*/
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
/*-- don't change *any* of these --- END!*/
#line 14 "xpl_parser.y"
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
#line 55 "xpl_parser.y"
/*-- The rules below will be included in yyparse, the main parsing function.*/
#line 53 "xpl_parser.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

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
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,   11,   11,    5,    5,    8,    8,    8,    8,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    6,    6,   10,   10,   13,   13,   21,   21,   21,   21,
    9,    9,   16,   16,   12,   12,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    4,    3,    3,    3,
    1,    1,    1,    1,    1,    7,   20,   20,   20,   20,
   18,   18,   18,   18,   17,   17,   17,   17,   17,   17,
   17,   17,   17,   17,   17,   17,   17,   17,   17,   17,
   17,   17,   17,   17,   17,   17,   17,   17,   22,   22,
   15,   15,   14,   14,   19,   19,
};
static const YYINT yylen[] = {                            2,
    1,    0,    2,    1,    2,    1,    3,    5,    3,    1,
    5,    5,    6,    6,    6,    6,    6,    6,    7,    7,
    8,    9,    1,    0,    3,    1,    4,    3,    3,    2,
    2,    4,    3,    2,    2,    1,    2,    2,    2,    1,
    1,    1,    1,    1,    1,    8,    2,    6,    6,    4,
    5,   12,   10,   12,   10,    2,    1,    1,    1,    3,
    1,    1,    1,    1,    1,    2,    2,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    1,
    3,    2,    2,    3,    3,    1,    3,    4,    2,    1,
    1,    0,    3,    1,    1,    4,
};
static const YYINT yydefred[] = {                         0,
   57,   58,   59,    0,    0,    0,    0,    0,    4,    6,
    0,   10,    0,    0,    0,    0,    0,    0,    0,    0,
    5,    3,    0,    0,    0,    0,    0,    0,   60,    0,
    0,   26,    0,    0,    0,    0,    0,    0,    0,    0,
   61,   62,    0,   90,   64,    0,    0,    0,    0,    0,
   86,    0,   65,    0,    0,    0,    0,    0,   56,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   82,   89,    0,    0,   18,
   25,   16,   15,    0,    0,   91,    0,    0,   87,   79,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   17,    0,    0,   41,
   42,   40,    0,    0,    0,   30,   44,   36,   43,    0,
    0,    0,    0,    0,   45,   20,    0,   19,   88,    0,
   96,    0,    0,    0,   47,    0,    0,    0,   34,   29,
   35,   28,    0,    0,   39,   37,   38,    0,    0,   93,
   21,    0,    0,    0,    0,    0,   33,   27,   22,    0,
    0,    0,    0,    0,    0,   51,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   48,   49,    0,    0,    0,
    0,    0,   46,    0,    0,    0,    0,   53,    0,   55,
    0,    0,    0,   52,   54,
};
static const YYINT yydgoto[] = {                          8,
  127,  128,  145,  129,    9,   10,   32,   11,   12,   33,
   13,  131,   34,   96,   97,  132,  133,   53,   54,   35,
  135,   55,
};
static const YYINT yysindex[] = {                       -51,
    0,    0,    0, -259,  -70,  -67,  -48,    0,    0,    0,
  -33,    0,  -51, -256,   -2, -218, -210, -206, -205,  -36,
    0,    0,  -31,  -48,   32,   33,   35,  -17,    0, 1291,
  -48,    0,   17,   37, -165,  -48,  -48,  -48, 1291,  -48,
    0,    0,   61,    0,    0, 1291, 1291, 1291, 1291, 1291,
    0,  981,    0,  -34, -158,   62,  -10,  -48,    0,   73,
   74,   79,  981,   83, 1291, 1023,   34,   34,  767,  793,
 1291, 1291, 1291, 1291, 1291, 1291, 1291, 1291, 1291, 1291,
 1291, 1291, 1291, 1291, 1291,    0,    0,  -56, 1104,    0,
    0,    0,    0,  -10,  -53,    0,   90,  648,    0,    0,
  139, 1023, 1047, 1047,    5,    5,    5,    5,   70,   70,
   34,   34,   34,  819,  981, -189,    0,   95,  100,    0,
    0,    0,   -6, 1291, 1251,    0,    0,    0,    0,   89,
 1156, 1126,  461, -110,    0,    0, -189,    0,    0, 1291,
    0,  -10, 1291, 1291,    0,  112,  119,  676,    0,    0,
    0,    0,   94, 1176,    0,    0,    0,  101,  -10,    0,
    0,  830,  877, 1291, 1291, 1291,    0,    0,    0, 1226,
 1226,  981,   58,   75,  851,    0, -251, 1291, 1291,  -96,
  100, 1226,  903,  929, -113,    0,    0, 1291, 1291,  -93,
  621,  728,    0, 1226, 1291, 1226, 1291,    0,  943,    0,
  955, 1226, 1226,    0,    0,
};
static const YYINT yyrindex[] = {                       167,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  168,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  110,  133,    0,  120,    0,  121,    0,    0,
  133,    0,    0,  142,    0,  133,  133,  133,    0,  133,
    0,    0,  -27,    0,    0,    0,    0,    0,    0,    0,
    0,  126,    0,   46,   18,    0,    1,    0,    0,    0,
    0,    0,  128,    0,   73,  911,   85,  113,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    4,    0,    0,
    0,    0,    0,    7,   19,    0,    0,   79,    0,    0,
 1062,   41,  515,  545,  164,  451,  474,  502,  395,  423,
  299,  339,  367,    0, 1082,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  110,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  995,  995,    0,    0, 1201,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0, 1011,    8,    0,  175,    0,  132,    0,  -87,  266,
    0,   66,    0,   64,    0,    0, 1457,  -91, -152,  228,
  150,    0,
};
#define YYTABLESIZE 1654
static const YYINT yytable[] = {                         15,
   12,  130,   23,   11,  116,   95,   14,  137,   31,   95,
   95,  173,  174,   95,   95,   95,   95,   95,   13,   95,
    7,  181,   40,    7,  142,   21,   85,  182,   86,   30,
   95,   95,   95,   95,   95,   95,  146,   24,  147,    7,
   25,   83,    7,   39,  153,  159,   81,   79,   26,   80,
   63,   82,   27,   28,   63,   63,   29,   57,   63,   63,
   63,   63,   63,   95,   63,   95,   89,   41,   42,   89,
   44,   36,   37,   85,   38,   63,   63,   63,   80,   63,
   58,   85,   80,   80,   85,   45,   80,   80,   80,   80,
   80,   12,   80,   59,   11,   84,   95,   14,   85,   85,
   65,   87,   88,   80,   80,   80,   83,   80,   63,   13,
   63,   81,   89,   92,   93,  178,   82,   67,   85,   94,
   86,   67,   67,   95,   84,   67,   67,   67,   67,   67,
  139,   67,  179,   85,  143,   85,   80,   86,   80,  144,
   63,   63,   67,   67,   67,   66,   67,  149,  158,   66,
   66,  164,  167,   66,   66,   66,   66,   66,  165,   66,
   84,   30,  185,  190,   85,  193,    2,    1,   31,   80,
   66,   66,   66,   24,   66,   83,   72,   67,    9,    7,
   81,   79,   23,   80,   32,   82,    8,   22,  186,   91,
    1,    2,    3,    1,    2,    3,   75,  154,   78,   16,
   77,   75,   18,  160,   75,   66,   90,   75,   67,    1,
    2,    3,    1,    2,    3,    0,    0,    0,    4,    5,
    6,   75,   75,   75,    0,   75,    0,   14,    0,   84,
    0,    0,   17,   19,   20,    0,   66,  117,   95,    0,
   14,    0,    0,  136,  138,    0,    0,    0,    0,   95,
   95,    0,   95,   95,   95,   95,   75,    0,    0,    0,
    0,   12,   12,   12,   11,   11,   11,   14,   14,   14,
   12,   12,   12,   11,   11,   11,   14,   14,   14,   13,
   13,   13,    0,   63,    0,    0,    0,   75,   13,   13,
   13,  161,    0,    0,   63,   63,   56,   63,   63,   63,
   63,   60,   61,   62,    0,   64,   85,    0,  169,    0,
    0,   80,    0,    0,    0,    0,  134,   85,   85,    0,
    0,    0,   80,   80,    0,   80,   80,   80,   80,    0,
    0,   70,    0,    0,    0,   70,   70,    0,    0,   70,
   70,   70,   70,   70,    0,   70,    0,    0,    0,    0,
   67,    0,   20,    0,    0,    0,   70,   70,   70,  134,
   70,   67,   67,    0,   67,   67,   67,   67,    0,    0,
    0,   71,    0,    0,    0,   71,   71,    0,   66,   71,
   71,   71,   71,   71,    0,   71,    0,    0,    0,   66,
   66,   70,   66,   66,   66,   66,   71,   71,   71,   72,
   71,    0,    0,   72,   72,    0,    0,   72,   72,   72,
   72,   72,    0,   72,    0,    0,    0,    0,   73,   74,
   75,   76,   70,    0,   72,   72,   72,   68,   72,   75,
    0,   71,   68,    0,    0,   68,    0,   68,   68,   68,
   75,   75,    0,   75,   75,   75,   75,    0,    0,    0,
    0,    0,   68,   68,   68,   69,   68,    0,    0,   72,
   69,    0,   71,   69,    0,   69,   69,   69,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   69,   69,   69,   76,   69,    0,    0,   68,   76,    0,
   72,   76,    0,  157,   76,    0,    0,   83,   72,    0,
    0,    0,   81,   79,    0,   80,   74,   82,   76,   76,
   76,   74,   76,    0,   74,   69,    0,   74,   68,  156,
   78,    0,   77,    0,    0,    0,    0,    0,    0,    0,
    0,   74,   74,   74,   73,   74,    0,    0,    0,   73,
    0,    0,   73,   76,    0,   73,   69,   78,    0,    0,
    0,   84,   78,    0,    0,   78,    0,    0,   78,   73,
   73,   73,    0,   73,   70,    0,   74,    0,    0,    0,
    0,    0,   78,   78,   76,   70,   70,   77,   70,   70,
   70,   70,   77,    0,   71,   77,    0,    0,   77,    0,
    0,    0,    0,    0,   73,    0,    0,   74,    0,    0,
    0,    0,   77,   77,   71,    0,    0,   78,    0,    0,
    0,    0,    0,    0,    0,   71,   71,    0,   71,   71,
   71,   71,    0,    0,    0,   73,    0,    0,    0,    0,
    0,    0,   72,    0,    0,    0,    0,   77,   78,    0,
    0,    0,    0,   72,   72,    0,   72,   72,   72,   72,
    0,    0,    0,    0,    0,    0,    0,   83,   72,    0,
   68,  194,   81,   79,    0,   80,    0,   82,   77,    0,
    0,   68,   68,    0,   68,   68,   68,   68,  195,    0,
   78,    0,   77,    0,   83,   72,    0,    0,   69,   81,
   79,  140,   80,    0,   82,    0,    0,    0,    0,   69,
   69,    0,   69,   69,   69,   69,    0,   78,    0,   77,
    0,   84,   83,   72,    0,    0,   76,   81,   79,    0,
   80,    0,   82,    0,    0,    0,  155,   76,   76,    0,
   76,   76,   76,   76,    0,   78,    0,   77,   84,   74,
   73,   74,   75,   76,   71,    0,    0,    0,    0,    0,
   74,   74,    0,   74,   74,   74,   74,    0,    0,    0,
    0,    0,    0,    0,   83,   72,   84,   73,  196,   81,
   79,   71,   80,    0,   82,    0,    0,    0,   73,   73,
   78,   73,   73,   73,   73,  197,    0,   78,    0,   77,
    0,   78,   78,    0,   78,   78,    0,    0,    0,   71,
    0,    0,    0,   83,   72,    0,    0,    0,   81,   79,
   77,   80,    0,   82,    0,    0,    0,    0,   84,    0,
    0,   77,   77,    0,   77,   77,   78,    0,   77,   83,
   72,    0,    0,  100,   81,   79,    0,   80,    0,   82,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   71,   78,    0,   77,   83,   72,   84,    0,   99,
   81,   79,    0,   80,    0,   82,   83,   72,    0,    0,
  170,   81,   79,    0,   80,    0,   82,    0,   78,    0,
   77,    0,    0,   84,    0,    0,    0,   83,   72,   78,
   71,   77,   81,   79,    0,   80,    0,   82,    0,    0,
   73,   74,   75,   76,    0,    0,    0,    0,    0,   84,
   78,  141,   77,   83,   72,    0,   71,  171,   81,   79,
   84,   80,    0,   82,    0,    0,    0,   73,   74,   75,
   76,    0,    0,    0,    0,    0,   78,    0,   77,   83,
   72,   84,   71,   83,   81,   79,    0,   80,   83,   82,
    0,   83,  166,   71,   83,   73,   74,   75,   76,    0,
  188,    0,   78,    0,   77,   83,   72,   84,   83,   83,
   81,   79,    0,   80,   71,   82,    0,    0,    0,   83,
   72,    0,    0,  202,   81,   79,  189,   80,   78,   82,
   77,   83,   72,   84,    0,  203,   81,   79,    0,   80,
   71,   82,   78,   83,   77,    0,    0,   73,   74,   75,
   76,    0,    0,    0,   78,    0,   77,   83,   72,   84,
    0,    0,   81,   79,    0,   80,   71,   82,    0,    0,
    0,   80,   80,   84,   83,    0,   80,   80,    0,   80,
   78,   80,   77,    0,    0,   84,   73,   74,   75,   76,
    0,    0,   71,    0,   80,    0,   80,    0,    0,   83,
    0,    0,    0,    0,   81,   79,   71,   80,    0,   82,
    0,   84,   73,   74,   75,   76,    0,    0,   71,    0,
    0,    0,   78,   83,   77,   80,    0,    0,   81,   79,
    0,   80,    0,   82,   84,    0,    0,    0,   73,   74,
   75,   76,   84,    0,   71,   84,   78,    0,   77,   73,
   74,   75,   76,   84,   81,    0,    0,    0,   80,   84,
   84,    0,   81,    0,    0,   81,    0,    0,  180,    0,
   73,   74,   75,   76,    0,    0,    0,   84,    0,   81,
   81,  151,    0,   50,    0,    0,   47,    0,   48,    0,
    0,    0,    0,    0,   84,    0,   73,   74,   75,   76,
    0,    0,    0,    0,  151,   50,    0,   51,   47,    0,
   48,    0,    0,    0,   81,    0,   83,    0,    0,    0,
  176,  177,   73,   74,   75,   76,    0,   83,   83,   51,
    0,    0,  187,    0,  125,   50,    0,    0,   47,    0,
   48,    0,    0,    0,  198,    0,  200,    0,   73,   74,
   75,   76,  204,  205,    0,   50,  125,    0,   47,   51,
   48,    0,   73,   74,   75,   76,   89,    0,  126,   46,
    0,    0,    0,    0,   73,   74,   75,   76,    0,   51,
   50,    0,    0,   50,    0,   50,   49,    0,   89,    0,
  152,   46,    0,    0,    0,    0,    0,    0,    0,    0,
   73,   74,   75,   76,   50,   50,   49,    0,   47,    0,
   48,    0,    0,    0,   80,   80,   80,   80,   89,    0,
  150,   46,    0,    0,    0,    0,    0,    0,    0,   51,
   50,   50,    0,   47,    0,   48,    0,    0,   89,    0,
  168,   46,   73,   74,   75,   76,    0,    0,    0,    0,
    0,    0,    0,    0,   51,    0,   49,    0,    0,    0,
    0,    0,    0,   50,    0,   50,   50,   84,   75,   76,
   50,    0,    0,   47,    0,   48,    0,    0,   84,   84,
    0,  125,    0,    0,    0,    0,    0,   81,   89,    0,
    0,   46,    0,    0,   51,    0,    0,    0,   81,   81,
   41,   42,   43,   44,    1,    2,    3,  118,  119,    0,
  120,  121,  122,    0,    0,    0,   46,  123,   45,  124,
    0,   49,   41,   42,   43,   44,    1,    2,    3,  118,
  119,    0,  120,  121,  122,    0,    0,    0,    0,  123,
   45,  124,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   41,   42,   43,   44,   46,    0,    0,  118,
  119,    0,  120,  121,  122,    0,    0,    0,    0,  123,
   45,  124,   41,   42,   43,   44,    0,    0,    0,  118,
  119,    0,  120,  121,  122,    0,    0,    0,    0,  123,
   45,  124,    0,    0,    0,    0,    0,   50,   50,   50,
   50,    0,    0,    0,   50,   50,    0,   50,   50,   50,
    0,    0,    0,    0,   50,   50,   50,    0,    0,    0,
    0,    0,   41,   42,   43,   44,   52,    0,    0,  118,
  119,    0,  120,  121,  122,   63,    0,    0,    0,  123,
   45,  124,   66,   67,   68,   69,   70,   41,   42,   43,
   44,    1,    2,    3,    0,    0,    0,    0,    0,    0,
    0,   98,    0,    0,    0,   45,    0,  101,  102,  103,
  104,  105,  106,  107,  108,  109,  110,  111,  112,  113,
  114,  115,    0,    0,    0,    0,    0,   41,   42,   43,
   44,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   45,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  148,   69,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   98,    0,    0,  162,
  163,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  172,  172,  175,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  183,  184,    0,    0,    0,    0,
    0,    0,    0,    0,  191,  192,    0,    0,    0,    0,
    0,  199,    0,  201,
};
static const YYINT yycheck[] = {                        259,
    0,   89,  259,    0,   61,   33,    0,   61,   40,   37,
   38,  164,  165,   41,   42,   43,   44,   45,    0,   47,
   91,  273,   40,   91,  116,   59,   61,  279,   63,   61,
   58,   59,   60,   61,   62,   63,   43,   40,   45,   91,
  259,   37,   91,   61,  132,  137,   42,   43,  259,   45,
   33,   47,  259,  259,   37,   38,   93,   41,   41,   42,
   43,   44,   45,   91,   47,   93,  123,  257,  258,  123,
  260,   40,   40,   33,   40,   58,   59,   60,   33,   62,
   44,   41,   37,   38,   44,  275,   41,   42,   43,   44,
   45,   91,   47,  259,   91,   91,  124,   91,   58,   59,
   40,  260,   41,   58,   59,   60,   37,   62,   91,   91,
   93,   42,  123,   41,   41,   58,   47,   33,   61,   41,
   63,   37,   38,   41,   91,   41,   42,   43,   44,   45,
   41,   47,   58,   93,   40,   61,   91,   63,   93,   40,
  123,  124,   58,   59,   60,   33,   62,   59,  259,   37,
   38,   40,   59,   41,   42,   43,   44,   45,   40,   47,
   91,   61,  259,  277,  124,  259,    0,    0,   59,  124,
   58,   59,   60,   41,   62,   37,   38,   93,   59,   59,
   42,   43,   41,   45,   59,   47,   59,   13,  181,   58,
  261,  262,  263,  261,  262,  263,   33,  132,   60,  270,
   62,   38,  270,  140,   41,   93,   57,   44,  124,  261,
  262,  263,  261,  262,  263,   -1,   -1,   -1,  270,  271,
  272,   58,   59,   60,   -1,   62,   -1,    0,   -1,   91,
   -1,   -1,    5,    6,    7,   -1,  124,   88,  266,   -1,
   13,   -1,   -1,   94,   95,   -1,   -1,   -1,   -1,  277,
  278,   -1,  280,  281,  282,  283,   93,   -1,   -1,   -1,
   -1,  261,  262,  263,  261,  262,  263,  261,  262,  263,
  270,  271,  272,  270,  271,  272,  270,  271,  272,  261,
  262,  263,   -1,  266,   -1,   -1,   -1,  124,  270,  271,
  272,  142,   -1,   -1,  277,  278,   31,  280,  281,  282,
  283,   36,   37,   38,   -1,   40,  266,   -1,  159,   -1,
   -1,  266,   -1,   -1,   -1,   -1,   89,  277,  278,   -1,
   -1,   -1,  277,  278,   -1,  280,  281,  282,  283,   -1,
   -1,   33,   -1,   -1,   -1,   37,   38,   -1,   -1,   41,
   42,   43,   44,   45,   -1,   47,   -1,   -1,   -1,   -1,
  266,   -1,  125,   -1,   -1,   -1,   58,   59,   60,  132,
   62,  277,  278,   -1,  280,  281,  282,  283,   -1,   -1,
   -1,   33,   -1,   -1,   -1,   37,   38,   -1,  266,   41,
   42,   43,   44,   45,   -1,   47,   -1,   -1,   -1,  277,
  278,   93,  280,  281,  282,  283,   58,   59,   60,   33,
   62,   -1,   -1,   37,   38,   -1,   -1,   41,   42,   43,
   44,   45,   -1,   47,   -1,   -1,   -1,   -1,  280,  281,
  282,  283,  124,   -1,   58,   59,   60,   33,   62,  266,
   -1,   93,   38,   -1,   -1,   41,   -1,   43,   44,   45,
  277,  278,   -1,  280,  281,  282,  283,   -1,   -1,   -1,
   -1,   -1,   58,   59,   60,   33,   62,   -1,   -1,   93,
   38,   -1,  124,   41,   -1,   43,   44,   45,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   58,   59,   60,   33,   62,   -1,   -1,   93,   38,   -1,
  124,   41,   -1,   33,   44,   -1,   -1,   37,   38,   -1,
   -1,   -1,   42,   43,   -1,   45,   33,   47,   58,   59,
   60,   38,   62,   -1,   41,   93,   -1,   44,  124,   59,
   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   58,   59,   60,   33,   62,   -1,   -1,   -1,   38,
   -1,   -1,   41,   93,   -1,   44,  124,   33,   -1,   -1,
   -1,   91,   38,   -1,   -1,   41,   -1,   -1,   44,   58,
   59,   60,   -1,   62,  266,   -1,   93,   -1,   -1,   -1,
   -1,   -1,   58,   59,  124,  277,  278,   33,  280,  281,
  282,  283,   38,   -1,  124,   41,   -1,   -1,   44,   -1,
   -1,   -1,   -1,   -1,   93,   -1,   -1,  124,   -1,   -1,
   -1,   -1,   58,   59,  266,   -1,   -1,   93,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  277,  278,   -1,  280,  281,
  282,  283,   -1,   -1,   -1,  124,   -1,   -1,   -1,   -1,
   -1,   -1,  266,   -1,   -1,   -1,   -1,   93,  124,   -1,
   -1,   -1,   -1,  277,  278,   -1,  280,  281,  282,  283,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   37,   38,   -1,
  266,   41,   42,   43,   -1,   45,   -1,   47,  124,   -1,
   -1,  277,  278,   -1,  280,  281,  282,  283,   58,   -1,
   60,   -1,   62,   -1,   37,   38,   -1,   -1,  266,   42,
   43,   44,   45,   -1,   47,   -1,   -1,   -1,   -1,  277,
  278,   -1,  280,  281,  282,  283,   -1,   60,   -1,   62,
   -1,   91,   37,   38,   -1,   -1,  266,   42,   43,   -1,
   45,   -1,   47,   -1,   -1,   -1,  266,  277,  278,   -1,
  280,  281,  282,  283,   -1,   60,   -1,   62,   91,  266,
  280,  281,  282,  283,  124,   -1,   -1,   -1,   -1,   -1,
  277,  278,   -1,  280,  281,  282,  283,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   37,   38,   91,  266,   41,   42,
   43,  124,   45,   -1,   47,   -1,   -1,   -1,  277,  278,
  266,  280,  281,  282,  283,   58,   -1,   60,   -1,   62,
   -1,  277,  278,   -1,  280,  281,   -1,   -1,   -1,  124,
   -1,   -1,   -1,   37,   38,   -1,   -1,   -1,   42,   43,
  266,   45,   -1,   47,   -1,   -1,   -1,   -1,   91,   -1,
   -1,  277,  278,   -1,  280,  281,   60,   -1,   62,   37,
   38,   -1,   -1,   41,   42,   43,   -1,   45,   -1,   47,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  124,   60,   -1,   62,   37,   38,   91,   -1,   93,
   42,   43,   -1,   45,   -1,   47,   37,   38,   -1,   -1,
   41,   42,   43,   -1,   45,   -1,   47,   -1,   60,   -1,
   62,   -1,   -1,   91,   -1,   -1,   -1,   37,   38,   60,
  124,   62,   42,   43,   -1,   45,   -1,   47,   -1,   -1,
  280,  281,  282,  283,   -1,   -1,   -1,   -1,   -1,   91,
   60,   93,   62,   37,   38,   -1,  124,   41,   42,   43,
   91,   45,   -1,   47,   -1,   -1,   -1,  280,  281,  282,
  283,   -1,   -1,   -1,   -1,   -1,   60,   -1,   62,   37,
   38,   91,  124,   33,   42,   43,   -1,   45,   38,   47,
   -1,   41,  277,  124,   44,  280,  281,  282,  283,   -1,
   58,   -1,   60,   -1,   62,   37,   38,   91,   58,   59,
   42,   43,   -1,   45,  124,   47,   -1,   -1,   -1,   37,
   38,   -1,   -1,   41,   42,   43,   58,   45,   60,   47,
   62,   37,   38,   91,   -1,   41,   42,   43,   -1,   45,
  124,   47,   60,   93,   62,   -1,   -1,  280,  281,  282,
  283,   -1,   -1,   -1,   60,   -1,   62,   37,   38,   91,
   -1,   -1,   42,   43,   -1,   45,  124,   47,   -1,   -1,
   -1,   37,   38,   91,  124,   -1,   42,   43,   -1,   45,
   60,   47,   62,   -1,   -1,   91,  280,  281,  282,  283,
   -1,   -1,  124,   -1,   60,   -1,   62,   -1,   -1,   37,
   -1,   -1,   -1,   -1,   42,   43,  124,   45,   -1,   47,
   -1,   91,  280,  281,  282,  283,   -1,   -1,  124,   -1,
   -1,   -1,   60,   37,   62,   91,   -1,   -1,   42,   43,
   -1,   45,   -1,   47,   33,   -1,   -1,   -1,  280,  281,
  282,  283,   41,   -1,  124,   44,   60,   -1,   62,  280,
  281,  282,  283,   91,   33,   -1,   -1,   -1,  124,   58,
   59,   -1,   41,   -1,   -1,   44,   -1,   -1,  278,   -1,
  280,  281,  282,  283,   -1,   -1,   -1,   91,   -1,   58,
   59,  131,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,
   -1,   -1,   -1,   -1,   93,   -1,  280,  281,  282,  283,
   -1,   -1,   -1,   -1,  154,   40,   -1,   64,   43,   -1,
   45,   -1,   -1,   -1,   93,   -1,  266,   -1,   -1,   -1,
  170,  171,  280,  281,  282,  283,   -1,  277,  278,   64,
   -1,   -1,  182,   -1,   91,   40,   -1,   -1,   43,   -1,
   45,   -1,   -1,   -1,  194,   -1,  196,   -1,  280,  281,
  282,  283,  202,  203,   -1,   40,   91,   -1,   43,   64,
   45,   -1,  280,  281,  282,  283,  123,   -1,  125,  126,
   -1,   -1,   -1,   -1,  280,  281,  282,  283,   -1,   64,
   40,   -1,   -1,   43,   -1,   45,   91,   -1,  123,   -1,
  125,  126,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  280,  281,  282,  283,   64,   40,   91,   -1,   43,   -1,
   45,   -1,   -1,   -1,  280,  281,  282,  283,  123,   -1,
  125,  126,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   64,
   40,   91,   -1,   43,   -1,   45,   -1,   -1,  123,   -1,
  125,  126,  280,  281,  282,  283,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   64,   -1,   91,   -1,   -1,   -1,
   -1,   -1,   -1,  123,   -1,  125,  126,  266,  282,  283,
   40,   -1,   -1,   43,   -1,   45,   -1,   -1,  277,  278,
   -1,   91,   -1,   -1,   -1,   -1,   -1,  266,  123,   -1,
   -1,  126,   -1,   -1,   64,   -1,   -1,   -1,  277,  278,
  257,  258,  259,  260,  261,  262,  263,  264,  265,   -1,
  267,  268,  269,   -1,   -1,   -1,  126,  274,  275,  276,
   -1,   91,  257,  258,  259,  260,  261,  262,  263,  264,
  265,   -1,  267,  268,  269,   -1,   -1,   -1,   -1,  274,
  275,  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  257,  258,  259,  260,  126,   -1,   -1,  264,
  265,   -1,  267,  268,  269,   -1,   -1,   -1,   -1,  274,
  275,  276,  257,  258,  259,  260,   -1,   -1,   -1,  264,
  265,   -1,  267,  268,  269,   -1,   -1,   -1,   -1,  274,
  275,  276,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
  260,   -1,   -1,   -1,  264,  265,   -1,  267,  268,  269,
   -1,   -1,   -1,   -1,  274,  275,  276,   -1,   -1,   -1,
   -1,   -1,  257,  258,  259,  260,   30,   -1,   -1,  264,
  265,   -1,  267,  268,  269,   39,   -1,   -1,   -1,  274,
  275,  276,   46,   47,   48,   49,   50,  257,  258,  259,
  260,  261,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   65,   -1,   -1,   -1,  275,   -1,   71,   72,   73,
   74,   75,   76,   77,   78,   79,   80,   81,   82,   83,
   84,   85,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
  260,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  275,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  124,  125,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  140,   -1,   -1,  143,
  144,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  164,  165,  166,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  178,  179,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  188,  189,   -1,   -1,   -1,   -1,
   -1,  195,   -1,  197,
};
#define YYFINAL 8
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 284
#define YYUNDFTOKEN 309
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,
0,0,0,0,0,"':'","';'","'<'","'='","'>'","'?'","'@'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"'{'","'|'","'}'","'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"tINTEGER","tFLOAT",
"tIDENTIFIER","tSTRING","tINTEGER_T","tREAL_T","tSTRING_T","tWHILE","tIF",
"tPRINTLN","tSTOP","tRETURN","tNEXT","tPROCEDURE_T","tUSE","tPUBLIC","tELSIF",
"tSWEEP","tNULL","tFROM","tTO","tAPPLY","tELSE","tEQ","tNE","tGE","tLE",
"tUNARY",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : decls",
"program :",
"decls : decls decl",
"decls : decl",
"decl : vardec ';'",
"decl : func",
"vardec : tPUBLIC vtype tIDENTIFIER",
"vardec : tPUBLIC vtype tIDENTIFIER '=' expr",
"vardec : tUSE vtype tIDENTIFIER",
"vardec : blkvar",
"func : vtype tIDENTIFIER '(' args ')'",
"func : tPROCEDURE_T tIDENTIFIER '(' args ')'",
"func : tPUBLIC vtype tIDENTIFIER '(' args ')'",
"func : tPUBLIC tPROCEDURE_T tIDENTIFIER '(' args ')'",
"func : tUSE vtype tIDENTIFIER '(' args ')'",
"func : tUSE tPROCEDURE_T tIDENTIFIER '(' args ')'",
"func : vtype tIDENTIFIER '(' args ')' block",
"func : tPROCEDURE_T tIDENTIFIER '(' args ')' block",
"func : tPUBLIC vtype tIDENTIFIER '(' args ')' block",
"func : tPUBLIC tPROCEDURE_T tIDENTIFIER '(' args ')' block",
"func : vtype tIDENTIFIER '(' args ')' '=' lit block",
"func : tPUBLIC vtype tIDENTIFIER '(' args ')' '=' lit block",
"args : vars",
"args :",
"vars : vars ',' var",
"vars : var",
"block : '{' blkvars instrs '}'",
"block : '{' blkvars '}'",
"block : '{' instrs '}'",
"block : '{' '}'",
"blkvar : vtype tIDENTIFIER",
"blkvar : vtype tIDENTIFIER '=' expr",
"blkvars : blkvars blkvar ';'",
"blkvars : blkvar ';'",
"instrs : instrs instr",
"instrs : instr",
"instr : expr ';'",
"instr : expr '!'",
"instr : expr tPRINTLN",
"instr : tNEXT",
"instr : tSTOP",
"instr : tRETURN",
"instr : cond",
"instr : iter",
"instr : block",
"instr : tFROM expr tTO expr tAPPLY tIDENTIFIER tTO tIDENTIFIER",
"cond : tIF if",
"if : '(' expr ')' instr tELSIF if",
"if : '(' expr ')' instr tELSE instr",
"if : '(' expr ')' instr",
"iter : tWHILE '(' expr ')' instr",
"iter : tSWEEP '+' '(' lval ':' expr ':' expr ':' expr ')' instr",
"iter : tSWEEP '+' '(' lval ':' expr ':' expr ')' instr",
"iter : tSWEEP '-' '(' lval ':' expr ':' expr ':' expr ')' instr",
"iter : tSWEEP '-' '(' lval ':' expr ':' expr ')' instr",
"var : vtype tIDENTIFIER",
"vtype : tINTEGER_T",
"vtype : tREAL_T",
"vtype : tSTRING_T",
"vtype : '[' vtype ']'",
"lit : tINTEGER",
"lit : tFLOAT",
"lit : str",
"lit : tNULL",
"expr : lit",
"expr : '-' expr",
"expr : '+' expr",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '%' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr tGE expr",
"expr : expr tLE expr",
"expr : expr tNE expr",
"expr : expr tEQ expr",
"expr : '(' expr ')'",
"expr : lval",
"expr : lval '=' expr",
"expr : lval '?'",
"expr : '~' expr",
"expr : expr '|' expr",
"expr : expr '&' expr",
"expr : '@'",
"expr : '[' expr ']'",
"expr : tIDENTIFIER '(' callargs ')'",
"str : str tSTRING",
"str : tSTRING",
"callargs : exprs",
"callargs :",
"exprs : expr ',' exprs",
"exprs : expr",
"lval : tIDENTIFIER",
"lval : expr '[' expr ']'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
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
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
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

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 82 "xpl_parser.y"
	{ compiler->ast(yystack.l_mark[0].sequence); }
break;
case 2:
#line 83 "xpl_parser.y"
	{ compiler->ast(new cdk::sequence_node(LINE)); }
break;
case 3:
#line 86 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node,yystack.l_mark[-1].sequence); }
break;
case 4:
#line 87 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node); }
break;
case 5:
#line 91 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[-1].node; }
break;
case 6:
#line 92 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 7:
#line 96 "xpl_parser.y"
	{ yyval.node= new xpl::variable_declaration_node(LINE,true,false,yystack.l_mark[-1].type,yystack.l_mark[0].s,nullptr);   }
break;
case 8:
#line 97 "xpl_parser.y"
	{ yyval.node= new xpl::variable_declaration_node(LINE,true,false,yystack.l_mark[-3].type,yystack.l_mark[-2].s,yystack.l_mark[0].expression);     }
break;
case 9:
#line 98 "xpl_parser.y"
	{ yyval.node= new xpl::variable_declaration_node(LINE,false,true,yystack.l_mark[-1].type,yystack.l_mark[0].s,nullptr);    }
break;
case 10:
#line 99 "xpl_parser.y"
	{ yyval.node=yystack.l_mark[0].node; }
break;
case 11:
#line 104 "xpl_parser.y"
	{ yyval.node = new xpl::function_declaration_node(LINE,false,false,yystack.l_mark[-4].type,yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 12:
#line 105 "xpl_parser.y"
	{ yyval.node = new xpl::function_declaration_node(LINE,false,false,new basic_type(0,basic_type::TYPE_VOID),yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 13:
#line 106 "xpl_parser.y"
	{ yyval.node = new xpl::function_declaration_node(LINE,true,false,yystack.l_mark[-4].type,yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 14:
#line 107 "xpl_parser.y"
	{ yyval.node = new xpl::function_declaration_node(LINE,true,false,new basic_type(0,basic_type::TYPE_VOID),yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 15:
#line 108 "xpl_parser.y"
	{ yyval.node = new xpl::function_declaration_node(LINE,false,true,yystack.l_mark[-4].type,yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 16:
#line 109 "xpl_parser.y"
	{ yyval.node = new xpl::function_declaration_node(LINE,false,true,new basic_type(0,basic_type::TYPE_VOID),yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 17:
#line 110 "xpl_parser.y"
	{ yyval.node = new xpl::function_definition_node(LINE,false,yystack.l_mark[-5].type,yystack.l_mark[-4].s,yystack.l_mark[-2].sequence,nullptr,yystack.l_mark[0].block); }
break;
case 18:
#line 111 "xpl_parser.y"
	{ yyval.node = new xpl::function_definition_node(LINE,false,new basic_type(0,basic_type::TYPE_VOID),yystack.l_mark[-4].s,yystack.l_mark[-2].sequence,nullptr,yystack.l_mark[0].block); }
break;
case 19:
#line 112 "xpl_parser.y"
	{ yyval.node = new xpl::function_definition_node(LINE,true,yystack.l_mark[-5].type,yystack.l_mark[-4].s,yystack.l_mark[-2].sequence,nullptr,yystack.l_mark[0].block); }
break;
case 20:
#line 113 "xpl_parser.y"
	{ yyval.node = new xpl::function_definition_node(LINE,true,new basic_type(0,basic_type::TYPE_VOID),yystack.l_mark[-4].s,yystack.l_mark[-2].sequence,nullptr,yystack.l_mark[0].block); }
break;
case 21:
#line 114 "xpl_parser.y"
	{ yyval.node = new xpl::function_definition_node(LINE,false,yystack.l_mark[-7].type,yystack.l_mark[-6].s,yystack.l_mark[-4].sequence,yystack.l_mark[-1].expression,yystack.l_mark[0].block); }
break;
case 22:
#line 115 "xpl_parser.y"
	{ yyval.node = new xpl::function_definition_node(LINE,true,yystack.l_mark[-7].type,yystack.l_mark[-6].s,yystack.l_mark[-4].sequence,yystack.l_mark[-1].expression,yystack.l_mark[0].block); }
break;
case 23:
#line 119 "xpl_parser.y"
	{ yyval.sequence=yystack.l_mark[0].sequence; }
break;
case 24:
#line 120 "xpl_parser.y"
	{ yyval.sequence=new cdk::sequence_node(LINE); }
break;
case 25:
#line 123 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-2].sequence); }
break;
case 26:
#line 124 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 27:
#line 131 "xpl_parser.y"
	{ yyval.block = new xpl::block_node(LINE, yystack.l_mark[-2].sequence, yystack.l_mark[-1].sequence); }
break;
case 28:
#line 132 "xpl_parser.y"
	{ yyval.block = new xpl::block_node(LINE, yystack.l_mark[-1].sequence,new cdk::sequence_node(LINE)); }
break;
case 29:
#line 133 "xpl_parser.y"
	{ yyval.block = new xpl::block_node(LINE, new cdk::sequence_node(LINE), yystack.l_mark[-1].sequence); }
break;
case 30:
#line 134 "xpl_parser.y"
	{ yyval.block = new xpl::block_node(LINE, new cdk::sequence_node(LINE),new cdk::sequence_node(LINE)); }
break;
case 31:
#line 137 "xpl_parser.y"
	{ yyval.node= new xpl::variable_declaration_node(LINE,false,false,yystack.l_mark[-1].type,yystack.l_mark[0].s,nullptr);   }
break;
case 32:
#line 138 "xpl_parser.y"
	{ yyval.node= new xpl::variable_declaration_node(LINE,false,false,yystack.l_mark[-3].type,yystack.l_mark[-2].s,yystack.l_mark[0].expression);   }
break;
case 33:
#line 141 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].node, yystack.l_mark[-2].sequence); }
break;
case 34:
#line 142 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].node); }
break;
case 35:
#line 146 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node,yystack.l_mark[-1].sequence); }
break;
case 36:
#line 147 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node); }
break;
case 37:
#line 152 "xpl_parser.y"
	{ yyval.node = new xpl::evaluation_node(LINE,yystack.l_mark[-1].expression); }
break;
case 38:
#line 153 "xpl_parser.y"
	{ yyval.node = new xpl::print_node(LINE,yystack.l_mark[-1].expression,false); }
break;
case 39:
#line 154 "xpl_parser.y"
	{ yyval.node = new xpl::print_node(LINE,yystack.l_mark[-1].expression,true); }
break;
case 40:
#line 155 "xpl_parser.y"
	{ yyval.node = new xpl::next_node(LINE); }
break;
case 41:
#line 156 "xpl_parser.y"
	{ yyval.node = new xpl::stop_node(LINE); }
break;
case 42:
#line 157 "xpl_parser.y"
	{ yyval.node = new xpl::return_node(LINE); }
break;
case 43:
#line 158 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 44:
#line 159 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 45:
#line 160 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].block; }
break;
case 46:
#line 161 "xpl_parser.y"
	{ yyval.node = new xpl::pratic1_node(LINE,yystack.l_mark[-6].expression,yystack.l_mark[-4].expression,yystack.l_mark[-2].s,yystack.l_mark[0].s); }
break;
case 47:
#line 164 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 48:
#line 167 "xpl_parser.y"
	{ yyval.node = new xpl::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].node, yystack.l_mark[0].node); }
break;
case 49:
#line 168 "xpl_parser.y"
	{ yyval.node = new xpl::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].node, yystack.l_mark[0].node); }
break;
case 50:
#line 169 "xpl_parser.y"
	{ yyval.node = new xpl::if_node(LINE,yystack.l_mark[-2].expression,yystack.l_mark[0].node); }
break;
case 51:
#line 174 "xpl_parser.y"
	{ yyval.node = new xpl::while_node(LINE,yystack.l_mark[-2].expression,yystack.l_mark[0].node); }
break;
case 52:
#line 175 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_up_node(LINE,yystack.l_mark[-8].lvalue,yystack.l_mark[-6].expression,yystack.l_mark[-4].expression,yystack.l_mark[-2].expression,yystack.l_mark[0].node); }
break;
case 53:
#line 176 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_up_node(LINE,yystack.l_mark[-6].lvalue,yystack.l_mark[-4].expression,yystack.l_mark[-2].expression,new cdk::integer_node(LINE,1),yystack.l_mark[0].node); }
break;
case 54:
#line 177 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_down_node(LINE,yystack.l_mark[-8].lvalue,yystack.l_mark[-6].expression,yystack.l_mark[-4].expression,yystack.l_mark[-2].expression,yystack.l_mark[0].node); }
break;
case 55:
#line 178 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_down_node(LINE,yystack.l_mark[-6].lvalue,yystack.l_mark[-4].expression,yystack.l_mark[-2].expression,new cdk::integer_node(LINE,1),yystack.l_mark[0].node); }
break;
case 56:
#line 183 "xpl_parser.y"
	{ yyval.node = new xpl::variable_declaration_node(LINE,false,false,yystack.l_mark[-1].type,yystack.l_mark[0].s,nullptr); }
break;
case 57:
#line 186 "xpl_parser.y"
	{ yyval.type = new basic_type(4,basic_type::TYPE_INT); }
break;
case 58:
#line 187 "xpl_parser.y"
	{ yyval.type = new basic_type(8,basic_type::TYPE_DOUBLE); }
break;
case 59:
#line 188 "xpl_parser.y"
	{ yyval.type = new basic_type(4,basic_type::TYPE_STRING); }
break;
case 60:
#line 189 "xpl_parser.y"
	{ yyval.type = new basic_type(4,basic_type::TYPE_POINTER); yyval.type->_subtype=yystack.l_mark[-1].type;  }
break;
case 61:
#line 193 "xpl_parser.y"
	{ yyval.expression = new cdk::integer_node(LINE, yystack.l_mark[0].i); }
break;
case 62:
#line 194 "xpl_parser.y"
	{ yyval.expression = new cdk::double_node(LINE,yystack.l_mark[0].d); }
break;
case 63:
#line 195 "xpl_parser.y"
	{ yyval.expression = new cdk::string_node(LINE, yystack.l_mark[0].s); }
break;
case 64:
#line 196 "xpl_parser.y"
	{ yyval.expression = new xpl::null_node(LINE); }
break;
case 65:
#line 199 "xpl_parser.y"
	{ yyval.expression=yystack.l_mark[0].expression; }
break;
case 66:
#line 200 "xpl_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 67:
#line 201 "xpl_parser.y"
	{ yyval.expression = new xpl::identity_node(LINE,yystack.l_mark[0].expression); }
break;
case 68:
#line 202 "xpl_parser.y"
	{ yyval.expression = new cdk::add_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 69:
#line 203 "xpl_parser.y"
	{ yyval.expression = new cdk::sub_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 70:
#line 204 "xpl_parser.y"
	{ yyval.expression = new cdk::mul_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 71:
#line 205 "xpl_parser.y"
	{ yyval.expression = new cdk::div_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 72:
#line 206 "xpl_parser.y"
	{ yyval.expression = new cdk::mod_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 73:
#line 207 "xpl_parser.y"
	{ yyval.expression = new cdk::lt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 74:
#line 208 "xpl_parser.y"
	{ yyval.expression = new cdk::gt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 75:
#line 209 "xpl_parser.y"
	{ yyval.expression = new cdk::ge_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 76:
#line 210 "xpl_parser.y"
	{ yyval.expression = new cdk::le_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 77:
#line 211 "xpl_parser.y"
	{ yyval.expression = new cdk::ne_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 78:
#line 212 "xpl_parser.y"
	{ yyval.expression = new cdk::eq_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 79:
#line 213 "xpl_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 80:
#line 214 "xpl_parser.y"
	{ yyval.expression = new cdk::rvalue_node(LINE, yystack.l_mark[0].lvalue); }
break;
case 81:
#line 215 "xpl_parser.y"
	{ yyval.expression = new cdk::assignment_node(LINE, yystack.l_mark[-2].lvalue, yystack.l_mark[0].expression); }
break;
case 82:
#line 216 "xpl_parser.y"
	{ yyval.expression = new xpl::address_of_node(LINE,yystack.l_mark[-1].lvalue); }
break;
case 83:
#line 217 "xpl_parser.y"
	{ yyval.expression = new cdk::not_node(LINE, yystack.l_mark[0].expression); }
break;
case 84:
#line 218 "xpl_parser.y"
	{ yyval.expression = new cdk::or_node(LINE, yystack.l_mark[-2].expression,yystack.l_mark[0].expression); }
break;
case 85:
#line 219 "xpl_parser.y"
	{ yyval.expression = new cdk::and_node(LINE,yystack.l_mark[-2].expression,yystack.l_mark[0].expression); }
break;
case 86:
#line 220 "xpl_parser.y"
	{ yyval.expression = new xpl::read_node(LINE); }
break;
case 87:
#line 221 "xpl_parser.y"
	{ yyval.expression = new xpl::memory_reservation_node(LINE, yystack.l_mark[-1].expression); }
break;
case 88:
#line 222 "xpl_parser.y"
	{ yyval.expression = new xpl::function_call_node(LINE, yystack.l_mark[-3].s, yystack.l_mark[-1].sequence); }
break;
case 89:
#line 225 "xpl_parser.y"
	{ yyval.s = new std::string(*yystack.l_mark[-1].s+*yystack.l_mark[0].s); delete yystack.l_mark[-1].s; delete yystack.l_mark[0].s; }
break;
case 90:
#line 226 "xpl_parser.y"
	{ yyval.s =yystack.l_mark[0].s; }
break;
case 91:
#line 229 "xpl_parser.y"
	{ yyval.sequence = yystack.l_mark[0].sequence; }
break;
case 92:
#line 230 "xpl_parser.y"
	{ yyval.sequence=new cdk::sequence_node(LINE); }
break;
case 93:
#line 233 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].sequence); }
break;
case 94:
#line 234 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression); }
break;
case 95:
#line 237 "xpl_parser.y"
	{ yyval.lvalue = new cdk::identifier_node(LINE, yystack.l_mark[0].s); }
break;
case 96:
#line 238 "xpl_parser.y"
	{ yyval.lvalue = new xpl::index_node(LINE,yystack.l_mark[-3].expression,yystack.l_mark[-1].expression);}
break;
#line 1299 "xpl_parser.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
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
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
