#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

#include "ast.h"
#include "common.h"
#include "parser.tab.h"

#define DEBUG_PRINT_TREE 0

node *ast = NULL;

node *ast_allocate(node_kind kind, ...) {
  va_list args;

  // make the node
  node *ast = (node *) malloc(sizeof(node));
  memset(ast, 0, sizeof *ast);
  ast->kind = kind;

  va_start(args, kind); 

  switch(kind) {
  
  case SCOPE_NODE:
    ast->scope_expr.left = va_arg(args, node *);
    ast->scope_expr.right = va_arg(args, node *);
    break;

  case BINARY_EXPRESSION_NODE:
    ast->binary_expr.op = va_arg(args, int);
    ast->binary_expr.left = va_arg(args, node *);
    ast->binary_expr.right = va_arg(args, node *);
    break;

  case UNARY_EXPRESSION_NODE:
    ast->unary_expr.op = va_arg(args, int);
    ast->unary_expr.right = va_arg(args, node *);
    break;

  case INT_NODE:
    ast->int_expr.val = va_arg(args, int);
    break;

  case FLOAT_NODE:
    ast->float_expr.val = va_arg(args, double);
    break;

  case BOOL_NODE:
    ast->bool_expr.val = va_arg(args, int);
    break;

  case IDENT_NODE:
    ast->id_expr.type = va_arg(args, int);
    break;

  case VAR_NODE:
    ast->var_expr.id = va_arg(args, char*);
    break;

  case DECLARATION_NODE:
    ast->declaration_expr.type = va_arg(args, node *);
    ast->declaration_expr.id = va_arg(args, char*);
    ast->declaration_expr.right = va_arg(args, node *);
    ast->declaration_expr.constant = va_arg(args, int);
    break;

  case IF_STATEMENT_NODE:
    ast->if_expr.if_comparison = va_arg(args, node *);
    ast->if_expr.if_statement = va_arg(args, node *);
    ast->if_expr.else_statement = va_arg(args, node *);
    break;

  case STATEMENT_NODE:
    ast->statement_expr.left = va_arg(args, node *);
    ast->statement_expr.right = va_arg(args, node *);
    break;

  case ASSIGNMENT_NODE:
    ast->assign_expr.left = va_arg(args, node *);
    ast->assign_expr.right = va_arg(args, node *);
    break;

  case FUNCTION_NODE:
    ast->func_expr.func = va_arg(args, char*);
    ast->func_expr.arguments = va_arg(args, node *);
    break;

  case CONSTRUCTOR_NODE:
    ast->construt_expr.left = va_arg(args, node *);
    ast->construt_expr.right = va_arg(args, node *);
    break;

  case NESTED_SCOPE_NODE:
    ast->nest_scope_expr.scope = va_arg(args, node *);
    break;

  case DECLARATIONS_NODE:
    ast->declarations_expr.left = va_arg(args, node *);
    ast->declarations_expr.right = va_arg(args, node *);
    break;

  case ARGUMENTS_NODE:
    ast->arguments_expr.left = va_arg(args, node *);
    ast->arguments_expr.right = va_arg(args, node *);
    break;

  case ARGUMENTS_OPT_NODE:
    ast->arguments_opt_expr.argum = va_arg(args, node *);
    break;

  case EXPRESSION_NODE:
    ast->expression_expr.expr = va_arg(args, node *);
    break;

  default: break;
  }

  va_end(args);

  return ast;
}

void ast_free(node *ast) {

  switch(ast->kind) {
  
  case SCOPE_NODE:
    ast_free(ast->scope_expr.left);
    ast_free(ast->scope_expr.right);
    free(ast);
    break;

  case BINARY_EXPRESSION_NODE:
    ast_free(ast->binary_expr.left);
    ast_free(ast->binary_expr.right);
    free(ast);
    break;

  case UNARY_EXPRESSION_NODE:
    ast_free(ast->unary_expr.right);
    free(ast);
    break;

  case INT_NODE:
    free(ast);
    break;

  case FLOAT_NODE:
    free(ast);
    break;

  case BOOL_NODE:
    free(ast);
    break;

  case IDENT_NODE:
    free(ast);
    break;

  case VAR_NODE:
    free(ast);
    break;

  case DECLARATION_NODE:
    ast_free(ast->declaration_expr.type);
    ast_free(ast->declaration_expr.right);
    free(ast);
    break;

  case IF_STATEMENT_NODE:
    ast_free(ast->if_expr.if_comparison);
    ast_free(ast->if_expr.if_statement);
    ast_free(ast->if_expr.else_statement);
    free(ast);
    break;

  case STATEMENT_NODE:
    ast_free(ast->statement_expr.left);
    ast_free(ast->statement_expr.right);
    free(ast);
    break;

  case ASSIGNMENT_NODE:
    ast_free(ast->assign_expr.left);
    ast_free(ast->assign_expr.right);
    free(ast);
    break;

  case FUNCTION_NODE:
    ast_free(ast->func_expr.arguments);
    free(ast);
    break;

  case CONSTRUCTOR_NODE:
    ast_free(ast->construt_expr.left);
    ast_free(ast->construt_expr.right);
    free(ast);
    break;

  case NESTED_SCOPE_NODE:
    ast_free(ast->nest_scope_expr.scope);
    free(ast);
    break;

  case DECLARATIONS_NODE:
    ast_free(ast->declarations_expr.left);
    ast_free(ast->declarations_expr.right);
    free(ast);
    break;

  case ARGUMENTS_NODE:
    ast_free(ast->arguments_expr.left);
    ast_free(ast->arguments_expr.right);
    free(ast);
    break;

  case ARGUMENTS_OPT_NODE:
    ast_free(ast->arguments_opt_expr.argum);
    free(ast);
    break;

  case EXPRESSION_NODE:
    ast_free(ast->expression_expr.expr);
    free(ast);
    break;

  default: break;
  }
}

void ast_print(node * ast) {

}
