#ifndef _SYMBOL_H
#define _SYMBOL_H

#include <stdio.h>

typedef union{
        int value;
        int type;
        int constant;
        struct symbol *scope;
}variable;

typedef struct symbol {
    char *name;
    char *type;
    variable var;
    struct symbol *symtable;
    struct symbol *next;
    int scope;
} symbol;


void pushVar(char *name, int type, int constant);

void pushFunc(int type, char const *name);

struct symbol* find_Sym(char const *name);

int exists_Sym_glob(char const *name);

int exists_Sym_loc(char const *name);

void resetScope();

void debug_printSymbolTable();

void init_table();

void newScope();

#endif
