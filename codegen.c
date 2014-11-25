/*
Justin Canton, 1000017910
Samprit Raihan, 998138830
*/
#include "codegen.h"

FILE *filePointer = fopen("./frag.txt", "w");

void generateAssembly(node * ast){

	// Open the assembly file
	
	switch(ast->kind) {
  
	    case SCOPE_NODE:
	    	fprintf(filePointer, "#SCOPE\n");
	    	if(ast->scope_expr.left != NULL){
	    		generateAssembly(ast->scope_expr.left);
	    	}
	    	if(ast->scope_expr.right != NULL){
	    		generateAssembly(ast->scope_expr.right);
	    	}
	      break;

	    case BINARY_EXPRESSION_NODE:

	      	break;

	    case UNARY_EXPRESSION_NODE:
	      	break;

	    case INT_NODE:
	    	//fprintf(filePointer, "#INT\n");
	    	fprintf(filePointer, "%d", ast->int_expr.val);
	      	break;

	    case FLOAT_NODE:
	    	//fprintf(filePointer, "#FLOAT\n");
	    	fprintf(filePointer, "%f", ast->float_expr.val);
	     	break;

	    case BOOL_NODE:
	      	break;

	    case VAR_NODE:
	    	//fprintf(filePointer, "#VAR\n");
	    	if(ast->var_expr.arr == -1){
	    		fprintf(filePointer, "%s", ast->var_expr.id);
	    	}else if(ast->var_expr.arr == 0){
	    		fprintf(filePointer, "%s.x", ast->var_expr.id);
	    	}else if(ast->var_expr.arr == 1){
	    		fprintf(filePointer, "%s.y", ast->var_expr.id);
	    	}else if(ast->var_expr.arr == 2){
	    		fprintf(filePointer, "%s.z", ast->var_expr.id);
	    	}else if(ast->var_expr.arr == 3){
	    		fprintf(filePointer, "%s.w", ast->var_expr.id);
	    	}
	      	break;

	    case DECLARATION_NODE:
	    	fprintf(filePointer, "#DECLARATION\n");
	    	if(ast->declaration_expr.constant == 261){
	    		generateAssembly(ast->declaration_expr.right);
	    		fprintf(filePointer, "PARAM %s = tempVar;\n", ast->declaration_expr.id);
	    	}else{
	    		if(ast->declaration_expr.right == NULL){
	    			fprintf(filePointer, "TEMP %s;\n", ast->declaration_expr.id);
	    		}else{
	    			fprintf(filePointer, "TEMP %s;\n",  ast->declaration_expr.id);
	    			if(ast->declaration_expr.right->kind == BINARY_EXPRESSION_NODE){
	    				fprintf(filePointer, "TEMP tempVar;\n");
	    				generateAssembly(ast->declaration_expr.right);
	    				fprintf(filePointer, "MOV %s, tempVar;\n",  ast->declaration_expr.id);
	    			}else{
	    				fprintf(filePointer, "MOV %s, ",  ast->declaration_expr.id);
	    				generateAssembly(ast->declaration_expr.right);
	    				fprintf(filePointer, ";\n");
	    			}

	    		}
	    	}
	      	break;

	    case IF_STATEMENT_NODE:
	      	break;

	    case STATEMENT_NODE:
	     	break;

	    case ASSIGNMENT_NODE:
	      	break;

	    case FUNCTION_NODE:
	      	break;

	    case CONSTRUCTOR_NODE:
	      	break;

	    case NESTED_SCOPE_NODE:
	      	break;

	    case DECLARATIONS_NODE:
	    	fprintf(filePointer, "#DECLARATIONS\n");
	    	if(ast->declarations_expr.left != NULL){
	    		generateAssembly(ast->declarations_expr.left);
	    	}
	    	if(ast->declarations_expr.right != NULL){
	    		generateAssembly(ast->declarations_expr.right);
	    	}
	      	break;

	    case ARGUMENTS_NODE:
	      	break;

	    case ARGUMENTS_OPT_NODE:
	      	break;

	    case EXPRESSION_NODE:
	      	break;

	    default: break;
	}
	/*
		From this point on, keep adding new instructions
		to the assembly file on a new line using 
		fprint(filePointer, <newline terminated string>)
	*/
	
	// Close the assembly file
	//fclose(filePointer);
}