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
int scope_ast = -1;
symbol *b[20];

/*Builds the tree*/
node *ast_allocate(node_kind kind, ...) {
  va_list args;

  // make the node
  node *ast = (node *) malloc(sizeof(node));
  memset(ast, 0, sizeof *ast);
  ast->kind = kind;

  va_start(args, kind); 

  switch(kind) {
  
    case SCOPE_NODE:
      ast->scope_expr.left = va_arg(args, node *);  //Declarations
      ast->scope_expr.right = va_arg(args, node *);   //Statements
      break;

    case BINARY_EXPRESSION_NODE:
      ast->binary_expr.op = va_arg(args, int);    //Operation
      ast->binary_expr.left = va_arg(args, node *);   //Left side of binary op
      ast->binary_expr.right = va_arg(args, node *);    //Right side of binary op
      break;

    case UNARY_EXPRESSION_NODE:
      ast->unary_expr.op = va_arg(args, int);   //Operation
      ast->unary_expr.right = va_arg(args, node *);   ///Right side of unary op
      break;

    case INT_NODE:
      ast->int_expr.val = va_arg(args, int);    //An int literal
      break;

    case FLOAT_NODE:
      ast->float_expr.val = va_arg(args, double);   //A float literal
      break;

    case BOOL_NODE:
      ast->bool_expr.val = va_arg(args, int);   //A bool literal
      break;

    case VAR_NODE:
      ast->var_expr.id = va_arg(args, char*);   //The variable id
      ast->var_expr.arr = va_arg(args, int);    //The array accessing of the variable
      break;

    case DECLARATION_NODE:
      ast->declaration_expr.type = va_arg(args, int);   //Type of variable
      ast->declaration_expr.id = va_arg(args, char*);   //ID of variable
      ast->declaration_expr.right = va_arg(args, node *);   //What the variable is equal to
      ast->declaration_expr.constant = va_arg(args, int);   //If it is constant
      ast->declaration_expr.line = va_arg(args, int);   //The line it occurs on
      break;

    case IF_STATEMENT_NODE:
      ast->if_expr.if_comparison = va_arg(args, node *);    //The comparison
      ast->if_expr.if_statement = va_arg(args, node *);   //The statement
      ast->if_expr.else_statement = va_arg(args, node *);   //The else statement
      ast->if_expr.line = va_arg(args, int);      //The line it occurs on
      break;

    case STATEMENT_NODE:
      ast->statement_expr.left = va_arg(args, node *);    //Statements
      ast->statement_expr.right = va_arg(args, node *);   //Statement
      break;

    case ASSIGNMENT_NODE:
      ast->assign_expr.left = va_arg(args, node *);   //The variable assigned to
      ast->assign_expr.right = va_arg(args, node *);    //The variable or value assigning
      ast->assign_expr.line = va_arg(args, int);    //The line it occurs on
      break;

    case FUNCTION_NODE:
      ast->func_expr.func = va_arg(args, int);    //Function
      ast->func_expr.arguments = va_arg(args, node *);    //Arguments
      break;

    case CONSTRUCTOR_NODE:
      ast->construt_expr.type = va_arg(args, int);     //Type of constructor
      ast->construt_expr.right = va_arg(args, node *);    //Arguments
      break;

    case NESTED_SCOPE_NODE:
      ast->nest_scope_expr.scope = va_arg(args, node *);    //The scope
      ast->nest_scope_expr.variables = va_arg(args, symbol *);    //The symbol table
      break; 

    case DECLARATIONS_NODE:
      ast->declarations_expr.left = va_arg(args, node *);   //Declarations
      ast->declarations_expr.right = va_arg(args, node *);  //Declaration
      break;

    case ARGUMENTS_NODE:
      ast->arguments_expr.left = va_arg(args, node *);    //Arguments
      ast->arguments_expr.right = va_arg(args, node *);   //Expression
      break;

    case ARGUMENTS_OPT_NODE:
      ast->arguments_opt_expr.argum = va_arg(args, node *);   //Arguments
      break;

    case EXPRESSION_NODE:
      ast->expression_expr.expr = va_arg(args, node *);   //For either brackets or accessing a variable
      break;

    default: break;
  }

  va_end(args);

  return ast;
}

/*Frees all the nodes in the ast tree*/
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
      if(ast->nest_scope_expr.variables != NULL)
        free(ast->nest_scope_expr.variables);
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

/*Returns the type of the variable in string format*/
char* getType(int type)
{
  char * typeString = NULL;
  switch(type){
        case -1:
          typeString = (char *)"invalid";
        case INT_NODE:
          typeString = (char *)"int";
          break;
        case FLOAT_NODE:
          typeString = (char *)"float";
          break;       
        case 1: 
          typeString = (char *)"int";
          break;
        case 2: 
          typeString = (char *)"bool";
          break;
        case 3: 
          typeString = (char *)"float";
          break;
        case 11: 
          typeString = (char *)"ivec2";
          break;
        case 12: 
          typeString = (char *)"ivec3";
          break;
        case 13: 
          typeString = (char *)"ivec4";
          break;
        case 21: 
          typeString = (char *)"bvec2";
          break;
        case 22: 
          typeString = (char *)"bvec3";
          break;
        case 23: 
          typeString = (char *)"bvec4";
          break;
        case 31: 
          typeString = (char *)"vec2";
          break;
        case 32: 
          typeString = (char *)"vec3";
          break;    
        case 33: 
          typeString = (char *)"vec4";
          break;
        case 261:
          typeString = (char *)"const";
          break;
        case 264:
          typeString = (char *)"dp3";
          break;
        case 266:
          typeString = (char *)"rsq";
          break;
        case 265:
          typeString = (char *)"lit";
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
      // if variable is of type vec3 or vec4, return type is float
      if(strcmp(sym->type, "vec3") == 0 || strcmp(sym->type, "vec4") == 0 )
        typeVal = 3; // to match with getType()
      if(strcmp(sym->type, "ivec3") == 0 || strcmp(sym->type, "ivec4") == 0 )
        typeVal = 1; // to match with getType()
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
    case FUNCTION_NODE:
      //type = getType(ast->func_expr.func);
      //printf("FUNCTION_NODE in burrow\n");
      //sym = find_Symbol_External(ast->var_expr.id);
      /*
      if(sym)
        typeVal = sym->type_int;
      else
        typeVal = -1;
      */
      //fprintf(dumpFile, "(CALL %s ", type);
      //ast_print(ast->func_expr.arguments);
      //fprintf(dumpFile, "\n");
      typeVal = burrow(ast->func_expr.arguments);
      //fprintf(dumpFile, "<--FUNCTION_NODE\n");      
      break;


    case ARGUMENTS_NODE:
      //fprintf(dumpFile, "ARGUMENTS_NODE in burrow\n");
      //typeVal = burrow(ast->arguments_expr.left);
      typeVal = burrow(ast->arguments_expr.right);
      //fprintf(dumpFile, ", ");
      
      break;

    case ARGUMENTS_OPT_NODE:
      //fprintf(dumpFile, "ARGUMENTS_OPT_NODE in burrow\n");
      typeVal = burrow(ast->arguments_opt_expr.argum);
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
      fprintf(dumpFile, "\n)\n");
      break;
    
    case DECLARATION_NODE:
      type = getType(ast->declaration_expr.type);
      //fprintf(dumpFile, "id: %s\n", ast->declaration_expr.id);
      if(ast->declaration_expr.constant == -1) // right hand side is a literal
        fprintf(dumpFile, "(DECLARATION %s %s)\n", ast->declaration_expr.id, type);
      else if(ast->declaration_expr.constant == -2) // right hand side is an expression form
      {
        fprintf(dumpFile, "(DECLARATION %s %s ", ast->declaration_expr.id, type);
        // the right hand side expression will be printed in the next recursive call
        ast_print(ast->declaration_expr.right);
      }
      else if(ast->declaration_expr.constant == CONST)
      {
        fprintf(dumpFile, "(DECLARATION const %s %s ", ast->declaration_expr.id, type);
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
      // Got stuff TODO
      // Could be:
        // ID 
        // ID '[' INT_C ']'
      if(ast->var_expr.arr == -1)
        fprintf(dumpFile, "%s ", ast->var_expr.id);
      else
        fprintf(dumpFile, "(INDEX int %s %d", ast->var_expr.id, ast->var_expr.arr);
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
      break;
    
    case NESTED_SCOPE_NODE:
      scope_ast = scope_ast + 1;
      b[scope_ast] = ast->nest_scope_expr.variables;
      fprintf(dumpFile, "(NESTED SCOPE\n");
      ast_print(ast->nest_scope_expr.scope);
      fprintf(dumpFile, ")\n");      
      break;

    case CONSTRUCTOR_NODE:
      //ast_print(ast->construt_expr.left);
      type = getType(ast->construt_expr.type);
      //fprintf(dumpFile, "type: %d\n", ast->construt_expr.type);
      //fprintf(dumpFile, "CONSTRUCTOR_NODE\n");
      fprintf(dumpFile, "(CALL %s", type);
      
      ast_print(ast->construt_expr.right); // get the arguments
      break;

    case ARGUMENTS_NODE:
      //fprintf(dumpFile, "ARGUMENTS_NODE\n");
      ast_print(ast->arguments_expr.left);
      ast_print(ast->arguments_expr.right);
      fprintf(dumpFile, ", ");
      
      break;

    case ARGUMENTS_OPT_NODE:
      //fprintf(dumpFile, "ARGUMENTS_OPT_NODE\n");
      fprintf(dumpFile, "(");
      ast_print(ast->arguments_opt_expr.argum);
      fprintf(dumpFile, ")");
      fprintf(dumpFile, ")");
      break; 

    case STATEMENT_NODE:
      fprintf(dumpFile, "(STATEMENTS\n");
      ast_print(ast->statement_expr.left);
      ast_print(ast->statement_expr.right);
      fprintf(dumpFile, ")\n");
      break;

    case ASSIGNMENT_NODE:
      //ast_print(ast->assign_expr.left);
      unaryTypeVal = burrow(ast->assign_expr.left);
      type = getType(unaryTypeVal);
      //printf("type: %s\n", type);
      //printf("ast->assign_expr.left->var_expr.id: %s\n", ast->assign_expr.left->var_expr.id);
      //printf("ast->assign_expr.left->expression_expr.expr: %s\n", ast->assign_expr.left->expression_expr.expr);
      fprintf(dumpFile, "(ASSIGN %s %s ", type, ast->assign_expr.left->var_expr.id);
      //ast_print(ast->assign_expr.left->expression_expr.expr);
      ast_print(ast->assign_expr.right);
      break; 
    case IF_STATEMENT_NODE:
      //fprintf(dumpFile, "IF_STATEMENT_NODE\n");
      if(ast->if_expr.if_comparison && ast->if_expr.if_statement){
        if(ast->if_expr.else_statement){
          fprintf(dumpFile, "(IF ");
          ast_print(ast->if_expr.if_comparison);
          ast_print(ast->if_expr.if_statement);
          ast_print(ast->if_expr.else_statement);
        }
        else
        {
          fprintf(dumpFile, "(IF ");
          ast_print(ast->if_expr.if_comparison);
          ast_print(ast->if_expr.if_statement);
        }
      }

      break;

        
    case FUNCTION_NODE:
      type = getType(ast->func_expr.func);
      fprintf(dumpFile, "(CALL %s ", type);
      ast_print(ast->func_expr.arguments);
      fprintf(dumpFile, "\n");
      //fprintf(dumpFile, "<--FUNCTION_NODE\n");
      
      break;
    
    default: 
      fprintf(dumpFile, "DEFAULT\n");
      
      break;
  }
  return;
}

symbol* find_Symbol_External(char *name){
      symbol *s;
      int c;
      int found = 0;
      for(c = scope_ast; c >= 0; c--){
            for(s = b[c]->symtable; s != NULL; s = s->next){
                  if (!strcmp(name, s->name)){
                        found = 1;
                        //printf("\nfound symbol %s\n", name);
                        break;
                  }
            }
            if(found == 1)
                  break;
      }
      if(found == 0)
            s = find_Sym_External(name);

      if(s == NULL){
            fprintf(errorFile, "Unable to find variable %s\n", name);
            errorOccurred = 1;
            return NULL;
      }

      return s;
}
