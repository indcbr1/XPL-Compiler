%option c++ yyclass="xpl_scanner" outfile="xpl_scanner.cpp"
%option stack noyywrap yylineno 8bit debug
%{ 
/* $Id: xpl_scanner.l,v 1.7 2017/05/21 23:47:56 ist181271 Exp $ */
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include "xpl_scanner.h"
#include "xpl_parser.tab.h"

// don't change this
#define yyerror LexerError
%}
%x X_STRING X_COMMENT X_STR_IGN
%%
                      // { set_debug(1); } //NEW, AND ADDED "debug" TO OPTIONS

"//".*                 ; /* ignore comments */

"/*"                   yy_push_state(X_COMMENT); /* Allow for nested comments */
<X_COMMENT>"/*"        yy_push_state(X_COMMENT);
<X_COMMENT>"*/"        yy_pop_state();            
<X_COMMENT>.           ; /* ignore comments */
<X_COMMENT>\n          ; /* ignore comments */


"procedure"            return tPROCEDURE_T;
"int"                  return tINTEGER_T;
"real"                 return tREAL_T;
"string"               return tSTRING_T;
">="                   return tGE; 

"public"               return tPUBLIC;
"use"                  return tUSE;

"<="                   return tLE; 
"=="                   return tEQ; 
"!="                   return tNE; 
"!!"                   return tPRINTLN;
"from"                 return tFROM;
"to"                   return tTO;
"apply"                return tAPPLY;
"while"                return tWHILE; 
"if"                   return tIF; 
"else"                 return tELSE;
"elsif"                return tELSIF;
"sweep"                return tSWEEP;
"next"                 return tNEXT;
"stop"                 return tSTOP;
"return"               return tRETURN;
"null"                 return tNULL;



[A-Za-z_][A-Za-z0-9_]*  yylval.s = new std::string(yytext); return tIDENTIFIER;

\"                     yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\\0          yy_pop_state();  yy_push_state(X_STR_IGN);
<X_STRING>\"           yy_pop_state(); return tSTRING;
<X_STRING>\\\"         *yylval.s += "\"";
<X_STRING>\\\\         *yylval.s += "\\";
<X_STRING>\\n          *yylval.s += "\n";
<X_STRING>\\r          *yylval.s += "\r";
<X_STRING>\\t          *yylval.s += "\t";
<X_STRING>\\[0-9a-fA-F]([0-9a-fA-F])? *yylval.s += std::string(1,strtol(yytext+1,nullptr,16));   /*if(errno == ERANGE) yyerror("Overflow ocurred while converting to ASCII character");*/
<X_STRING>.|\n         *yylval.s += yytext;

<X_STR_IGN>\"           yy_pop_state(); return tSTRING;
<X_STR_IGN>\\\"         ;
<X_STR_IGN>\\\\         ;
<X_STR_IGN>.|\n         ;

[1-9][0-9]*|0           yylval.i = strtol(yytext, nullptr, 10); if(errno == ERANGE) yyerror("Overflow ocurred while converting to Integer"); return tINTEGER;

"0"[xX][A-Fa-f1-9][A-Fa-f0-9]*       yylval.i = strtol(yytext+2, nullptr, 16); if(errno == ERANGE) yyerror("Overflow ocurred while converting to Integer"); return tINTEGER;

("."[0-9]+|[0-9]+"."|[0-9]+"."[0-9]+)([eE][+-]?[0-9]+)?|[0-9]+[eE][+-]?[0-9]+     yylval.d = strtod(yytext,nullptr); if(errno == ERANGE) yyerror("Overflow ocurred while converting to Float"); return tFLOAT;

[-\[\]:~&,|?!@()<>=+*/%;{}.]       return *yytext; //Added brackets, not, and, or, addressof,print, read, :, comma!

[ \t\n]+               ; /* ignore whitespace */

.                      yyerror("Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int xpl_scanner::yywrap() { return 1; }
