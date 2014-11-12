#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

symbol *symtable = NULL;
symbol *currentScope = NULL;
int ScopeCount = 0;


void pushVar(char const *name, int type) {
    struct symbol *s = NULL;
    s = (struct symbol*)malloc(sizeof(struct symbol));
    s->name = (char *) malloc (strlen (name) + 1);
    s->name = name;
    switch(type){
    	case 1: 
    		s->type = "int";
    		break;
    	case 2: 
    		s->type = "bool";
    		break;
    	case 3: 
    		s->type = "float";
    		break;
    	case 11: 
    		s->type = "ivec2";
    		break;
    	case 12: 
    		s->type = "ivec3";
    		break;
    	case 13: 
    		s->type = "ivec4";
    		break;
    	case 21: 
    		s->type = "bvec2";
    		break;
    	case 22: 
    		s->type = "bvec3";
    		break;
    	case 23: 
    		s->type = "bvec4";
    		break;
    	case 31: 
    		s->type = "vec2";
    		break;
    	case 32: 
    		s->type = "vec3";
    		break;
    	case 33: 
    		s->type = "vec4";
    		break;
    }

    if(currentScope != NULL){
        s->var.scope = currentScope;
        printf("identified a variable \"%s\" in the scope of function \"%d\"\n",s->name,s->var.scope->scope);
    }else printf("identified a global variable \"%s\"\n",s->name);

    if(ScopeCount == 1)
        if(!exists_Sym_glob(name)){
            printf("appending symbol \"%s\" to global symboltable \n",name);
            printf("-----------------------------------------------------------------\n");
            s->next = NULL;
            symbol *tmp = symtable;
            if(tmp == NULL){
            	symtable = s;
            }else{
            	while(tmp->next != NULL){
            		tmp = tmp->next;
            	}
            	tmp->next = s;
            }
        }else return;
    else if(!exists_Sym_loc(name)){
        printf("appending symbol \"%s\" to local table \"%d\" \n",name, currentScope->scope);
        printf("-----------------------------------------------------------------\n");
        s->next = NULL;
        symbol *tmp = currentScope;
        if(tmp == NULL){
        	currentScope = s;
        }else{
        	while(tmp->next != NULL){
        		tmp = tmp->next;
        	}
        	tmp->next = s;
        }
    }
}

void resetScope(){
    debug_printSymbolTable();
    currentScope=NULL;
    printf("reset scope to global\n");
    printf("-----------------------------------------------------------------\n");
}

int exists_Sym_glob(char const *name){
    symbol *s = NULL;
    printf("searching for symbol \"%s\" in global table\n",name);
    if(symtable == NULL){
        printf("global symboltable is empty\n");
        return 0;
    }

    for(s = symtable; s != NULL; s = s->next){  
        if (! strcmp(name, s->name)){
        	printf("ERROR   --      multiple declaration of variable \"%s\"\n", name);
            return 1;
     	}
    }
    printf("cannot find a symbol with the same declaration\n");
    return 0;
}


int exists_Sym_loc(char const *name){
    symbol *s = NULL;
    printf("searching for symbol \"%s\" in table \"%d\"\n",name,currentScope->scope);
    if(currentScope->next == NULL){
        printf("local table \"%d\" is empty\n", currentScope->scope);
        return 0;
    }

    if(currentScope != NULL){
	    for(s = currentScope->next; s != NULL; s = s->next){
	        if (!strcmp(name, s->name)){
		        printf("ERROR   --      multiple declaration of variable \"%s\n", name);
	            return 1;
	        }
	    }
    }
    printf("cannot find a symbol with the same declaration\n");
    return 0;
}


struct symbol* find_Sym(char const *name){
    symbol *s = NULL;
    for(s = symtable; s != NULL; s = s->next){  
	    if (! strcmp(name, s->name)){
	        printf("\n found symbol %s",name);
	        return s;
	    }
	}
}

void debug_printSymbolTable(){
    symbol *s = NULL;

    printf("\n\n\t\t - DEBUG ___ SYMBOL _ TABLE ___ DEBUG - \n\n");
    printf("-----------------------------------------------------------------\n");
    printf("     global \t\t|     local\n");
    printf("-----------------------------------------------------------------\n");

    for(s = symtable; s != NULL; s = s->next){
        printf("|type:%s name:%s| \n",s->type,s->name);
    }

    if(currentScope != NULL){
	    for(s = currentScope->next; s != NULL; s = s->next){
	    	printf("\t\t\t|type:%s name:%s| \n",s->type,s->name);
	    }
	}
}

void newScope(){
	ScopeCount = ScopeCount + 1;		
	struct symbol *s = NULL;
    s = (struct symbol*)malloc(sizeof(struct symbol));
    s->scope = ScopeCount;
    printf("making new scope %d\n", s->scope);
    printf("-----------------------------------------------------------------\n");
    currentScope = s;
}