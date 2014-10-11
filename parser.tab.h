/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     myToken1 = 258,
     myToken2 = 259,
     PLUS = 260,
     MINUS = 261,
     TIMES = 262,
     SLASH = 263,
     NOT = 264,
     POWER = 265,
     EQL = 266,
     NEQL = 267,
     LSS = 268,
     GTR = 269,
     LEQ = 270,
     GEQ = 271,
     ANDAND = 272,
     OROR = 273,
     LPAREN = 274,
     RPAREN = 275,
     LBRACKET = 276,
     RBRACKET = 277,
     SEMICOLON = 278,
     COMMA = 279,
     PERIOD = 280,
     BOOL = 281,
     BVEC2 = 282,
     BVEC3 = 283,
     BVEC4 = 284,
     INT = 285,
     IVEC2 = 286,
     IVEC3 = 287,
     IVEC4 = 288,
     FLOAT = 289,
     VEC2 = 290,
     VEC3 = 291,
     VEC4 = 292,
     CONST = 293,
     VOID = 294,
     IFSYM = 295,
     WHILESYM = 296,
     DP3 = 297,
     LIT = 298,
     RSQ = 299,
     IDENT = 300,
     NUMBER = 301,
     COMMENT = 302
   };
#endif
/* Tokens.  */
#define myToken1 258
#define myToken2 259
#define PLUS 260
#define MINUS 261
#define TIMES 262
#define SLASH 263
#define NOT 264
#define POWER 265
#define EQL 266
#define NEQL 267
#define LSS 268
#define GTR 269
#define LEQ 270
#define GEQ 271
#define ANDAND 272
#define OROR 273
#define LPAREN 274
#define RPAREN 275
#define LBRACKET 276
#define RBRACKET 277
#define SEMICOLON 278
#define COMMA 279
#define PERIOD 280
#define BOOL 281
#define BVEC2 282
#define BVEC3 283
#define BVEC4 284
#define INT 285
#define IVEC2 286
#define IVEC3 287
#define IVEC4 288
#define FLOAT 289
#define VEC2 290
#define VEC3 291
#define VEC4 292
#define CONST 293
#define VOID 294
#define IFSYM 295
#define WHILESYM 296
#define DP3 297
#define LIT 298
#define RSQ 299
#define IDENT 300
#define NUMBER 301
#define COMMENT 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 57 "parser.y"

  int num;



/* Line 2068 of yacc.c  */
#line 150 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


