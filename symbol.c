#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

symbol *head = NULL;
symbol *currentScope = NULL;
symbol *previousScope = NULL;
int ScopeCount = 0;

/*Add the variable to the symbol table*/
void pushVar(char *name, int type, int constant) {
    struct symbol *s = NULL;
    s = (struct symbol*)malloc(sizeof(struct symbol));
    s->name = name;
    s->type_int = type;
    s->constant = constant;
    //Get the type in a string format
    switch(type){
    	case 1: 
    		s->type = (char *)"int";
    		break;
    	case 2: 
    		s->type = (char *)"bool";
    		break;
    	case 3: 
    		s->type = (char *)"float";
    		break;
    	case 11: 
    		s->type = (char *)"ivec2";
    		break;
    	case 12: 
    		s->type = (char *)"ivec3";
    		break;
    	case 13: 
    		s->type = (char *)"ivec4";
    		break;
    	case 21: 
    		s->type = (char *)"bvec2";
    		break;
    	case 22: 
    		s->type = (char *)"bvec3";
    		break;
    	case 23: 
    		s->type = (char *)"bvec4";
    		break;
    	case 31: 
    		s->type = (char *)"vec2";
    		break;
    	case 32: 
    		s->type = (char *)"vec3";
    		break;
    	case 33: 
    		s->type = (char *)"vec4";
    		break;
    }

    //Assign the scope of the variable
    if(ScopeCount != 1){
        s->var.scope = currentScope;
        //printf("identified a variable \"%s\" in the scope of function \"%d\"\n",s->name,s->var.scope->scope);
    }
    else
    {   // Do nothing
        //printf("identified a global variable \"%s\"\n",s->name);
    } 
    
    //Look for the variable in the symbol table
    if(ScopeCount == 1)
        if(!exists_Sym_glob(name)){
            //printf("appending symbol \"%s\" to global symboltable \n",name);
            //printf("-----------------------------------------------------------------\n");
            s->next = NULL;
            symbol *tmp = currentScope->symtable;
            if(tmp == NULL){
            	currentScope->symtable = s;
            }else{
            	while(tmp->next != NULL){
            		tmp = tmp->next;
            	}
            	tmp->next = s;
            }
        }else return;
    else if(!exists_Sym_loc(name)){
        //printf("appending symbol \"%s\" to local table \"%d\" \n",name, currentScope->scope);
        //printf("-----------------------------------------------------------------\n");
        s->next = NULL;
        symbol *tmp = currentScope->symtable;
        if(tmp == NULL){
        	currentScope->symtable = s;
        }else{
        	while(tmp->next != NULL){
        		tmp = tmp->next;
        	}
        	tmp->next = s;
        }
    }
}

/*Moves the scope back 1 when the nested scope is finished*/
struct symbol* resetScope(){
    //debug_printSymbolTable();
    symbol *s = head;
    symbol *t = NULL;
    //Find the scope that is right before the previous one and then assign it to current scope
    if(currentScope != head){
        while(s->next != currentScope)
            s = s->next;
    }
    currentScope = s;
    t = currentScope->next;
    currentScope->next = NULL;
    ScopeCount--;
    //printf("reset scope to %d\n", currentScope->scope);
    //printf("-----------------------------------------------------------------\n");

    //Return the scope for the ast to use
    return t;
}

/*Search the global symbol table for the variable to see if it was previously declared*/
int exists_Sym_glob(char const *name){
    symbol *s = NULL;
    //printf("searching for symbol \"%s\" in global table\n",name);
    if(currentScope->symtable == NULL){
        //fprintf(errorFile, "ERROR   --      global symboltable is empty \n");
        //errorOccurred = 1;
        return 0;
    }

    for(s = currentScope->symtable; s != NULL; s = s->next){  
        if (!strcmp(name, s->name)){
        	fprintf(errorFile, "ERROR   --      multiple declaration of variable \"%s\"\n", name);
            errorOccurred = 1;
            return 1;
     	}
    }
    //printf("cannot find a symbol with the same declaration\n");
    return 0;
}

/*Search the local symbol table for the variable to see if it was previously declared*/
int exists_Sym_loc(char const *name){
    symbol *s = NULL;
    //printf("searching for symbol \"%s\" in table \"%d\"\n",name,currentScope->scope);
    if(currentScope->symtable == NULL){
        //printf("local table \"%d\" is empty\n", currentScope->scope);
        return 0;
    }

    if(currentScope->symtable != NULL){
	    for(s = currentScope->symtable; s != NULL; s = s->next){
	        if (!strcmp(name, s->name)){
		        fprintf(errorFile, "ERROR   --      multiple declaration of variable \"%s\n", name);
                errorOccurred = 1;
	            return 1;
	        }
	    }
    }
    //printf("cannot find a symbol with the same declaration\n");
    return 0;
}

/*Search the symbol table for a variable*/
struct symbol* find_Sym(char const *name){
    symbol *s = NULL;
    for(s = currentScope->symtable; s != NULL; s = s->next){ 
        if (!strcmp(name, s->name)){
            //printf("\nfound symbol %s\n",name);
            return s;
        }
    }
    return NULL;
}

/*Search the symbol table for a variable*/
struct symbol* find_Sym_External(char const *name){
    symbol *s = NULL;
    for(s = currentScope->symtable; s != NULL; s = s->next){ 
        if (!strcmp(name, s->name)){
            //printf("\nfound symbol %s\n",name);
            return s;
        }
    }
    return NULL;
}

/*Print out the symbol table, but not used since this isn't required*/
void debug_printSymbolTable(){
    symbol *s = NULL;
    symbol *t = NULL;

    printf("\n\n\t\t - DEBUG ___ SYMBOL _ TABLE ___ DEBUG - \n\n");
    printf("-----------------------------------------------------------------\n");
    printf("     global \t\t|     local\n");
    printf("-----------------------------------------------------------------\n");

    for(t = head; t != NULL; t = t->next){
        for(s = t->symtable; s != NULL; s = s->next){
            if(t->next != NULL){
                printf("|type:%s name:%s| \n",s->type,s->name);
            }else if(t->scope == 1){
                printf("|type:%s name:%s| \n",s->type,s->name);
            }else{
                printf("\t\t\t|type:%s name:%s| \n",s->type,s->name);
            }
        }
    }
}

/*Make a new scope for each nested scope*/
void newScope(){
	ScopeCount = ScopeCount + 1;		
	struct symbol *s = NULL;
    s = (struct symbol*)malloc(sizeof(struct symbol));
    s->scope = ScopeCount;
    s->symtable = NULL;
    //printf("making new scope %d\n", s->scope);
    //printf("-----------------------------------------------------------------\n");
    if(head == NULL)
        head = s;
    if(currentScope == NULL){
        currentScope = s;
    }else{
        currentScope->next = s;
        currentScope = currentScope->next;
    }
}
