%{
/***********************************************************************
 * Justin Canton, 1000017910
 * Samprit Raihan, 998138830
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
#include "ast.h"
#include "symbol.h"
#include "semantic.h"

#define YYERROR_VERBOSE
#define yTRACE(x)    { if (traceParser) fprintf(traceFile, "%s\n", x); }

void yyerror(const char* s);    /* what to do in case of error            */
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
  node *as_ast;
}

%token          FLOAT_T
%token          INT_T
%token          BOOL_T
%token          CONST
%token          FALSE_C TRUE_C
%token          FUNC1 FUNC2 FUNC3
%token          IF ELSE
%token          AND OR NEQ EQ LEQ GEQ

// links specific values of tokens to yyval
%token <as_vec>   VEC_T
%token <as_vec>   BVEC_T
%token <as_vec>   IVEC_T
%token <as_float> FLOAT_C
%token <as_int>   INT_C
%token <as_str>   ID

// operator precedence
%left     OR                        // 7
%left     AND                       // 6
%left     EQ NEQ '<' LEQ '>' GEQ    // 5
%left     '+' '-'                   // 4
%left     '*' '/'                   // 3
%right    '^'                       // 2
%right    '!' UMINUS                // 1
%left     '(' '['                   // 0

// resolve dangling else shift/reduce conflict with associativity
%left     WITHOUT_ELSE
%left     WITH_ELSE

// type declarations
// TODO: fill this out
%type <as_ast> expression
%type <as_ast> program
%type <as_ast> scope
%type <as_ast> declaration
%type <as_ast> statement
%type <as_ast> declarations
%type <as_ast> statements
%type <as_int> type
%type <as_ast> variable
%type <as_ast> arguments
%type <as_ast> arguments_opt

// expect one shift/reduce conflict, where Bison chooses to shift
// the ELSE.
%expect 1

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
  : scope 
      { ast = $1;
        yTRACE("program -> scope\n");
        debug_printSymbolTable();
        semantic_check(ast, 0);}
  ;

scope
  : '{' {newScope();} declarations statements '}'
      { $$ = ast_allocate(SCOPE_NODE, $3, $4);
        yTRACE("scope -> { declarations statements }\n") }
  ;

declarations
  : declarations declaration
      { $$ = ast_allocate(DECLARATIONS_NODE, $1, $2);
        yTRACE("declarations -> declarations declaration\n") }
  | 
      { $$ = NULL;
        yTRACE("declarations -> \n") }
  ;

statements
  : statements statement
      { $$ = ast_allocate(STATEMENT_NODE, $1, $2);
        yTRACE("statements -> statements statement\n") }
  | 
      { $$ = NULL;
        yTRACE("statements -> \n") }
  ;

declaration
  : type ID ';' 
      { pushVar($2, $1, 0);
        $$ = ast_allocate(DECLARATION_NODE, $1, $2, NULL, -1, yyline);
        yTRACE("declaration -> type ID ;\n") }
  | type ID '=' expression ';'
      { pushVar($2, $1, 0);
        $$ = ast_allocate(DECLARATION_NODE, $1, $2, $4, -2, yyline);
        yTRACE("declaration -> type ID = expression ;\n") }
  | CONST type ID '=' expression ';'
      { pushVar($3, $2, 1);
        $$ = ast_allocate(DECLARATION_NODE, $2, $3, $5, CONST, yyline);
        yTRACE("declaration -> CONST type ID = expression ;\n") }
  ;

statement
  : variable '=' expression ';'
      { $$ = ast_allocate(ASSIGNMENT_NODE, $1, $3, yyline);
        yTRACE("statement -> variable = expression ;\n") }
  | IF '(' expression ')' statement ELSE statement %prec WITH_ELSE
      { $$ = ast_allocate(IF_STATEMENT_NODE, $3, $5, $7, yyline);
        yTRACE("statement -> IF ( expression ) statement ELSE statement \n") }
  | IF '(' expression ')' statement %prec WITHOUT_ELSE
      { $$ = ast_allocate(IF_STATEMENT_NODE, $3, $5, NULL, yyline);
        yTRACE("statement -> IF ( expression ) statement \n") }
  | scope 
      { $$ = ast_allocate(NESTED_SCOPE_NODE, $1, resetScope());
	      yTRACE("statement -> scope \n") }
  | ';'
      { yTRACE("statement -> ; \n") }
  ;

type
  : INT_T
      { $$ = 1;
        yTRACE("type -> INT_T \n") }
  | IVEC_T
      { $$ = 10 + yyval.as_vec;
        yTRACE("type -> IVEC_T \n") }
  | BOOL_T
      { $$ = 2;
        yTRACE("type -> BOOL_T \n") }
  | BVEC_T
      { $$ = 20 + yyval.as_vec;
        yTRACE("type -> BVEC_T \n") }
  | FLOAT_T
      { $$ = 3;
        yTRACE("type -> FLOAT_T \n") }
  | VEC_T
      { $$ = 30 + yyval.as_vec;
        yTRACE("type -> VEC_T \n") }
  ;

expression

  /* function-like operators */
  : type '(' arguments_opt ')' %prec '('
      { $$ = ast_allocate(CONSTRUCTOR_NODE, $1, $3);
        yTRACE("expression -> type ( arguments_opt ) \n") }
  | FUNC1 '(' arguments_opt ')' %prec '('
      { $$ = ast_allocate(FUNCTION_NODE, FUNC1, $3);
        yTRACE("expression -> FUNC ( arguments_opt ) \n") }
  | FUNC2 '(' arguments_opt ')' %prec '('
      { $$ = ast_allocate(FUNCTION_NODE, FUNC2, $3);
        yTRACE("expression -> FUNC ( arguments_opt ) \n") }
  | FUNC3 '(' arguments_opt ')' %prec '('
      { $$ = ast_allocate(FUNCTION_NODE, FUNC3, $3);
        yTRACE("expression -> FUNC ( arguments_opt ) \n") }

  /* unary opterators */
  | '-' expression %prec UMINUS
      { $$ = ast_allocate(UNARY_EXPRESSION_NODE, UMINUS, $2);
        yTRACE("expression -> - expression \n") }
  | '!' expression %prec '!'
      { $$ = ast_allocate(UNARY_EXPRESSION_NODE, '!', $2);
        yTRACE("expression -> ! expression \n") }

  /* binary operators */
  | expression AND expression %prec AND
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, AND, $1, $3);
        yTRACE("expression -> expression AND expression \n") }
  | expression OR expression %prec OR
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, OR, $1, $3);
        yTRACE("expression -> expression OR expression \n") }
  | expression EQ expression %prec EQ
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, EQ, $1, $3);
        yTRACE("expression -> expression EQ expression \n") }
  | expression NEQ expression %prec NEQ
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, NEQ, $1, $3);
        yTRACE("expression -> expression NEQ expression \n") }
  | expression '<' expression %prec '<'
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, '<', $1, $3);
        yTRACE("expression -> expression < expression \n") }
  | expression LEQ expression %prec LEQ
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, LEQ, $1, $3);
        yTRACE("expression -> expression LEQ expression \n") }
  | expression '>' expression %prec '>'
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, '>', $1, $3);
        yTRACE("expression -> expression > expression \n") }
  | expression GEQ expression %prec GEQ
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, GEQ, $1, $3);
        yTRACE("expression -> expression GEQ expression \n") }
  | expression '+' expression %prec '+'
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, '+', $1, $3);
        yTRACE("expression -> expression + expression \n") }
  | expression '-' expression %prec '-'
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, '-', $1, $3);
        yTRACE("expression -> expression - expression \n") }
  | expression '*' expression %prec '*'
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, '*', $1, $3);
        yTRACE("expression -> expression * expression \n") }
  | expression '/' expression %prec '/'
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, '/', $1, $3);
        yTRACE("expression -> expression / expression \n") }
  | expression '^' expression %prec '^'
      { $$ = ast_allocate(BINARY_EXPRESSION_NODE, '^', $1, $3);
        yTRACE("expression -> expression ^ expression \n") }

  /* literals */
  | TRUE_C
      { $$ = ast_allocate(BOOL_NODE, TRUE_C);
        yTRACE("expression -> TRUE_C \n") }
  | FALSE_C
      { $$ = ast_allocate(BOOL_NODE, FALSE_C);
        yTRACE("expression -> FALSE_C \n") }
  | INT_C
      { $$ = ast_allocate(INT_NODE, $1);
        yTRACE("expression -> INT_C \n") }
  | FLOAT_C
      { $$ = ast_allocate(FLOAT_NODE, $1);
        yTRACE("expression -> FLOAT_C \n") }

  /* misc */
  | '(' expression ')'
      { $$ = ast_allocate(EXPRESSION_NODE, $2);
        yTRACE("expression -> ( expression ) \n") }
  | variable 
      { $$ = ast_allocate(EXPRESSION_NODE, $1);
        yTRACE("expression -> variable \n") }
  ;

variable
  : ID
      { $$ = ast_allocate(VAR_NODE, $1, -1);
        yTRACE("variable -> ID \n") }
  | ID '[' INT_C ']' %prec '['
      { $$ = ast_allocate(VAR_NODE, $1, $3);
        yTRACE("variable -> ID [ INT_C ] \n") }
  ;

arguments
  : arguments ',' expression
      { $$ = ast_allocate(ARGUMENTS_NODE, $1, $3);
        yTRACE("arguments -> arguments , expression \n") }
  | expression
      { $$ = ast_allocate(ARGUMENTS_NODE, NULL, $1);
        yTRACE("arguments -> expression \n") }
  ;

arguments_opt
  : arguments
      { $$ = ast_allocate(ARGUMENTS_OPT_NODE, $1);
        yTRACE("arguments_opt -> arguments \n") }
  |
      { $$ = NULL;
        yTRACE("arguments_opt -> \n") }
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

