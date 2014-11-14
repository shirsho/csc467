
#ifndef AST_H_
#define AST_H_ 1

#include <stdarg.h>

// Dummy node just so everything compiles, create your own node/nodes
//
// The code provided below is an example ONLY. You can use/modify it,
// but do not assume that it is correct or complete.
//
// There are many ways of making AST nodes. The approach below is an example
// of a descriminated union. If you choose to use C++, then I suggest looking
// into inheritance.

// forward declare
struct node_;
typedef struct node_ node;
extern node *ast;

typedef enum {
  UNKNOWN               = 0,

  SCOPE_NODE            = (1 << 0),
  
  EXPRESSION_NODE       = (1 << 2),
  UNARY_EXPRESSION_NODE = (1 << 2) | (1 << 3),
  BINARY_EXPRESSION_NODE= (1 << 2) | (1 << 4),
  INT_NODE              = (1 << 2) | (1 << 5), 
  FLOAT_NODE            = (1 << 2) | (1 << 6),
  IDENT_NODE            = (1 << 2) | (1 << 7),
  VAR_NODE              = (1 << 2) | (1 << 8),
  FUNCTION_NODE         = (1 << 2) | (1 << 9),
  CONSTRUCTOR_NODE      = (1 << 2) | (1 << 10),

  STATEMENT_NODE        = (1 << 1),
  IF_STATEMENT_NODE     = (1 << 1) | (1 << 11),
  WHILE_STATEMENT_NODE  = (1 << 1) | (1 << 12),
  ASSIGNMENT_NODE       = (1 << 1) | (1 << 13),
  NESTED_SCOPE_NODE     = (1 << 1) | (1 << 14),

  DECLARATION_NODE      = (1 << 15),
  DECLARATIONS_NODE     = (1 << 16),
  ARGUMENTS_NODE        = (1 << 17),
  ARGUMENTS_OPT_NODE    = (1 << 18),
  BOOL_NODE             = (1 << 19)
} node_kind;

struct node_ {

  // an example of tagging each node with a type
  node_kind kind;

  union {
    struct {
      node *left;   // declarations
      node *right;   // statements
    } scope_expr;
  
    struct {
      int op;     //operator
      node *right;    //expression
    } unary_expr;

    struct {
      int op;     //operator
      node *left;     //expression
      node *right;    //expression
    } binary_expr;

    struct {
      double val;    //float value
    } float_expr;

    struct {
      int val;      //int value
    } int_expr;

    struct {
      int val;      //bool value
    } bool_expr;

    struct {
      char* id;   //identifier
      int arr;    //array index
    } var_expr;

    struct {
      int constant;   //constant?
      int type;     //type
      char* id;     //identifier
      node *right;    //expression?
      int line;     //line number
    } declaration_expr;
  
    struct {
      node *if_comparison;	//if comparison
      node *if_statement;	//if statement
      node *else_statement;	//else statement
      int line;     //line number
    } if_expr;

    struct {
      node *left;  //statements
      node *right;  //statement
    } statement_expr;

    struct {
      node *left;  //variable
      node *right;   //value
      int line;   //line number
    } assign_expr;

    struct {
      int func;   //function
      node *arguments;   //arguments
    } func_expr;

    struct {
      int type;  //type
      node *right;   //arguments
    } construt_expr;

    struct {
      node *scope;   //scope
    } nest_scope_expr;

    struct {
      node *left;  //declarations
      node *right;  //declaration
    } declarations_expr;

    struct {
      node *left;  //arguments
      node *right;  //expression
    } arguments_expr;

    struct {
      node *argum;  //arguments
    } arguments_opt_expr;

    struct {
      node *expr;   //expression or variable
    } expression_expr;
  };
};

node *ast_allocate(node_kind type, ...);
void ast_free(node *ast);
void ast_print(node * ast);

#endif /* AST_H_ */
