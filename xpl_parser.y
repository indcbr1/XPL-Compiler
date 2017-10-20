%{
// $Id: xpl_parser.y,v 1.10 2017/05/17 23:59:36 ist181271 Exp $
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}
 /*Remover cenas desnecessarias daqui*/
%union {
  int                   i;	/* integer value */
  double                d;      /* 8 byte float  */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;
  xpl::block_node      *block;
  basic_type      *type;
};

%token <i> tINTEGER
%token <d> tFLOAT
%token <s> tIDENTIFIER tSTRING
%token <type> tINTEGER_T tREAL_T tSTRING_T 
%token tWHILE tIF tPRINTLN tSTOP tRETURN tNEXT tPROCEDURE_T  tUSE tPUBLIC tELSIF tSWEEP tNULL tFROM tTO tAPPLY
    
%nonassoc ')'
%nonassoc tELSE tELSIF

%right '='
%nonassoc '|'
%nonassoc '&'
%nonassoc '~'
%left tEQ tNE
%left tGE tLE  '>' '<'
%left '+' '-'
%left '*' '/' '%' 
%nonassoc tUNARY  
%nonassoc '['
/*removed stmt from node and list from sequence!!!*/
%type <node> program iter instr if cond decl func var vardec blkvar
%type <sequence> args decls instrs vars exprs callargs blkvars
%type <expression> expr lit
%type <lvalue> lval
%type <type> vtype
%type <block> block
%type <s> str

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

/*program	: tBEGIN list tEND { compiler->ast(new xpl::program_node(LINE, $2)); }
	      ;
*/

/*
stmt : expr ';'                         { $$ = new xpl::evaluation_node(LINE, $1); }
 	   | tPRINT expr ';'                  { $$ = new xpl::print_node(LINE, $2); }
     | tREAD lval ';'                   { $$ = new xpl::read_node(LINE, $2); }
     | tWHILE '(' expr ')' stmt         { $$ = new xpl::while_node(LINE, $3, $5); }
     | tIF '(' expr ')' stmt %prec tIFX { $$ = new xpl::if_node(LINE, $3, $5); }
     | tIF '(' expr ')' stmt tELSE stmt { $$ = new xpl::if_else_node(LINE, $3, $5, $7); }
     | '{' list '}'                     { $$ = $2; } 
     ;
*/

/*
list : stmt	     { $$ = new cdk::sequence_node(LINE, $1); }
	   | list stmt { $$ = new cdk::sequence_node(LINE, $2, $1); }
	   ;
*/

/* Empty program: nil_node??? seems right */

program: decls      { compiler->ast($1); }
       |            { compiler->ast(new cdk::sequence_node(LINE)); }
       ;

decls : decls decl      { $$ = new cdk::sequence_node(LINE,$2,$1); }
      | decl            { $$ = new cdk::sequence_node(LINE,$1); }
      ;
       

decl : vardec ';'       { $$ = $1; }
     | func             { $$ = $1; }
     ;


vardec  : tPUBLIC vtype tIDENTIFIER           { $$= new xpl::variable_declaration_node(LINE,true,false,$2,$3,nullptr);   } 
        | tPUBLIC vtype tIDENTIFIER '=' expr  { $$= new xpl::variable_declaration_node(LINE,true,false,$2,$3,$5);     }
        | tUSE vtype tIDENTIFIER              { $$= new xpl::variable_declaration_node(LINE,false,true,$2,$3,nullptr);    }
        | blkvar                              { $$=$1; }
        ;



func : vtype tIDENTIFIER '(' args ')'                { $$ = new xpl::function_declaration_node(LINE,false,false,$1,$2,$4); }
     | tPROCEDURE_T tIDENTIFIER '(' args ')'         { $$ = new xpl::function_declaration_node(LINE,false,false,new basic_type(0,basic_type::TYPE_VOID),$2,$4); }
     | tPUBLIC vtype tIDENTIFIER '(' args ')'        { $$ = new xpl::function_declaration_node(LINE,true,false,$2,$3,$5); }
     | tPUBLIC tPROCEDURE_T tIDENTIFIER '(' args ')' { $$ = new xpl::function_declaration_node(LINE,true,false,new basic_type(0,basic_type::TYPE_VOID),$3,$5); }
     | tUSE vtype tIDENTIFIER '(' args ')'           { $$ = new xpl::function_declaration_node(LINE,false,true,$2,$3,$5); }
     | tUSE tPROCEDURE_T tIDENTIFIER '(' args ')'    { $$ = new xpl::function_declaration_node(LINE,false,true,new basic_type(0,basic_type::TYPE_VOID),$3,$5); } 
     | vtype tIDENTIFIER '(' args ')' block                 { $$ = new xpl::function_definition_node(LINE,false,$1,$2,$4,nullptr,$6); }
     | tPROCEDURE_T tIDENTIFIER '(' args ')' block          { $$ = new xpl::function_definition_node(LINE,false,new basic_type(0,basic_type::TYPE_VOID),$2,$4,nullptr,$6); }
     | tPUBLIC vtype tIDENTIFIER '(' args ')' block         { $$ = new xpl::function_definition_node(LINE,true,$2,$3,$5,nullptr,$7); }
     | tPUBLIC tPROCEDURE_T tIDENTIFIER '(' args ')' block  { $$ = new xpl::function_definition_node(LINE,true,new basic_type(0,basic_type::TYPE_VOID),$3,$5,nullptr,$7); }
     | vtype tIDENTIFIER '(' args ')' '=' lit  block                { $$ = new xpl::function_definition_node(LINE,false,$1,$2,$4,$7,$8); }
     | tPUBLIC vtype tIDENTIFIER '(' args ')' '=' lit  block        { $$ = new xpl::function_definition_node(LINE,true,$2,$3,$5,$8,$9); }
     ;


args : vars         { $$=$1; }
     |              { $$=new cdk::sequence_node(LINE); }
     ;
    
vars : vars ',' var { $$ = new cdk::sequence_node(LINE, $3, $1); }
     | var          { $$ = new cdk::sequence_node(LINE, $1); }
     ;
     

      


block : '{' blkvars instrs '}' { $$ = new xpl::block_node(LINE, $2, $3); }
      | '{' blkvars '}'        { $$ = new xpl::block_node(LINE, $2,new cdk::sequence_node(LINE)); }
      | '{' instrs '}'       { $$ = new xpl::block_node(LINE, new cdk::sequence_node(LINE), $2); }
      | '{' '}'              { $$ = new xpl::block_node(LINE, new cdk::sequence_node(LINE),new cdk::sequence_node(LINE)); }
      ;

blkvar: vtype tIDENTIFIER                   { $$= new xpl::variable_declaration_node(LINE,false,false,$1,$2,nullptr);   }
      | vtype tIDENTIFIER '=' expr          { $$= new xpl::variable_declaration_node(LINE,false,false,$1,$2,$4);   }
      ;
      
blkvars: blkvars blkvar ';' { $$ = new cdk::sequence_node(LINE, $2, $1); }
       | blkvar ';'         { $$ = new cdk::sequence_node(LINE, $1); }
       ;

      
instrs: instrs instr  { $$ = new cdk::sequence_node(LINE,$2,$1); }
      | instr         { $$ = new cdk::sequence_node(LINE,$1); }
      ;
      


instr : expr ';'      { $$ = new xpl::evaluation_node(LINE,$1); }
      | expr '!'      { $$ = new xpl::print_node(LINE,$1,false); }
      | expr tPRINTLN { $$ = new xpl::print_node(LINE,$1,true); }
      | tNEXT         { $$ = new xpl::next_node(LINE); }
      | tSTOP         { $$ = new xpl::stop_node(LINE); }
      | tRETURN       { $$ = new xpl::return_node(LINE); }
      | cond          { $$ = $1; }
      | iter          { $$ = $1; }
      | block         { $$ = $1; }
      | tFROM expr tTO expr tAPPLY tIDENTIFIER tTO tIDENTIFIER      { $$ = new xpl::pratic1_node(LINE,$2,$4,$6,$8); }
      ;

cond  : tIF if { $$ = $2; }
      ;
      
if    : '(' expr ')' instr tELSIF if   { $$ = new xpl::if_else_node(LINE, $2, $4, $6); }
      | '(' expr ')' instr tELSE instr { $$ = new xpl::if_else_node(LINE, $2, $4, $6); }
      | '(' expr ')' instr   { $$ = new xpl::if_node(LINE,$2,$4); }
      ;
      

      
iter  : tWHILE '(' expr ')' instr                                { $$ = new xpl::while_node(LINE,$3,$5); }
      | tSWEEP '+' '(' lval ':' expr ':' expr ':' expr ')' instr   { $$ = new xpl::sweep_up_node(LINE,$4,$6,$8,$10,$12); }
      | tSWEEP '+' '(' lval ':' expr ':' expr ')' instr            { $$ = new xpl::sweep_up_node(LINE,$4,$6,$8,new cdk::integer_node(LINE,1),$10); }
      | tSWEEP '-' '(' lval ':' expr ':' expr ':' expr ')' instr { $$ = new xpl::sweep_down_node(LINE,$4,$6,$8,$10,$12); }
      | tSWEEP '-' '(' lval ':' expr ':' expr ')' instr          { $$ = new xpl::sweep_down_node(LINE,$4,$6,$8,new cdk::integer_node(LINE,1),$10); }
      ;


     
var  : vtype tIDENTIFIER    { $$ = new xpl::variable_declaration_node(LINE,false,false,$1,$2,nullptr); }
     ;

vtype: tINTEGER_T           { $$ = new basic_type(4,basic_type::TYPE_INT); }
     | tREAL_T              { $$ = new basic_type(8,basic_type::TYPE_DOUBLE); }
     | tSTRING_T            { $$ = new basic_type(4,basic_type::TYPE_STRING); }
     | '[' vtype ']'        { $$ = new basic_type(4,basic_type::TYPE_POINTER); $$->_subtype=$2;  }
     ;
     

lit  : tINTEGER                  { $$ = new cdk::integer_node(LINE, $1); }
     | tFLOAT                    { $$ = new cdk::double_node(LINE,$1); } //new
     | str                       { $$ = new cdk::string_node(LINE, $1); }
     | tNULL                     { $$ = new xpl::null_node(LINE); } //new
     ;

expr : lit                       { $$=$1; }
     | '-' expr %prec tUNARY     { $$ = new cdk::neg_node(LINE, $2); }
     | '+' expr %prec tUNARY     { $$ = new xpl::identity_node(LINE,$2); } //new
     | expr '+' expr	         { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr	         { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr	         { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr	         { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr	         { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr	         { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr	         { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tGE expr	         { $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr             { $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tNE expr	         { $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr tEQ expr	         { $$ = new cdk::eq_node(LINE, $1, $3); }
     | '(' expr ')'              { $$ = $2; }
     | lval                      { $$ = new cdk::rvalue_node(LINE, $1); }  
     | lval '=' expr             { $$ = new cdk::assignment_node(LINE, $1, $3); }
     | lval '?'                  { $$ = new xpl::address_of_node(LINE,$1); } //new
     | '~'  expr                 { $$ = new cdk::not_node(LINE, $2); } //new
     | expr '|' expr             { $$ = new cdk::or_node(LINE, $1,$3); } //new
     | expr '&' expr             { $$ = new cdk::and_node(LINE,$1,$3); } //new
     | '@'                       { $$ = new xpl::read_node(LINE); } //new
     | '[' expr ']'              { $$ = new xpl::memory_reservation_node(LINE, $2); } //new
     | tIDENTIFIER '(' callargs ')'  { $$ = new xpl::function_call_node(LINE, $1, $3); } //new
     ;
     
str  : str tSTRING              { $$ = new std::string(*$1+*$2); delete $1; delete $2; } 
     | tSTRING                  { $$ =$1; }
     ;

callargs: exprs                 { $$ = $1; } 
        |                       { $$=new cdk::sequence_node(LINE); }
        ;
     
exprs: expr ',' exprs            { $$ = new cdk::sequence_node(LINE, $1, $3); }
     | expr                      { $$ = new cdk::sequence_node(LINE, $1); }
     ;

lval : tIDENTIFIER             { $$ = new cdk::identifier_node(LINE, $1); }
     | expr '[' expr ']'       { $$ = new xpl::index_node(LINE,$1,$3);} //new
     ;

%%
