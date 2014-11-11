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
    if(ast->scope_expr.left != NULL)
      ast_free(ast->scope_expr.left);
    if(ast->scope_expr.right != NULL)
      ast_free(ast->scope_expr.right);
    free(ast);
    break;

  case BINARY_EXPRESSION_NODE:
    if(ast->binary_expr.left != NULL)
      ast_free(ast->binary_expr.left);
    if(ast->binary_expr.right != NULL)
      ast_free(ast->binary_expr.right);
    free(ast);
    break;

  case UNARY_EXPRESSION_NODE:
    if(ast->unary_expr.right != NULL)
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
    if(ast->declaration_expr.type != NULL)
      ast_free(ast->declaration_expr.type);
    if(ast->declaration_expr.right != NULL)
      ast_free(ast->declaration_expr.right);
    free(ast->declaration_expr.id);
    free(ast);
    break;

  case IF_STATEMENT_NODE:
    if(ast->if_expr.if_comparison != NULL)
      ast_free(ast->if_expr.if_comparison);
    if(ast->if_expr.if_statement != NULL)
      ast_free(ast->if_expr.if_statement);
    if(ast->if_expr.else_statement != NULL)
      ast_free(ast->if_expr.else_statement);
    free(ast);
    break;

  case STATEMENT_NODE:
    if(ast->statement_expr.left != NULL)
      ast_free(ast->statement_expr.left);
    if(ast->statement_expr.right != NULL)
      ast_free(ast->statement_expr.right);
    free(ast);
    break;

  case ASSIGNMENT_NODE:
    if(ast->assign_expr.left != NULL)
      ast_free(ast->assign_expr.left);
    if(ast->assign_expr.right != NULL)
      ast_free(ast->assign_expr.right);
    free(ast);
    break;

  case FUNCTION_NODE:
    if(ast->func_expr.arguments != NULL)
      ast_free(ast->func_expr.arguments);
    free(ast);
    break;

  case CONSTRUCTOR_NODE:
    if(ast->construt_expr.left != NULL)
      ast_free(ast->construt_expr.left);
    if(ast->construt_expr.right != NULL)
      ast_free(ast->construt_expr.right);
    free(ast);
    break;

  case NESTED_SCOPE_NODE:
    if(ast->nest_scope_expr.scope != NULL)
      ast_free(ast->nest_scope_expr.scope);
    free(ast);
    break;

  case DECLARATIONS_NODE:
    if(ast->declarations_expr.left != NULL)
      ast_free(ast->declarations_expr.left);
    if(ast->declarations_expr.right != NULL)
      ast_free(ast->declarations_expr.right);
    free(ast);
    break;

  case ARGUMENTS_NODE:
    if(ast->arguments_expr.left != NULL)
      ast_free(ast->arguments_expr.left);
    if(ast->arguments_expr.right != NULL)
      ast_free(ast->arguments_expr.right);
    free(ast);
    break;

  case ARGUMENTS_OPT_NODE:
    if(ast->arguments_opt_expr.argum != NULL)
      ast_free(ast->arguments_opt_expr.argum);
    free(ast);
    break;

  case EXPRESSION_NODE:
    if(ast->expression_expr.expr != NULL)
      ast_free(ast->expression_expr.expr);
    free(ast);
    break;

  default: break;
  }
}

void ast_print(node * ast) {
  //print dat shet

  // do inorder traversal
  if(ast == NULL) return;
  switch(ast->kind) {
    
    case SCOPE_NODE:
      // visit left node
      ast_print(ast->scope_expr.left);
      // print the current node
      fprintf(dumpFile, "SCOPE_NODE:\n");
      // visit right node
      ast_print(ast->scope_expr.right);
      break;

    case BINARY_EXPRESSION_NODE:
      ast_print(ast->binary_expr.left);
      
      fprintf(dumpFile, "BINARY_EXPRESSION_NODE\n");
      fprintf(dumpFile, "op: %d\n", ast->binary_expr.op);
              
      ast_print(ast->binary_expr.right);
      break;

    case UNARY_EXPRESSION_NODE:
      // print the current node  
      
      fprintf(dumpFile, "UNARY_EXPRESSION_NODE\n");
      fprintf(dumpFile, "op: %d\n", ast->unary_expr.op);
      
      ast_print(ast->unary_expr.right);
      break;

    case INT_NODE:
      // print the current node
      fprintf(dumpFile, "INT_NODE\n");
      fprintf(dumpFile, "val: %d\n", ast->int_expr.val);        
      break;

    case BOOL_NODE:
      // print the current node
      fprintf(dumpFile, "BOOL_NODE\n");
      fprintf(dumpFile, "val: %d\n", ast->bool_expr.val);              
      break;

    case FLOAT_NODE:
      // print the current node
      fprintf(dumpFile, "FLOAT_NODE\n");
      fprintf(dumpFile, "val: %f\n", ast->float_expr.val);              
      break;

    case IDENT_NODE:
      // print the current node
      fprintf(dumpFile, "IDENT_NODE\n");
      fprintf(dumpFile, "id: %d\n", ast->id_expr.type);              
      break;

    case VAR_NODE:
      // print the current node
      fprintf(dumpFile, "VAR_NODE\n");
      fprintf(dumpFile, "id: %s\n", ast->var_expr.id);              
      break;

    case DECLARATION_NODE:
      // print the current node
      ast_print(ast->declaration_expr.type);
      fprintf(dumpFile, "DECLARATION_NODE\n");
      fprintf(dumpFile, "id: %s\n", ast->declaration_expr.id);
      
      if(ast->declaration_expr.constant != -1)              
        fprintf(dumpFile, "constant: %d\n", ast->declaration_expr.constant);
      
      ast_print(ast->declaration_expr.right);
      
      break;

    case IF_STATEMENT_NODE:
      ast_print(ast->if_expr.if_comparison);
      fprintf(dumpFile, "IF_STATEMENT_NODE: if_comparison\n");
      
      ast_print(ast->if_expr.if_statement);
      fprintf(dumpFile, "IF_STATEMENT_NODE: if_statement\n");
      
      ast_print(ast->if_expr.else_statement);
      fprintf(dumpFile, "IF_STATEMENT_NODE: else_statement\n");

      break;

    case STATEMENT_NODE:
      ast_print(ast->statement_expr.left);
      fprintf(dumpFile, "STATEMENT_NODE\n");
      ast_print(ast->statement_expr.right);
      break;

    case ASSIGNMENT_NODE:
      ast_print(ast->assign_expr.left);
      fprintf(dumpFile, "STATEMENT_NODE\n");
      ast_print(ast->assign_expr.right);
      break;

    case FUNCTION_NODE:
      ast_print(ast->func_expr.arguments);      
      fprintf(dumpFile, "STATEMENT_NODE\n");
      fprintf(dumpFile, "func: %s\n", ast->func_expr.func);              
      break;

    case CONSTRUCTOR_NODE:
      ast_print(ast->construt_expr.left);
      fprintf(dumpFile, "CONSTRUCTOR_NODE\n");
      ast_print(ast->construt_expr.right);
      break;

    case NESTED_SCOPE_NODE:
      ast_print(ast->nest_scope_expr.scope);
      fprintf(dumpFile, "NESTED_SCOPE_NODE\n");
      break;

    case DECLARATIONS_NODE:
      ast_print(ast->declarations_expr.left);
      fprintf(dumpFile, "DECLARATIONS_NODE\n");      
      ast_print(ast->declarations_expr.right);
      break;

    case ARGUMENTS_NODE:
      ast_print(ast->arguments_expr.left);
      fprintf(dumpFile, "ARGUMENTS_NODE\n");      
      ast_print(ast->arguments_expr.right);
      break;

    case ARGUMENTS_OPT_NODE:
      ast_print(ast->arguments_opt_expr.argum);
      fprintf(dumpFile, "ARGUMENTS_OPT_NODE\n");      
      break;

    case EXPRESSION_NODE:
      ast_print(ast->expression_expr.expr);
      fprintf(dumpFile, "EXPRESSION_NODE\n");      
      break;
      
    default: break;
  }
  return;
}