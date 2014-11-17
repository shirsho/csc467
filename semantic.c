
#include "semantic.h"

int scope = -1;
symbol *a[20];

/*Semantic check each of the different semantic cases possible*/
int semantic_check(node *ast, int assign) {
	int expr_left;
      int expr_right;
      int op;
      char *type1;
	char *type2;
	symbol *s;
	switch(ast->kind){
		case SCOPE_NODE:
			//printf("\nScope semantics\n");
			if(ast->scope_expr.left != NULL)
				semantic_check(ast->scope_expr.left, 0);
			if(ast->scope_expr.right != NULL)
				semantic_check(ast->scope_expr.right, 0);
			break;

		case BINARY_EXPRESSION_NODE:
			//printf("\nBinary semantics\n");
      		expr_left = semantic_check(ast->binary_expr.left, 0);
      		expr_right = semantic_check(ast->binary_expr.right, 0);
      		op = ast->binary_expr.op;
			type1 = get_Type(expr_left);
                  type2 = get_Type(expr_right); 

      		switch(op){
      			case '+':	
      				if(expr_left == INT && expr_right == INT){
      					return INT;
      				}else if((expr_left == FLOAT && expr_right == FLOAT) || (expr_left == INT && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == INT)){
      					return FLOAT;
      				} else if(expr_left == IVEC2 && expr_right == IVEC2){
      					return IVEC2;
      				}else if (expr_left == IVEC3 && expr_right == IVEC3){
      					return IVEC3;
      				}else if (expr_left == IVEC4 && expr_right == IVEC4){
      					return IVEC4;
      				}else if(expr_left == VEC2 && expr_right == VEC2){
      					return VEC2;
      				}else if(expr_left == VEC3 && expr_right == VEC3){
      					return VEC3;
      				}else if(expr_left == VEC4 && expr_right == VEC4){
      					return VEC4;
      				}else{
      					fprintf(errorFile, "Invalid addition between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      			case '-':
      				if(expr_left == INT && expr_right == INT){
      					return INT;
      				}else if((expr_left == FLOAT && expr_right == FLOAT) || (expr_left == INT && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == INT)){
      					return FLOAT;
      				} else if(expr_left == IVEC2 && expr_right == IVEC2){
      					return IVEC2;
      				}else if (expr_left == IVEC3 && expr_right == IVEC3){
      					return IVEC3;
      				}else if (expr_left == IVEC4 && expr_right == IVEC4){
      					return IVEC4;
      				}else if(expr_left == VEC2 && expr_right == VEC2){
      					return VEC2;
      				}else if(expr_left == VEC3 && expr_right == VEC3){
      					return VEC3;
      				}else if(expr_left == VEC4 && expr_right == VEC4){
      					return VEC4;
      				}else{
      					fprintf(errorFile, "Invalid subtraction between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      			case '*':
      				if(expr_left == INT && expr_right == INT){
      					return INT;
      				}else if((expr_left == FLOAT && expr_right == FLOAT) || (expr_left == INT && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == INT)){
      					return FLOAT;
      				} else if(expr_left == IVEC2 && expr_right == IVEC2){
      					return IVEC2;
      				}else if (expr_left == IVEC3 && expr_right == IVEC3){
      					return IVEC3;
      				}else if (expr_left == IVEC4 && expr_right == IVEC4){
      					return IVEC4;
      				}else if(expr_left == VEC2 && expr_right == VEC2){
      					return VEC2;
      				}else if(expr_left == VEC3 && expr_right == VEC3){
      					return VEC3;
      				}else if(expr_left == VEC4 && expr_right == VEC4){
      					return VEC4;
      				}else if((expr_left == VEC2 && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == VEC2)){
      					return VEC2;
      				}else if((expr_left == VEC3 && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == VEC3)){
      					return VEC3;
      				}else if((expr_left == VEC4 && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == VEC4)){
      					return VEC4;
      				}else if((expr_left == IVEC2 && expr_right == INT) || (expr_left == INT && expr_right == IVEC2)){
      					return VEC2;
      				}else if((expr_left == IVEC3 && expr_right == INT) || (expr_left == INT && expr_right == IVEC3)){
      					return VEC3;
      				}else if((expr_left == IVEC3 && expr_right == INT) || (expr_left == INT && expr_right == IVEC3)){
      					return VEC4;
      				}else{
      					fprintf(errorFile, "Invalid multiplication between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      			case '/':
      				if(expr_left == INT && expr_right == INT){
      					return INT;
      				}else if((expr_left == FLOAT && expr_right == FLOAT) || (expr_left == INT && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == INT)){
      					return FLOAT;
      				}else{
      					fprintf(errorFile, "Invalid division between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      			case '^':
      				if(expr_left == INT && expr_right == INT){
      					return INT;
      				}else if((expr_left == FLOAT && expr_right == FLOAT) || (expr_left == INT && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == INT)){
      					return FLOAT;
      				}else{
      					fprintf(errorFile, "Invalid division between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      			case AND:
      				if(expr_left == BOOL && expr_right == BOOL){
      					return BOOL;
      				}else if(expr_left == BVEC2 && expr_right == BVEC2){
      					return VEC2;
      				}else if(expr_left == BVEC3 && expr_right == BVEC3){
      					return VEC3;
      				}else if(expr_left == BVEC4 && expr_right == BVEC4){
      					return VEC4;
      				}else{
      					fprintf(errorFile, "Invalid logical AND between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      			case OR:
      				if(expr_left == BOOL && expr_right == BOOL){
      					return BOOL;
      				}else if(expr_left == BVEC2 && expr_right == BVEC2){
      					return VEC2;
      				}else if(expr_left == BVEC3 && expr_right == BVEC3){
      					return VEC3;
      				}else if(expr_left == BVEC4 && expr_right == BVEC4){
      					return VEC4;
      				}else{
      					fprintf(errorFile, "Invalid logical OR between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      			case '>':
      				if(expr_left == INT && expr_right == INT){
      					return BOOL;
      				}else if((expr_left == FLOAT && expr_right == FLOAT) || (expr_left == INT && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == INT)){
      					return BOOL;
      				}else{
      					fprintf(errorFile, "Invalid greater than comparison between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      			case '<':
      				if(expr_left == INT && expr_right == INT){
      					return BOOL;
      				}else if((expr_left == FLOAT && expr_right == FLOAT) || (expr_left == INT && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == INT)){
      					return BOOL;
      				}else{
      					fprintf(errorFile, "Invalid less than between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      			case GEQ:
      				if(expr_left == INT && expr_right == INT){
      					return BOOL;
      				}else if((expr_left == FLOAT && expr_right == FLOAT) || (expr_left == INT && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == INT)){
      					return BOOL;
      				}else{
      					fprintf(errorFile, "Invalid greater than or equal to comparison between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      			case LEQ:
      				if(expr_left == INT && expr_right == INT){
      					return BOOL;
      				}else if((expr_left == FLOAT && expr_right == FLOAT) || (expr_left == INT && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == INT)){
      					return BOOL;
      				}else{
      					fprintf(errorFile, "Invalid less than or equal to between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      			case EQ:
      				if(expr_left == INT && expr_right == INT){
      					return BOOL;
      				}else if((expr_left == FLOAT && expr_right == FLOAT) || (expr_left == INT && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == INT)){
      					return BOOL;
      				} else if(expr_left == IVEC2 && expr_right == IVEC2){
      					return BOOL;
      				}else if (expr_left == IVEC3 && expr_right == IVEC3){
      					return BOOL;
      				}else if (expr_left == IVEC4 && expr_right == IVEC4){
      					return BOOL;
      				}else if(expr_left == VEC2 && expr_right == VEC2){
      					return BOOL;
      				}else if(expr_left == VEC3 && expr_right == VEC3){
      					return BOOL;
      				}else if(expr_left == VEC4 && expr_right == VEC4){
      					return BOOL;
      				}else{
      					fprintf(errorFile, "Invalid equals comparison between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      			case NEQ:
      				if(expr_left == INT && expr_right == INT){
      					return BOOL;
      				}else if((expr_left == FLOAT && expr_right == FLOAT) || (expr_left == INT && expr_right == FLOAT) || (expr_left == FLOAT && expr_right == INT)){
      					return BOOL;
      				} else if(expr_left == IVEC2 && expr_right == IVEC2){
      					return BOOL;
      				}else if (expr_left == IVEC3 && expr_right == IVEC3){
      					return BOOL;
      				}else if (expr_left == IVEC4 && expr_right == IVEC4){
      					return BOOL;
      				}else if(expr_left == VEC2 && expr_right == VEC2){
      					return BOOL;
      				}else if(expr_left == VEC3 && expr_right == VEC3){
      					return BOOL;
      				}else if(expr_left == VEC4 && expr_right == VEC4){
      					return BOOL;
      				}else{
      					fprintf(errorFile, "Invalid not equals comparison between type %s and type %s\n", type1, type2);
      					errorOccurred = 1;
      					return 0;
      				}
      		}
      		break;

	      case UNARY_EXPRESSION_NODE:
	    	      //printf("\nUnary semantics\n");
	      	expr_right = semantic_check(ast->unary_expr.right, 0);
			type1 = get_Type(expr_right);

			switch(ast->unary_expr.op){
				case UMINUS:
					if(expr_right == INT){
						return INT;
					}else if(expr_right == FLOAT){
						return FLOAT;
					}else if(expr_right == IVEC2){
						return IVEC2;
					}else if(expr_right == IVEC3){
						return IVEC3;
					}else if(expr_right == IVEC4){
						return IVEC4;
					}else if(expr_right == VEC2){
						return VEC2;
					}else if(expr_right == VEC3){
						return VEC3;
					}else if(expr_right == VEC4){
						return VEC4;
					}else{
						fprintf(errorFile, "Invalid unary minus with type %s\n", type1);
      					errorOccurred = 1;
      					return 0;
					}
				case '!':
					if(expr_right == BOOL){
						return BOOL;
					}else if(expr_right == BVEC2){
						return BVEC2;
					}else if(expr_right == BVEC3){
						return BVEC3;
					}else if(expr_right == BVEC4){
						return BVEC4;
					}else{
						fprintf(errorFile, "Invalid not with type %s\n", type1);
      					errorOccurred = 1;
      					return 0;
					}
			}
	      	break;

	      case INT_NODE:
	      	return INT;
	      	break;

	      case FLOAT_NODE:
	      	return FLOAT;
	      	break;

	      case BOOL_NODE:
	      	return BOOL;
	     	     break;

	      case VAR_NODE:
      	    	//printf("\nVariable Semantics\n");
          		
                  s = find_Symbol(ast->var_expr.id);

                  if(s == NULL)
                        break;

            	if(s->constant == 1 && assign == 1){
            		fprintf(errorFile, "Invalid asignment to variable %s with constant value\n", ast->var_expr.id);
      			errorOccurred = 1;
      			return CONSTANT;
            	}

            	switch(s->type_int){
      			case 1:					
      				if(ast->var_expr.arr != -1){
      					fprintf(errorFile, "Invalid syntax, int variable is not array addressable\n");
      					errorOccurred = 1;
      					return 0;
      				}else{
      					return INT;
      				}
      				break;
      			case 3:
      				if(ast->var_expr.arr != -1){
      					fprintf(errorFile, "Invalid syntax, int variable is not array addressable\n");
      					errorOccurred = 1;
      					return 0;
      				}else{
      					return FLOAT;
      				}
      				break;
      			case 2:
      				if(ast->var_expr.arr != -1){
      					fprintf(errorFile, "Invalid syntax, int variable is not array addressable\n");
      					errorOccurred = 1;
      					return 0;
      				}else{
      					return BOOL;
      				}
      				break;
      			case 11:
      				if(ast->var_expr.arr >= 2 || ast->var_expr.arr < -1){
      					fprintf(errorFile, "Invalid syntax, %d is out of ivec2 array addressable range\n", ast->var_expr.arr);
      					errorOccurred = 1;
      					return 0;
      				}else if(ast->var_expr.arr == -1){
      					return IVEC2;
      				}else{
      					return INT;
      				}
      				break;
      			case 12:
      				if(ast->var_expr.arr >= 3 || ast->var_expr.arr < -1){
      					fprintf(errorFile, "Invalid syntax, %d is out of ivec3 array addressable range\n", ast->var_expr.arr);
      					errorOccurred = 1;
      					return 0;
      				}else if(ast->var_expr.arr == -1){
      					return IVEC3;
      				}else{
      					return INT;
      				}
      				break;
      			case 13:
      				if(ast->var_expr.arr >= 4 || ast->var_expr.arr < -1){
      					fprintf(errorFile, "Invalid syntax, %d is out of ivec4 array addressable range\n", ast->var_expr.arr);
      					errorOccurred = 1;
      					return 0;
      				}else if(ast->var_expr.arr == -1){
      					return IVEC4;
      				}else{
      					return INT;
      				}
      				break;
      			case 31:
      				if(ast->var_expr.arr >= 2 || ast->var_expr.arr < -1){
      					fprintf(errorFile, "Invalid syntax, %d is out of vec2 array addressable range\n", ast->var_expr.arr);
      					errorOccurred = 1;
      					return 0;
      				}else if(ast->var_expr.arr == -1){
      					return VEC2;
      				}else{
      					return FLOAT;
      				}
      				break;
      			case 32:
      				if(ast->var_expr.arr >= 3 || ast->var_expr.arr < -1){
      					fprintf(errorFile, "Invalid syntax, %d is out of vec3 array addressable range\n", ast->var_expr.arr);
      					errorOccurred = 1;
      					return 0;
      				}else if(ast->var_expr.arr == -1){
      					return VEC3;
      				}else{
      					return FLOAT;
      				}
      				break;
      			case 33:
      				if(ast->var_expr.arr >= 4 || ast->var_expr.arr < -1){
      					fprintf(errorFile, "Invalid syntax, %d is out of vec4 array addressable range\n", ast->var_expr.arr);
      					errorOccurred = 1;
      					return 0;
      				}else if(ast->var_expr.arr == -1){
      					return VEC4;
      				}else{
      					return FLOAT;
      				}
      				break;
      			case 21:
      				if(ast->var_expr.arr >= 2 || ast->var_expr.arr < -1){
      					fprintf(errorFile, "Invalid syntax, %d is out of bvec2 array addressable range\n", ast->var_expr.arr);
      					errorOccurred = 1;
      					return 0;
      				}else if(ast->var_expr.arr == -1){
      					return BVEC2;
      				}else{
      					return BOOL;
      				}
      				break;
      			case 22:
      				if(ast->var_expr.arr >= 3 || ast->var_expr.arr < -1){
      					fprintf(errorFile, "Invalid syntax, %d is out of bvec3 array addressable range\n", ast->var_expr.arr);
      					errorOccurred = 1;
      					return 0;
      				}else if(ast->var_expr.arr == -1){
      					return BVEC3;
      				}else{
      					return BOOL;
      				}
      				break;
      			case 23:
      				if(ast->var_expr.arr >= 4 || ast->var_expr.arr < -1){
      					fprintf(errorFile, "Invalid syntax, %d is out of bvec4 array addressable range\n", ast->var_expr.arr);
      					errorOccurred = 1;
      					return 0;
      				}else if(ast->var_expr.arr == -1){
      					return BVEC4;
      				}else{
      					return BOOL;
      				}
      				break;
      		}
            	break;

	      case DECLARATION_NODE:
	    	      //printf("\nDeclaration semantics\n");
	    	      if(ast->declaration_expr.right != NULL){
	    		     expr_right = semantic_check(ast->declaration_expr.right, 0);
		      	switch(ast->declaration_expr.type){
		      		case 1:
		      			if(expr_right == INT){
		      				return VALID;
		      			}else{
		      				fprintf(errorFile, "Invalid declaration with type int on line %d\n", ast->declaration_expr.line);
		  					errorOccurred = 1;
		  					return 0;
						}
					case 11:
		      			if(expr_right == IVEC2){
		      				return VALID;
		      			}else{
		      				fprintf(errorFile, "Invalid declaration with type ivec2 on line %d\n", ast->declaration_expr.line);
		  					errorOccurred = 1;
		  					return 0;
						}
					case 12:
		      			if(expr_right == IVEC3){
		      				return VALID;
		      			}else{
		      				fprintf(errorFile, "Invalid declaration with type ivec3 on line %d\n", ast->declaration_expr.line);
		  					errorOccurred = 1;
		  					return 0;
						}
					case 13:
		      			if(expr_right == IVEC4){
		      				return VALID;
		      			}else{
		      				fprintf(errorFile, "Invalid declaration with type ivec4 on line %d\n", ast->declaration_expr.line);
		  					errorOccurred = 1;
		  					return 0;
						}
					case 2:
		      			if(expr_right == BOOL){
		      				return VALID;
		      			}else{
		      				fprintf(errorFile, "Invalid declaration with type bool on line %d\n", ast->declaration_expr.line);
		  					errorOccurred = 1;
		  					return 0;
						}
					case 21:
		      			if(expr_right == BVEC2){
		      				return VALID;
		      			}else{
		      				fprintf(errorFile, "Invalid declaration with type bvec2 on line %d\n", ast->declaration_expr.line);
		  					errorOccurred = 1;
		  					return 0;
						}
					case 22:
		      			if(expr_right == BVEC3){
		      				return VALID;
		      			}else{
		      				fprintf(errorFile, "Invalid declaration with type bvec3 on line %d\n", ast->declaration_expr.line);
		  					errorOccurred = 1;
		  					return 0;
						}
					case 23:
		      			if(expr_right == BVEC4){
		      				return VALID;
		      			}else{
		      				fprintf(errorFile, "Invalid declaration with type bvec4 on line %d\n", ast->declaration_expr.line);
		  					errorOccurred = 1;
		  					return 0;
						}
					case 3:
		      			if(expr_right == FLOAT){
		      				return VALID;
		      			}else{
		      				fprintf(errorFile, "Invalid declaration with type float on line %d\n", ast->declaration_expr.line);
		  					errorOccurred = 1;
		  					return 0;
						}
					case 31:
		      			if(expr_right == VEC2){
		      				return VALID;
		      			}else{
		      				fprintf(errorFile, "Invalid declaration with type vec2 on line %d\n", ast->declaration_expr.line);
		  					errorOccurred = 1;
		  					return 0;
						}
					case 32:
		      			if(expr_right == VEC3){
		      				return VALID;
		      			}else{
		      				fprintf(errorFile, "Invalid declaration with type vec3 on line %d\n", ast->declaration_expr.line);
		  					errorOccurred = 1;
		  					return 0;
						}
					case 33:
		      			if(expr_right == VEC4){
		      				return VALID;
		      			}else{
		      				fprintf(errorFile, "Invalid declaration with type vec4 on line %d\n", ast->declaration_expr.line);
		  					errorOccurred = 1;
		  					return 0;
						}

	      		}
	      	}else{
	      		return VALID;
	      	}
	      	break;

	      case IF_STATEMENT_NODE:
	    	      //printf("\nIf Statement semantics\n");
	      	if(ast->if_expr.if_comparison != NULL)
	      		expr_left = semantic_check(ast->if_expr.if_comparison, 0);
	      	if(ast->if_expr.if_statement != NULL)
	      		semantic_check(ast->if_expr.if_statement, 0);
	      	if(ast->if_expr.else_statement != NULL)
	      		semantic_check(ast->if_expr.else_statement, 0);
	      	if(expr_left != BOOL){
	      		fprintf(errorFile, "Invalid expression in if statement on line %d\n", ast->if_expr.line);
      			errorOccurred = 1;
      			return 0;
	      	}else{
	      		return VALID;
	      	}
	      	break;

	      case STATEMENT_NODE:
	    	      //printf("\nStatement semantics\n");
	      	if(ast->statement_expr.left != NULL)
	      		expr_left = semantic_check(ast->statement_expr.left, 0);
	      	if(ast->statement_expr.right != NULL)
	      		expr_right = semantic_check(ast->statement_expr.right, 0);
	      	break;

	      case ASSIGNMENT_NODE:
	    	      //printf("\nAssignment semantics\n");
            	if(ast->assign_expr.left != NULL)
            		expr_left = semantic_check(ast->assign_expr.left, 1);
            	if(ast->assign_expr.right != NULL)
            		expr_right = semantic_check(ast->assign_expr.right, 0);
      		
                  type1 = get_Type(expr_left);
                  type2 = get_Type(expr_right);

      		if(expr_left == INT && expr_right == INT){
      			return VALID;
      		}else if(expr_left == FLOAT && expr_right == FLOAT){
      			return VALID;
      		} else if(expr_left == IVEC2 && expr_right == IVEC2){
      			return VALID;
      		}else if (expr_left == IVEC3 && expr_right == IVEC3){
      			return VALID;
      		}else if (expr_left == IVEC4 && expr_right == IVEC4){
      			return VALID;
      		}else if(expr_left == VEC2 && expr_right == VEC2){
      			return VALID;
      		}else if(expr_left == VEC3 && expr_right == VEC3){
      			return VALID;
      		}else if(expr_left == VEC4 && expr_right == VEC4){
      			return VALID;
      		}else if(expr_left == BOOL && expr_right == BOOL){
      			return VALID;
      		}else if(expr_left == BVEC2 && expr_right == BVEC2){
      			return VALID;
      		}else if(expr_left == BVEC3 && expr_right == BVEC3){
      			return VALID;
      		}else if(expr_left == BVEC4 && expr_right == BVEC4){
      			return VALID;
      		}else if(expr_left == CONSTANT){
      			fprintf(errorFile, "Invalid assignment to constant variable on line %d\n", ast->assign_expr.line);
      			errorOccurred = 1;
      			return 0;
      		}else{
      			fprintf(errorFile, "Invalid assignment between type %s and type %s on line %d\n", type1, type2, ast->assign_expr.line);
      			errorOccurred = 1;
      			return 0;
      		}
            	break;

	      case FUNCTION_NODE:
	    	      //printf("\nFunction semantics\n");
      	    	if(ast->func_expr.arguments != NULL)
      	    		expr_right = semantic_check(ast->func_expr.arguments, 0);
      	      	switch(ast->func_expr.func){
      	      		case FUNC1:
      	      			if(expr_right == IVEC32){
      	      				return INT;
      	      			}else if(expr_right == IVEC42){
      	      				return INT;
      	      			}else if(expr_right == VEC32){
      	      				return FLOAT;
      	      			}else if(expr_right == VEC42){
      	      				return FLOAT;
      	      			}else{
      	      				fprintf(errorFile, "Invalid arguments for dp3\n");
            					errorOccurred = 1;
            					return 0;
      	      			}
      	      			break;
      	      		case FUNC2:
      	      			if(expr_right == VEC4){
      	      				return VEC4;
      	      			}else{
      	      				fprintf(errorFile, "Invalid arguments for lit\n");
            					errorOccurred = 1;
            					return 0;
      	      			}
      	      			break;
      	      		case FUNC3:
      	      			if(expr_right == FLOAT){
      	      				return FLOAT;
      	      			}else if(expr_right == INT){
      	      				return FLOAT;
      	      			}else{
      	      				fprintf(errorFile, "Invalid arguments for rsq\n");
            					errorOccurred = 1;
            					return 0;
      	      			}
      	      			break;
      				default: 
      					fprintf(errorFile, "Invalid function\n");
                                    errorOccurred = 1;
                                    return 0;
      					break;
      	      	}
      	      	break;

	      case CONSTRUCTOR_NODE:
      	      //printf("\nConstructor semantics\n");
      	    	if(ast->construt_expr.right != NULL)
      	    		expr_right = semantic_check(ast->construt_expr.right, 0);
      	    	
      	      	switch(ast->construt_expr.type){
      				case 11:
      	      			if(expr_right == ITWO){
      	      				return IVEC2;
      	      			}else{
      	      				fprintf(errorFile, "Invalid declaration with type ivec2\n");
            					errorOccurred = 1;
            					return 0;
      					}
      					break;
      				case 12:
      	      			if(expr_right == ITHREE){
      	      				return IVEC3;
      	      			}else{
      	      				fprintf(errorFile, "Invalid declaration with type ivec3\n");
            					errorOccurred = 1;
            					return 0;
      					}
      					break;
      				case 13:
      	      			if(expr_right == IFOUR){
      	      				return IVEC4;
      	      			}else{
      	      				fprintf(errorFile, "Invalid declaration with type ivec4\n");
            					errorOccurred = 1;
            					return 0;
      					}
      					break;
      				case 21:
      	      			if(expr_right == BTWO){
      	      				return BVEC2;
      	      			}else{
      	      				fprintf(errorFile, "Invalid declaration with type bvec2\n");
            					errorOccurred = 1;
            					return 0;
      					}
      					break;
      				case 22:
      	      			if(expr_right == BTHREE){
      	      				return BVEC3;
      	      			}else{
      	      				fprintf(errorFile, "Invalid declaration with type bvec3\n");
            					errorOccurred = 1;
            					return 0;
      					}
      					break;
      				case 23:
      	      			if(expr_right == BFOUR){
      	      				return BVEC4;
      	      			}else{
      	      				fprintf(errorFile, "Invalid declaration with type bvec4\n");
            					errorOccurred = 1;
            					return 0;
      					}
      					break;
      				case 31:
      	      			if(expr_right == FTWO){
      	      				return VEC2;
      	      			}else{
      	      				fprintf(errorFile, "Invalid declaration with type vec2\n");
            					errorOccurred = 1;
            					return 0;
      					}
      					break;
      				case 32:
      	      			if(expr_right == FTHREE){
      	      				return VEC3;
      	      			}else{
      	      				fprintf(errorFile, "Invalid declaration with type vec3\n");
            					errorOccurred = 1;
            					return 0;
      					}
      					break;
      				case 33:
      	      			if(expr_right == FFOUR){
      	      				return VEC4;
      	      			}else{
      	      				fprintf(errorFile, "Invalid declaration with type vec4\n");
            					errorOccurred = 1;
            					return 0;
      					}
      					break;
      			}
      	      	break;


	      case NESTED_SCOPE_NODE:
      	    	//printf("\nNested Scope semantics\n");
            	scope = scope + 1;
            	a[scope] = ast->nest_scope_expr.variables;
            	if(ast->nest_scope_expr.scope != NULL)
            		semantic_check(ast->nest_scope_expr.scope, 0);
            	scope = scope - 1;
            	break;
		
	      case DECLARATIONS_NODE:
      	    	//printf("\nDeclarations semantics\n");
            	if(ast->declarations_expr.left != NULL)
            		semantic_check(ast->declarations_expr.left, 0);
            	if(ast->declarations_expr.right != NULL)
            		semantic_check(ast->declarations_expr.right, 0);
            	break;

	      case ARGUMENTS_NODE:
	    	      //printf("\nArguments semantics\n");
	      	if(ast->arguments_expr.left != NULL){
	      		expr_left = semantic_check(ast->arguments_expr.left, 0);
	      	}else{
	      		expr_left = 0;
	      	}

	      	if(ast->arguments_expr.right != NULL){
	      		expr_right = semantic_check(ast->arguments_expr.right, 0);
			}		
	      	
	      	switch(expr_left){
	      		case INT:
	      			if(expr_right == INT){
	      				return ITWO;
	      			}else{
	      				fprintf(errorFile, "Invalid constructor types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      			break;
	      		case ITWO:
	      			if(expr_right == INT){
	      				return ITHREE;
	      			}else{
	      				fprintf(errorFile, "Invalid constructor types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      			break;
	      		case ITHREE:
	      			if(expr_right == INT){
	      				return IFOUR;
	      			}else{
	      				fprintf(errorFile, "Invalid constructor types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      			break;
	      		case IFOUR:
	      			fprintf(errorFile, "Too many variables in the constructor\n");
      				errorOccurred = 1;
      				return 0;
	      			break;
	      		case FLOAT:
	      			if(expr_right == FLOAT){
	      				return FTWO;
	      			}else{
	      				fprintf(errorFile, "Invalid constructor types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      			break;
	      		case FTWO:
	      			if(expr_right == FLOAT){
	      				return FTHREE;
	      			}else{
	      				fprintf(errorFile, "Invalid constructor types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      			break;
	      		case FTHREE:
	      			if(expr_right == FLOAT){
	      				return FFOUR;
	      			}else{
	      				fprintf(errorFile, "Invalid constructor types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      			break;
	      		case FFOUR:
	      			fprintf(errorFile, "Too many variables in the constructor\n");
      				errorOccurred = 1;
      				return 0;
	      			break;
	      		case BOOL:
	      			if(expr_right == BOOL){
	      				return BTWO;
	      			}else{
	      				fprintf(errorFile, "Invalid constructor types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      			break;
	      		case BTWO:
	      			if(expr_right == BOOL){
	      				return BTHREE;
	      			}else{
	      				fprintf(errorFile, "Invalid constructor types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      			break;
	      		case BTHREE:
	      			if(expr_right == BOOL){
	      				return BFOUR;
	      			}else{
	      				fprintf(errorFile, "Invalid constructor types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      			break;
	      		case BFOUR:
	      			fprintf(errorFile, "Too many variables in the constructor\n");
      				errorOccurred = 1;
      				return 0;
	      			break;
	      		case IVEC3:
	      			if(expr_right == IVEC3){
	      				return IVEC32;
	      			}else{
	      				fprintf(errorFile, "Invalid function types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      		case IVEC4:
	      			if(expr_right == IVEC4){
	      				return IVEC42;
	      			}else{
	      				fprintf(errorFile, "Invalid function types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      		case VEC3:
	      			if(expr_right == VEC3){
	      				return VEC32;
	      			}else{
	      				fprintf(errorFile, "Invalid function types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      		case VEC4:
	      			if(expr_right == VEC4){
	      				return VEC42;
	      			}else{
	      				fprintf(errorFile, "Invalid function types\n");
      					errorOccurred = 1;
      					return 0;
	      			}
	      		case VEC32:
	      			fprintf(errorFile, "Too many variables in the function\n");
      				errorOccurred = 1;
      				return 0;
	      			break;
	      		case VEC42:
	      			fprintf(errorFile, "Too many variables in the function\n");
      				errorOccurred = 1;
      				return 0;
	      			break;
	      		case IVEC32:
	      			fprintf(errorFile, "Too many variables in the function\n");
      				errorOccurred = 1;
      				return 0;
	      			break;
	      		case IVEC42:
	      			fprintf(errorFile, "Too many variables in the function\n");
      				errorOccurred = 1;
      				return 0;
	      			break;
	      		case 0:
	      			return expr_right;
	      			break;
	      		default: 
	      			fprintf(errorFile, "Error occured\n");
      				errorOccurred = 1;
      				return 0;
	      			break;
	      	}
	      	break;

	      case ARGUMENTS_OPT_NODE:
      	    	//printf("\nArguments opt semantics\n");
      	    	if(ast->arguments_opt_expr.argum != NULL){
      	      		return semantic_check(ast->arguments_opt_expr.argum, 0);
      	      	}
      	      break;

	      case EXPRESSION_NODE:
	    	      //printf("\nExpression semantics\n");
	      	if(ast->expression_expr.expr != NULL);
	      		return semantic_check(ast->expression_expr.expr, 0);
	      	break;

	      default: break;
	}
  return 0; // failed checks
}

/*Return the type in string format*/
char* get_Type(int value){
      switch(value){
            case INT:
                  return (char *)"int";
                  break;
            case FLOAT:
                  return (char *)"float";
                  break;
            case BOOL:
                  return (char *)"bool";
                  break;
            case IVEC2:
                  return (char *)"ivec2";
                  break;
            case IVEC3:
                  return (char *)"ivec3";
                  break;
            case IVEC4:
                  return (char *)"ivec4";
                  break;
            case VEC2:
                  return (char *)"vec2";
                  break;
            case VEC3:
                  return (char *)"vec3";
                  break;
            case VEC4:
                  return (char *)"vec4";
                  break;
            case BVEC2:
                  return (char *)"bvec2";
                  break;
            case BVEC3:
                  return (char *)"bvec3";
                  break;
            case BVEC4:
                  return (char *)"bvec4";
                  break;
            default:
                  return (char *)"unknown";
                  break;
      }

}

/*Find the variable from the symbol table*/
symbol* find_Symbol(char *name){
      symbol *s;
      int b;
      int found = 0;
      for(b = scope; b >= 0; b--){
            for(s = a[b]->symtable; s != NULL; s = s->next){
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