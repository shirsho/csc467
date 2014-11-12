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
    s->type = type;
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

/*void pushFunc(int type, char const *name){
	struct symbol *s = NULL;
	s = (struct symbol*)malloc(sizeof(struct symbol));
	s->name = (char *) malloc (strlen (name) + 1);
	s->name = name;
	s->type = type;
	printf("identified function %s of type %d\n",s->name,s->type);

	if(!exists_Sym_glob(name)){
        LL_APPEND(symtable,s);
        printf("appending function %s to global table \n",name);
        printf("-----------------------------------------------------------------\n");
	}

	currentScope = s;
	printf("set current scope to %s\n",currentScope->name);
	printf("-----------------------------------------------------------------\n");
}*/

void resetScope(){
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

    //LL_FOREACH(symtable,s){
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

    //LL_FOREACH(currentScope,s){
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
    //LL_FOREACH(symtable,s)
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

    //LL_FOREACH(symtable,s)
    for(s = symtable; s != NULL; s = s->next){
        printf("|type:%d name:%s| \n",s->type,s->name);
    }
    //LL_FOREACH(currentScope,s)
    if(currentScope != NULL){
	    for(s = currentScope->next; s != NULL; s = s->next){
	    	printf("\t\t\t|type:%d name:%s| \n",s->type,s->name);
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