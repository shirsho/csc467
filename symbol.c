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


void pushVar(char *name, int type, int constant) {
    struct symbol *s = NULL;
    s = (struct symbol*)malloc(sizeof(struct symbol));
    s->name = name;
    s->var.type = type;
    s->var.constant = constant;
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

    if(ScopeCount != 1){
        s->var.scope = currentScope;
        printf("identified a variable \"%s\" in the scope of function \"%d\"\n",s->name,s->var.scope->scope);
    }else printf("identified a global variable \"%s\"\n",s->name);

    if(ScopeCount == 1)
        if(!exists_Sym_glob(name)){
            printf("appending symbol \"%s\" to global symboltable \n",name);
            printf("-----------------------------------------------------------------\n");
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
        printf("appending symbol \"%s\" to local table \"%d\" \n",name, currentScope->scope);
        printf("-----------------------------------------------------------------\n");
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

void resetScope(){
    debug_printSymbolTable();
    symbol *s = head;
    symbol *t = NULL;
    symbol *u = NULL;
    if(currentScope != head){
        while(s->next != currentScope)
            s = s->next;
    }
    t = currentScope->symtable;
    while(t != NULL){
        u = t;
        t = t->next;
        free(u);
    }
    free(currentScope);
    currentScope = s;
    currentScope->next = NULL;
    ScopeCount--;
    printf("reset scope to %d\n", currentScope->scope);
    printf("-----------------------------------------------------------------\n");
}

int exists_Sym_glob(char const *name){
    symbol *s = NULL;
    printf("searching for symbol \"%s\" in global table\n",name);
    if(currentScope->symtable == NULL){
        printf("global symboltable is empty\n");
        return 0;
    }

    for(s = currentScope->symtable; s != NULL; s = s->next){  
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
    if(currentScope->symtable == NULL){
        printf("local table \"%d\" is empty\n", currentScope->scope);
        return 0;
    }

    if(currentScope->symtable != NULL){
	    for(s = currentScope->symtable; s != NULL; s = s->next){
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
    symbol *t = currentScope;
    symbol *u = head;
    while(u != t){
        for(s = t->symtable; s != NULL; s = s->next){
    	    if (!strcmp(name, s->name)){
    	        printf("\nfound symbol %s\n",name);
    	        return s;
    	    }
    	}
        while(u->next != t){
            u = u->next;
        }
        t = u;
        u = head;
    }
    for(s = u->symtable; s != NULL; s = s->next){ 
        if (!strcmp(name, s->name)){
            printf("\nfound symbol %s\n",name);
            return s;
        }
    }
    return NULL;
}

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

void newScope(){
	ScopeCount = ScopeCount + 1;		
	struct symbol *s = NULL;
    s = (struct symbol*)malloc(sizeof(struct symbol));
    s->scope = ScopeCount;
    s->symtable = NULL;
    printf("making new scope %d\n", s->scope);
    printf("-----------------------------------------------------------------\n");
    if(head == NULL)
        head = s;
    if(currentScope == NULL){
        currentScope = s;
    }else{
        currentScope->next = s;
        currentScope = currentScope->next;
    }
}
