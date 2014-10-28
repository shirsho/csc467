%{
/***********************************************************************
 * --YOUR GROUP INFO SHOULD GO HERE--
 * 
 *   Interface to the parser module for CSC467 course project.
 * 
 *   Phase 2: Implement context free grammar for source language, and
 *            parse tracing functionality.
 *   Phase 3: Construct the AST for the source language program.
 ***********************************************************************/

/***********************************************************************
 *  C Definitions and external declarations for this module.
 *
 *  Phase 3: Include ast.h if needed, and declarations for other global or
 *           external vars, functions etc. as needed.
 ***********************************************************************/

#include <string.h>
#include "common.h"
//#include "ast.h"
//#include "symbol.h"
//#include "semantic.h"
#define YYERROR_VERBOSE
#define yTRACE(x)    { if (traceParser) fprintf(traceFile, "%s\n\n", x); }

void yyerror(const char* s);    /* what to do in case of error      */
int yylex();              /* procedure for calling lexical analyzer */
extern int yyline;        /* variable holding current line number   */

enum {
  DP3 = 0, 
  LIT = 1, 
  RSQ = 2
};

%}

/***********************************************************************
 *  Yacc/Bison declarations.
 *  Phase 2:
 *    1. Add precedence declarations for operators (after %start declaration)
 *    2. If necessary, add %type declarations for some nonterminals
 *  Phase 3:
 *    1. Add fields to the union below to facilitate the construction of the
 *       AST (the two existing fields allow the lexical analyzer to pass back
 *       semantic info, so they shouldn't be touched).
 *    2. Add <type> modifiers to appropriate %token declarations (using the
 *       fields of the union) so that semantic information can by passed back
 *       by the scanner.
 *    3. Make the %type declarations for the language non-terminals, utilizing
 *       the fields of the union as well.
 ***********************************************************************/

%{
#define YYDEBUG 1
%}

// defines the yyval union
%union {
  int as_int;
  int as_vec;
  float as_float;
  char *as_str;
  int as_func;
}

%token          FLOAT_T
%token          INT_T
%token          BOOL_T
%token          CONST
%token          FALSE_C TRUE_C
%token          FUNC
%token          IF WHILE ELSE
%token          AND OR NEQ EQ LEQ GEQ

// links specific values of tokens to yyval
%token <as_vec>   VEC_T
%token <as_vec>   BVEC_T
%token <as_vec>   IVEC_T
%token <as_float> FLOAT_C
%token <as_int>   INT_C
%token <as_str>   ID

%left     OR
%left     AND
%left     EQ NEQ '<' LEQ '>' GEQ
%left     '+' '-'
%left     '*' '/'
%right    '^'
%left     '!' UMINUS

%start    program

%%

/***********************************************************************
 *  Yacc/Bison rules
 *  Phase 2:
 *    1. Replace grammar found here with something reflecting the source
 *       language grammar
 *    2. Implement the trace parser option of the compiler
 ***********************************************************************/

program
  : scope     {yTRACE("program -> scope");}
  ;

scope
  : '{'declarations statements '}'  {yTRACE("scope -> { declarations statements }");}
  ;

declarations
  : declarations declaration     {yTRACE("declarations -> declarations declaration");}
  |                              {yTRACE("declarations -> ");}
  ;

statements
  : statements statement      {yTRACE("statements -> statements statement");}
  |                           {yTRACE("statements -> ");}
  ;

declaration
  : type ID';'        {yTRACE("declaration -> type ID;");}
  | type ID '=' expression ';'    {yTRACE("declaration -> type ID = expression;");}
  | CONST type ID '=' expression ';'    {yTRACE("declaration -> const type ID = expression;");}
  |                             {yTRACE("declaration -> ");}
  ;

statement
  : variable '=' expression ';'     {yTRACE("statement -> variable = expression;");}
  | IF '(' expression ')' statement else_statement  {yTRACE("statement -> if (expression) statement else_statement");}
  | WHILE '(' expression ')' statement        {yTRACE("statement -> while (expression) statement");}
  | scope         {yTRACE("statement -> scope");}
  | ';'           {yTRACE("statement -> ;");}
  ;

else_statement
  : ELSE statement      {yTRACE("else_statement -> else statement");}
  |                     {yTRACE("else_statement -> ");}
  ;

type 
  : INT_T         {yTRACE("type -> int");}
  | IVEC_T        {if(yylval.as_vec == 1) {yTRACE("type -> ivec2")} 
                    else if(yylval.as_vec == 2) {yTRACE("type -> ivec3")}
                    else {yTRACE("type -> ivec4")};}
  | BOOL_T        {yTRACE("type -> bool");}
  | BVEC_T        {if(yylval.as_vec == 1) {yTRACE("type -> bvec2")} 
                    else if(yylval.as_vec == 2) {yTRACE("type -> bvec3")}
                    else {yTRACE("type -> bvec4")};}
  | FLOAT_T       {yTRACE("type -> float");}
  | VEC_T         {if(yylval.as_vec == 1) {yTRACE("type -> vec2")} 
                    else if(yylval.as_vec == 2) {yTRACE("type -> vec3")}
                    else {yTRACE("type -> vec4")};}
  ;

expression
  : constructor       {yTRACE("expression -> constructor");}
  | function          {yTRACE("expression -> function");}
  | INT_C             {yTRACE("expression -> INT_C");}
  | FLOAT_C           {yTRACE("expression -> FLOAT_C");}
  | variable          {yTRACE("expression -> variable");}
  | unary_op expression         {yTRACE("expression -> unary_op expression");}
  | expr1              {yTRACE("expression -> expr1");}
  | TRUE_C            {yTRACE("expression -> true");}
  | FALSE_C           {yTRACE("expression -> false");}
  | '('expression')'  {yTRACE("expression -> (expression)");}
  ;

variable
  : ID                {yTRACE("variable -> ID");}
  | ID '['INT_C']'    {yTRACE("variable -> ID [INT_C]");}
  ;

unary_op
  : '!'         {yTRACE("unary_op -> !");}
  | '-'         {yTRACE("unary_op -> -");}
  ;

expr1
  : expr2 OR expr2          {yTRACE("expr1 -> expr2 || expr2");}
  | expr2                   {yTRACE("expr1 -> expr2");}
  ;

expr2
  : expr3 AND expr3         {yTRACE("expr2 -> expr3 && expr3");}
  | expr3                   {yTRACE("expr2 -> expr3");}
  ;

expr3
  : expr4 EQ expr4          {yTRACE("expr3 -> expr4 == expr4");}
  | expr4 LEQ expr4         {yTRACE("expr3 -> expr4 <= expr4");}
  | expr4 '<' expr4         {yTRACE("expr3 -> expr4 < expr4");}
  | expr4 GEQ expr4         {yTRACE("expr3 -> expr4 >= expr4");}
  | expr4 '>' expr4         {yTRACE("expr3 -> expr4 > expr4");}
  | expr4 NEQ expr4         {yTRACE("expr3 -> expr4 != expr4");}
  | expr4                   {yTRACE("expr3 -> expr4");}
  ;

expr4
  : term '+' term           {yTRACE("expr4 -> term + term");}
  | term '-' term           {yTRACE("expr4 -> term - term");}
  | term                    {yTRACE("expr4 -> term");}
  ;

term
  : factor '*' factor       {yTRACE("term -> factor * factor");}
  | factor '/' factor       {yTRACE("term -> factor / factor");}
  | factor                  {yTRACE("term -> factor");}
  ;

factor
  : expression '^' expression   {yTRACE("factor -> expression ^ expression");}
  | expression                  {yTRACE("factor -> expression");}
  ;

/*binary_op
  : AND         {yTRACE("binary_op -> &&");}
  | OR          {yTRACE("binary_op -> ||");}
  | EQ          {yTRACE("binary_op -> ==");}
  | NEQ         {yTRACE("binary_op -> !=");}
  | '<'         {yTRACE("binary_op -> <");}
  | LEQ         {yTRACE("binary_op -> <=");}
  | '>'         {yTRACE("binary_op -> >");}
  | GEQ         {yTRACE("binary_op -> >=");}
  | '+'         {yTRACE("binary_op -> +");}
  | '-'         {yTRACE("binary_op -> -");}
  | '*'         {yTRACE("binary_op -> *");}
  | '/'         {yTRACE("binary_op -> /");}
  | '^'         {yTRACE("binary_op -> ^");}
  ;
 */
 
constructor
  : type '(' arguments ')'    {yTRACE("constructor -> type(arguments)");}
  ;

function
  : function_name '(' arguments_opt ')'   {yTRACE("function -> function_name(arguments_opt)");}
  ;

function_name
  : FUNC       {if(yylval.as_func == 0) {yTRACE("function_name -> dp3")}
                else if(yylval.as_func == 1) {yTRACE("function_name -> lit")}
                else {yTRACE("function_name -> rsq")};}
  ;

arguments_opt
  : arguments       {yTRACE("arguments_opt -> arguments");}
  |                 {yTRACE("arguments_opt -> ");}
  ;

arguments
  : arguments ',' expression        {yTRACE("arguments -> arguments,expression");}
  | expression                      {yTRACE("arguments -> expression");}
  ;

%%

/***********************************************************************ol
 * Extra C code.
 *
 * The given yyerror function should not be touched. You may add helper
 * functions as necessary in subsequent phases.
 ***********************************************************************/
void yyerror(const char* s) {
  if(errorOccurred) {
    return;    /* Error has already been reported by scanner */
  } else {
    errorOccurred = 1;
  }

  fprintf(errorFile, "\nPARSER ERROR, LINE %d", yyline);
  
  if(strcmp(s, "parse error")) {
    if(strncmp(s, "parse error, ", 13)) {
      fprintf(errorFile, ": %s\n", s);
    } else {
      fprintf(errorFile, ": %s\n", s+13);
    }
  } else {
    fprintf(errorFile, ": Reading token %s\n", yytname[YYTRANSLATE(yychar)]);
  }
}

