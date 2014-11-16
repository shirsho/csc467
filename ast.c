#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

#include "ast.h"
#include "common.h"
#include "parser.tab.h"
#include "symbol.h"
#include "semantic.h"
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

    case VAR_NODE:
      ast->var_expr.id = va_arg(args, char*);
      ast->var_expr.arr = va_arg(args, int);
      break;

    case DECLARATION_NODE:
      ast->declaration_expr.type = va_arg(args, int);
      ast->declaration_expr.id = va_arg(args, char*);
      ast->declaration_expr.right = va_arg(args, node *);
      ast->declaration_expr.constant = va_arg(args, int);
      ast->declaration_expr.line = va_arg(args, int);
      break;

    case IF_STATEMENT_NODE:
      ast->if_expr.if_comparison = va_arg(args, node *);
      ast->if_expr.if_statement = va_arg(args, node *);
      ast->if_expr.else_statement = va_arg(args, node *);
      ast->if_expr.line = va_arg(args, int);
      break;

    case STATEMENT_NODE:
      ast->statement_expr.left = va_arg(args, node *);
      ast->statement_expr.right = va_arg(args, node *);
      break;

    case ASSIGNMENT_NODE:
      ast->assign_expr.left = va_arg(args, node *);
      ast->assign_expr.right = va_arg(args, node *);
      ast->assign_expr.line = va_arg(args, int);
      break;

    case FUNCTION_NODE:
      ast->func_expr.func = va_arg(args, int);
      ast->func_expr.arguments = va_arg(args, node *);
      break;

    case CONSTRUCTOR_NODE:
      ast->construt_expr.type = va_arg(args, int);
      ast->construt_expr.right = va_arg(args, node *);
      break;

    case NESTED_SCOPE_NODE:
      ast->nest_scope_expr.scope = va_arg(args, node *);
      ast->nest_scope_expr.variables = va_arg(args, symbol *);
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

    case VAR_NODE:
      free(ast);
      break;

    case DECLARATION_NODE:
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

char* getType(int type)
{
  char * typeString = NULL;
  switch(type){
        case -1:
          typeString = "invalid";
        case INT_NODE:
          typeString = "int";
          break;
        case FLOAT_NODE:
          typeString = "float";
          break;       
        case 1: 
          typeString = "int";
          break;
        case 2: 
          typeString = "bool";
          break;
        case 3: 
          typeString = "float";
          break;
        case 11: 
          typeString = "ivec2";
          break;
        case 12: 
          typeString = "ivec3";
          break;
        case 13: 
          typeString = "ivec4";
          break;
        case 21: 
          typeString = "bvec2";
          break;
        case 22: 
          typeString = "bvec3";
          break;
        case 23: 
          typeString = "bvec4";
          break;
        case 31: 
          typeString = "vec2";
          break;
        case 32: 
          typeString = "vec3";
          break;    
        case 33: 
          typeString = "vec4";
          break;
        case 261:
          typeString = "const";
          break;   
  }
  return typeString;
}
// burrows down the ast and returns the type field of the node
// which is later converted into a string representing the actual type (e.g int, float)
int burrow(node * ast)
{
  // What nodes have type field?
  // 1. declaration_expr.type
  // 2. construt_exp.type
  int typeVal = -1; // default return for error check
  int leftBinTypeVal;
  int rightBinTypeVal;
  symbol* sym = NULL;
  if (ast == NULL)
    return typeVal;
  
  switch(ast->kind){
    case DECLARATION_NODE:
      //printf("DECLARATION_NODE in burrow\n");
      typeVal = ast->declaration_expr.type;
      break;
    case CONSTRUCTOR_NODE:
      //printf("CONSTRUCTOR_NODE in burrow\n");
 
      typeVal = ast->declaration_expr.type;
      break;
    case INT_NODE:
      //printf("INT_NODE in burrow\n");
      //printf("typeval int ---->%d\n", INT_NODE);
      typeVal = 1; // to match with getType()
      //printf("INT_NODE typeVal ----->%d\n", typeVal);
      
      break;
    case FLOAT_NODE:
      //printf("FLOAT_NODE in burrow\n");
      typeVal = 3; // to match with getType()
      break;
    case VAR_NODE:
      //printf("VAR_NODE in burrow: %s \n", ast->var_expr.id);
      
      // find the type associated with this variable from symbol table
      sym = find_Symbol_External(ast->var_expr.id);
      if(sym)
        typeVal = sym->type_int;
      else
        typeVal = -1;
      //printf("\nVAR_NODE typeVal ----->%d \n", typeVal);
      
      break;
    case EXPRESSION_NODE:
      //printf("EXPRESSION_NODE in burrow.....\n");
      typeVal = burrow(ast->expression_expr.expr);
      //printf("\ntypeVal ----->%d \n", typeVal);
      break;
    case BINARY_EXPRESSION_NODE:
      //printf("BINARY_EXPRESSION_NODE in burrow\n");
      leftBinTypeVal = burrow(ast->binary_expr.left);
      rightBinTypeVal = burrow(ast->binary_expr.right);
      if(leftBinTypeVal == rightBinTypeVal)
      {
        typeVal = leftBinTypeVal;
      }
      break;
    case UNARY_EXPRESSION_NODE:
      //printf("UNARY_EXPRESSION_NODE in burrow\n");
      typeVal = burrow(ast->unary_expr.right);
      break;
    case BOOL_NODE:
      //printf("BOOL_NODE in burrow\n");
      typeVal = 2; // to match with getType()
      break;
    default:
      typeVal = -1;
      break;
  }
  return typeVal;
}

void ast_print(node * ast) {
  //print dat shet
  char * type = NULL;
  int unaryTypeVal;
  int leftBinTypeVal;
  int rightBinTypeVal;
  
  if(ast == NULL) return;
  switch(ast->kind) {
    // Working
    case SCOPE_NODE:
      fprintf(dumpFile, "(SCOPE \n");
      // call to get (DECLARATIONS...)  (STATEMENTS...));
      ast_print(ast->scope_expr.left);  // go to declarations
      ast_print(ast->scope_expr.right); // go to statements
      // close scope bracket
      fprintf(dumpFile, ")\n");     
      break;

    case DECLARATIONS_NODE:
      fprintf(dumpFile, "(DECLARATIONS\n");
      ast_print(ast->declarations_expr.left); // come back to declarations
      ast_print(ast->declarations_expr.right); // go to declaration
      fprintf(dumpFile, ")\n");
      break;
    
    case DECLARATION_NODE:
      type = getType(ast->declaration_expr.type);
      //fprintf(dumpFile, "id: %s\n", ast->declaration_expr.id);
      if(ast->declaration_expr.constant == -1) // right hand side is a literal
        fprintf(dumpFile, "(DECLARATION %s %s)\n", type, ast->declaration_expr.id);
      else if(ast->declaration_expr.constant == -2) // right hand side is an expression form
      {
        fprintf(dumpFile, "(DECLARATION %s %s ", type, ast->declaration_expr.id);
        // the right hand side expression will be printed in the next recursive call
        ast_print(ast->declaration_expr.right);
      }
      else if(ast->declaration_expr.constant == CONST)
      {
        fprintf(dumpFile, "(DECLARATION const %s %s ", type, ast->declaration_expr.id);
        // the right hand side expression will be printed in the next recursive call
        ast_print(ast->declaration_expr.right);
      }
      break;
    
    case INT_NODE:
      //printf("INT_NODE --->\n");
      fprintf(dumpFile, "%d ", ast->int_expr.val);
      break;

    case BOOL_NODE:
      if(ast->bool_expr.val == TRUE_C)
        fprintf(dumpFile, "true ");
      else if(ast->bool_expr.val == FALSE_C)
        fprintf(dumpFile, "false ");
      break;

    case FLOAT_NODE:
      fprintf(dumpFile, "%f ", ast->float_expr.val);
      break;

    case VAR_NODE:
      fprintf(dumpFile, "%s ", ast->var_expr.id);
      //printf("<---VAR_NODE\t");

      break;
    
    case EXPRESSION_NODE:
      ast_print(ast->expression_expr.expr);
      //fprintf(dumpFile, "<---EXPRESSION_NODE\n");
      break;
    
    case UNARY_EXPRESSION_NODE:
      // TODO This makes no sense
      //fprintf(dumpFile, "op: %d\n", ast->unary_expr.op);
      if(ast->unary_expr.op == UMINUS) // op is unary minus
      {
        // get the int associated with type using burrow
        unaryTypeVal = burrow(ast->unary_expr.right);
        //printf("typeVal is:%d\n", unaryTypeVal);
        // then get the string for the type
        type = getType(unaryTypeVal);
        fprintf(dumpFile, "(UNARY %s - ", type);
        ast_print(ast->unary_expr.right);
        fprintf(dumpFile, ") ");
      }
      else if(ast->unary_expr.op == 33) // op is unary !
      {  
        fprintf(dumpFile, "(UNARY bool ! ");
        ast_print(ast->unary_expr.right);
        fprintf(dumpFile, ") ");
      }
      break;
    
    case BINARY_EXPRESSION_NODE:
      //ast_print(ast->binary_expr.left);
      //printf("binary op:%d\n", ast->binary_expr.op);
      if(ast->binary_expr.op == 43) // for +
      {
        leftBinTypeVal = burrow(ast->binary_expr.left);
        rightBinTypeVal = burrow(ast->binary_expr.right);
        //printf("rightBinTypeVal:%d\n", rightBinTypeVal);
        
        //printf("leftBinTypeVal:%d, rightBinTypeVal:%d\n", leftBinTypeVal, rightBinTypeVal);
        
        if(leftBinTypeVal != -1 && rightBinTypeVal != -1 && leftBinTypeVal == rightBinTypeVal)
        {
          type = getType(leftBinTypeVal);
          fprintf(dumpFile, "(BINARY %s + ", type);
        }
        else // type mismatch
          fprintf(dumpFile, "(BINARY INVALID + ");
        ast_print(ast->binary_expr.left);
        ast_print(ast->binary_expr.right);
        fprintf(dumpFile, ") ");
        
      }
      else if(ast->binary_expr.op == 45) // for -
      {  
        leftBinTypeVal = burrow(ast->binary_expr.left);
        rightBinTypeVal = burrow(ast->binary_expr.right);
        //printf("leftBinTypeVal:%d, rightBinTypeVal:%d\n", leftBinTypeVal, rightBinTypeVal);
        if(leftBinTypeVal != -1 && rightBinTypeVal != -1 && leftBinTypeVal == rightBinTypeVal)
        {
          type = getType(leftBinTypeVal);
          fprintf(dumpFile, "(BINARY %s - ", type);
        }
        else // type mismatch
          fprintf(dumpFile, "(BINARY INVALID - ");
        ast_print(ast->binary_expr.left);
        ast_print(ast->binary_expr.right);
        fprintf(dumpFile, ") ");
      }
      else if(ast->binary_expr.op == 42) // for *
      {  
        leftBinTypeVal = burrow(ast->binary_expr.left);
        rightBinTypeVal = burrow(ast->binary_expr.right);
        //printf("leftBinTypeVal:%d, rightBinTypeVal:%d\n", leftBinTypeVal, rightBinTypeVal);
        if(leftBinTypeVal != -1 && rightBinTypeVal != -1 && leftBinTypeVal == rightBinTypeVal)
        {
          type = getType(leftBinTypeVal);
          fprintf(dumpFile, "(BINARY %s * ", type);
        }
        else // type mismatch
          fprintf(dumpFile, "(BINARY INVALID * ");
        ast_print(ast->binary_expr.left);
        ast_print(ast->binary_expr.right);
        fprintf(dumpFile, ") ");
      }
      else if(ast->binary_expr.op == 47) // for /
      {  
        leftBinTypeVal = burrow(ast->binary_expr.left);
        rightBinTypeVal = burrow(ast->binary_expr.right);
        //printf("leftBinTypeVal:%d, rightBinTypeVal:%d\n", leftBinTypeVal, rightBinTypeVal);
        if(leftBinTypeVal != -1 && rightBinTypeVal != -1 && leftBinTypeVal == rightBinTypeVal)
        {
          type = getType(leftBinTypeVal);
          fprintf(dumpFile, "(BINARY %s / ", type);
        }
        else // type mismatch
          fprintf(dumpFile, "(BINARY INVALID / ");
        ast_print(ast->binary_expr.left);
        ast_print(ast->binary_expr.right);
        fprintf(dumpFile, ") ");
      }
      else if(ast->binary_expr.op == AND)
      {  
        leftBinTypeVal = burrow(ast->binary_expr.left);
        //printf("leftBinTypeVal:%d\n", leftBinTypeVal);
        rightBinTypeVal = burrow(ast->binary_expr.right);
        //printf("leftBinTypeVal:%d, rightBinTypeVal:%d\n", leftBinTypeVal, rightBinTypeVal);
        if(leftBinTypeVal != -1 && rightBinTypeVal != -1 && leftBinTypeVal == rightBinTypeVal)
        {
          type = getType(leftBinTypeVal);
          if(strcmp(type, "bool") == 0)
            fprintf(dumpFile, "(BINARY bool AND ");
          else
            fprintf(dumpFile, "(BINARY INVALID AND ");
        }
        else // type mismatch
          fprintf(dumpFile, "(BINARY INVALID AND ");
        ast_print(ast->binary_expr.left);
        ast_print(ast->binary_expr.right);
        fprintf(dumpFile, ") ");
        
      }
      else if(ast->binary_expr.op == OR)
      {  
        leftBinTypeVal = burrow(ast->binary_expr.left);
        //printf("leftBinTypeVal:%d\n", leftBinTypeVal);
        rightBinTypeVal = burrow(ast->binary_expr.right);
        //printf("leftBinTypeVal:%d, rightBinTypeVal:%d\n", leftBinTypeVal, rightBinTypeVal);
        if(leftBinTypeVal != -1 && rightBinTypeVal != -1 && leftBinTypeVal == rightBinTypeVal)
        {
          type = getType(leftBinTypeVal);
          if(strcmp(type, "bool") == 0)
            fprintf(dumpFile, "(BINARY bool OR ");
          else // type mismatch
            fprintf(dumpFile, "(BINARY INVALID GEQ ");
        }
        else // type mismatch
          fprintf(dumpFile, "(BINARY INVALID OR ");
        ast_print(ast->binary_expr.left);
        ast_print(ast->binary_expr.right);
        fprintf(dumpFile, ") ");
      }
      else if(ast->binary_expr.op == NEQ)
      {  
        leftBinTypeVal = burrow(ast->binary_expr.left);
        //printf("leftBinTypeVal:%d\n", leftBinTypeVal);
        rightBinTypeVal = burrow(ast->binary_expr.right);
        //printf("leftBinTypeVal:%d, rightBinTypeVal:%d\n", leftBinTypeVal, rightBinTypeVal);
        if(leftBinTypeVal != -1 && rightBinTypeVal != -1 && leftBinTypeVal == rightBinTypeVal)
        {
          type = getType(leftBinTypeVal);
          fprintf(dumpFile, "(BINARY bool NEQ ");
        }
        else // type mismatch
          fprintf(dumpFile, "(BINARY INVALID NEQ ");
        ast_print(ast->binary_expr.left);
        ast_print(ast->binary_expr.right);
        fprintf(dumpFile, ") ");
      }
      else if(ast->binary_expr.op == EQ)
      {  
        leftBinTypeVal = burrow(ast->binary_expr.left);
        //printf("leftBinTypeVal:%d\n", leftBinTypeVal);
        rightBinTypeVal = burrow(ast->binary_expr.right);
        //printf("leftBinTypeVal:%d, rightBinTypeVal:%d\n", leftBinTypeVal, rightBinTypeVal);
        if(leftBinTypeVal != -1 && rightBinTypeVal != -1 && leftBinTypeVal == rightBinTypeVal)
        {
          type = getType(leftBinTypeVal);
          fprintf(dumpFile, "(BINARY bool EQ ");
        }
        else // type mismatch
          fprintf(dumpFile, "(BINARY INVALID EQ ");
        ast_print(ast->binary_expr.left);
        ast_print(ast->binary_expr.right);
        fprintf(dumpFile, ") ");
      }
      else if(ast->binary_expr.op == LEQ)   
      {  
        leftBinTypeVal = burrow(ast->binary_expr.left);
        //printf("leftBinTypeVal:%d\n", leftBinTypeVal);
        rightBinTypeVal = burrow(ast->binary_expr.right);
        //printf("leftBinTypeVal:%d, rightBinTypeVal:%d\n", leftBinTypeVal, rightBinTypeVal);
        if(leftBinTypeVal != -1 && rightBinTypeVal != -1 && leftBinTypeVal == rightBinTypeVal)
        {
          type = getType(leftBinTypeVal);
          fprintf(dumpFile, "(BINARY bool LEQ ");
        }
        else // type mismatch
          fprintf(dumpFile, "(BINARY INVALID LEQ ");
        ast_print(ast->binary_expr.left);
        ast_print(ast->binary_expr.right);
        fprintf(dumpFile, ") ");
      }
      else if(ast->binary_expr.op == GEQ)
      {  
        leftBinTypeVal = burrow(ast->binary_expr.left);
        //printf("leftBinTypeVal:%d\n", leftBinTypeVal);
        rightBinTypeVal = burrow(ast->binary_expr.right);
        //printf("leftBinTypeVal:%d, rightBinTypeVal:%d\n", leftBinTypeVal, rightBinTypeVal);
        if(leftBinTypeVal != -1 && rightBinTypeVal != -1 && leftBinTypeVal == rightBinTypeVal)
        {
          type = getType(leftBinTypeVal);
          fprintf(dumpFile, "(BINARY bool GEQ ");
        }
        else // type mismatch
          fprintf(dumpFile, "(BINARY INVALID GEQ ");
        ast_print(ast->binary_expr.left);
        ast_print(ast->binary_expr.right);
        fprintf(dumpFile, ") ");
      }
      


      //fprintf(dumpFile, "(BINARY <type>");
      //fprintf(dumpFile, "op: %d\n", ast->binary_expr.op);

      //ast_print(ast->binary_expr.right);
      break;
    
    case NESTED_SCOPE_NODE:
      fprintf(dumpFile, "(NESTED SCOPE\n");
      ast_print(ast->nest_scope_expr.scope);
      fprintf(dumpFile, ") <--NESTED SCOPE END\n");      
      break;

    /*  
    
    case STATEMENT_NODE:
      fprintf(dumpFile, "STATEMENTS\t(STATEMENTS...)\n");
      ast_print(ast->statement_expr.left);
      ast_print(ast->statement_expr.right);
      break;
    
    */
    /*
    
    

    

    

    case IF_STATEMENT_NODE:
      //ast_print(ast->if_expr.if_comparison);
      //fprintf(dumpFile, "IF_STATEMENT_NODE: if_comparison\n");
      //ast_print(ast->if_expr.if_statement);
      //fprintf(dumpFile, "IF_STATEMENT_NODE: if_statement\n");
      //ast_print(ast->if_expr.else_statement);
      if(ast->if_expr.if_comparison && ast->if_expr.if_statement){
        if(ast->if_expr.else_statement)
          fprintf(dumpFile, "IF\t(IF %s %s %s)\n", ast->if_expr.if_comparison, ast->if_expr.if_statement, ast->if_expr.else_statement);
        else
          fprintf(dumpFile, "IF\t(IF %s %s)\n", ast->if_expr.if_comparison, ast->if_expr.if_statement);
      }

      break;
    

    case ASSIGNMENT_NODE:

      //ast_print(ast->assign_expr.left);
      // TODO: Need to print <type>
      fprintf(dumpFile, "ASSIGN\t(ASSIGN <type> %s %s\n", ast->assign_expr.left->var_expr.id, ast->assign_expr.left->expression_expr.expr);
      //ast_print(ast->assign_expr.right);
      break;

    case FUNCTION_NODE:
      ast_print(ast->func_expr.arguments);
      fprintf(dumpFile, "FUNCTION_NODE\n");
      fprintf(dumpFile, "func: %d\n", ast->func_expr.func);
      break;

    case CONSTRUCTOR_NODE:
      //ast_print(ast->construt_expr.left);
      fprintf(dumpFile, "type: %d\n", ast->construt_expr.type);
      fprintf(dumpFile, "CONSTRUCTOR_NODE\n");
      ast_print(ast->construt_expr.right);
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
    */
   
    default: break;
  }
  return;
}

