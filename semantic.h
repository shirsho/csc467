#ifndef _SEMANTIC_H
#define _SEMANTIC_H

#include "ast.h"
#include "symbol.h"
#include "parser.tab.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT 1
#define IVEC2 2
#define IVEC3 3
#define IVEC4 4
#define FLOAT 5
#define VEC2 6
#define VEC3 7
#define VEC4 8
#define BOOL 9
#define BVEC2 10
#define BVEC3 11
#define BVEC4 12
#define ITWO 13
#define ITHREE 14
#define IFOUR 15
#define BTWO 16
#define BTHREE 17
#define BFOUR 18
#define FTWO 19
#define FTHREE 20
#define FFOUR 21
#define IVEC32 22
#define IVEC42 23
#define VEC32 24
#define VEC42 25
#define CONSTANT 26
#define VALID 27

extern int scope;
extern symbol *a[20];

int semantic_check(node *ast, int assign);
char* get_Type(int value);
symbol* find_Symbol(char *name);
#endif
