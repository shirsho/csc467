/*
Justin Canton, 1000017910
Samprit Raihan, 998138830
*/

#ifndef _SYMBOL_H
#define _SYMBOL_H

#include <stdio.h>
#include "common.h"

typedef union{
        int value;
        struct symbol *scope;
}variable;

typedef struct symbol {
    char *name;
    char *type;
    variable var;
    int type_int;
    int constant;
    struct symbol *symtable;
    struct symbol *next;
    int scope;
} symbol;


void pushVar(char *name, int type, int constant);

void pushFunc(int type, char const *name);

struct symbol* find_Sym(char const *name);

struct symbol* find_Sym_External(char const *name);

int exists_Sym_glob(char const *name);

int exists_Sym_loc(char const *name);

struct symbol* resetScope();

void debug_printSymbolTable();

void init_table();

void newScope();

#endif
