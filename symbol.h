#ifndef _SYMBOL_H
#define _SYMBOL_H

#include <stdio.h>

typedef union{
        int value;
        struct symbol *scope;
}variable;

typedef union{
        int returntype;
}function;

typedef struct symbol {
    char const *name;
    int type;
    variable var;
    function func;
    struct symbol *next;
    int scope;
} symbol;


void pushVar(char const *name, int type);

void pushFunc(int type, char const *name);

struct symbol* find_Sym(char const *name);

int exists_Sym_glob(char const *name);

int exists_Sym_loc(char const *name);

void resetScope();

void debug_printSymbolTable();

void init_table();

void newScope();

#endif