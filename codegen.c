/*
Justin Canton, 1000017910
Samprit Raihan, 998138830
*/
#include "codegen.h"

int tempCount = 1;
int argumentsCount = 0;

FILE *filePointer = fopen("./frag.txt", "w");

int generateAssembly(node * ast){
	int s;
	// Open the assembly file
	
	switch(ast->kind) {
  
	    case SCOPE_NODE:
	    	printf("SCOPE\n");
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
	    		if(ast->declaration_expr.right->kind == BINARY_EXPRESSION_NODE){
	    			generateAssembly(ast->declaration_expr.right);
	    			fprintf(filePointer, "PARAM %s = tempVar%d;\n", ast->declaration_expr.id, tempCount);
	    		}else{
	    			fprintf(filePointer, "PARAM %s = ",  ast->declaration_expr.id);
	    			generateAssembly(ast->declaration_expr.right);
	    			fprintf(filePointer, ";\n");
	    		}
	    	}else{
	    		if(ast->declaration_expr.right == NULL){
	    			fprintf(filePointer, "TEMP %s;\n", ast->declaration_expr.id);
	    		}else{
	    			fprintf(filePointer, "TEMP %s;\n",  ast->declaration_expr.id);
	    			if(ast->declaration_expr.right->kind == BINARY_EXPRESSION_NODE || 
	    				ast->declaration_expr.right->kind == UNARY_EXPRESSION_NODE ||
	    				ast->declaration_expr.right->kind == CONSTRUCTOR_NODE ||
	    				ast->declaration_expr.right->kind == FUNCTION_NODE){
	    				generateAssembly(ast->declaration_expr.right);
	    				fprintf(filePointer, "MOV %s, tempVar%d;\n",  ast->declaration_expr.id, tempCount);
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
	    	fprintf(filePointer, "TEMP tempVar%d;\n", tempCount);
	    	generateAssembly(ast->construt_expr.right);
	    	return s;
	      	break;

	    case NESTED_SCOPE_NODE:
	    	printf("NESTED SCOPE\n");
	    	if(ast->nest_scope_expr.scope != NULL){
	    		generateAssembly(ast->nest_scope_expr.scope);
	    	}
	      	break;

	    case DECLARATIONS_NODE:
	    	printf("DECLARATIONS\n");
	    	if(ast->declarations_expr.left != NULL){
	    		generateAssembly(ast->declarations_expr.left);
	    	}
	    	if(ast->declarations_expr.right != NULL){
	    		generateAssembly(ast->declarations_expr.right);
	    	}
	      	break;

	    case ARGUMENTS_NODE:
	    	if(ast->arguments_expr.left != NULL)
	    		generateAssembly(ast->arguments_expr.left);
	    	if(argumentsCount == 0){
	    		fprintf(filePointer, "MOV tempVar%d.x, ", tempCount);
	    		generateAssembly(ast->arguments_expr.right);
	    		argumentsCount += 1;
	    		fprintf(filePointer, ";\n");
	    	}else if(argumentsCount == 1){
	    		fprintf(filePointer, "MOV tempVar%d.y, ", tempCount);
	    		generateAssembly(ast->arguments_expr.right);
	    		argumentsCount += 1;
	    		fprintf(filePointer, ";\n");
	    	}else if(argumentsCount == 2){
	    		fprintf(filePointer, "MOV tempVar%d.z, ", tempCount);
	    		generateAssembly(ast->arguments_expr.right);
	    		argumentsCount += 1;
	    		fprintf(filePointer, ";\n");
	    	}else if(argumentsCount == 3){
	    		fprintf(filePointer, "MOV tempVar%d.w, ", tempCount);
	    		generateAssembly(ast->arguments_expr.right);
	    		argumentsCount += 1;
	    		fprintf(filePointer, ";\n");
	    	}
	      	break;

	    case ARGUMENTS_OPT_NODE:
	    	generateAssembly(ast->arguments_opt_expr.argum);
	    	argumentsCount = 0;
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