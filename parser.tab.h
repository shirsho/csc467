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
     EQUAL = 264,
     NOT = 265,
     POWER = 266,
     EQL = 267,
     NEQL = 268,
     LSS = 269,
     GTR = 270,
     LEQ = 271,
     GEQ = 272,
     ANDAND = 273,
     OROR = 274,
     LPAREN = 275,
     RPAREN = 276,
     LBRACKET = 277,
     RBRACKET = 278,
     SEMICOLON = 279,
     COMMA = 280,
     PERIOD = 281,
     BOOL = 282,
     BVEC2 = 283,
     BVEC3 = 284,
     BVEC4 = 285,
     INT = 286,
     IVEC2 = 287,
     IVEC3 = 288,
     IVEC4 = 289,
     FLOAT = 290,
     VEC2 = 291,
     VEC3 = 292,
     VEC4 = 293,
     CONST = 294,
     VOID = 295,
     IFSYM = 296,
     ELSESYM = 297,
     WHILESYM = 298,
     DP3 = 299,
     LIT = 300,
     RSQ = 301,
     IDENT = 302,
     NUMBER = 303,
     COMMENT = 304
   };
#endif
/* Tokens.  */
#define myToken1 258
#define myToken2 259
#define PLUS 260
#define MINUS 261
#define TIMES 262
#define SLASH 263
#define EQUAL 264
#define NOT 265
#define POWER 266
#define EQL 267
#define NEQL 268
#define LSS 269
#define GTR 270
#define LEQ 271
#define GEQ 272
#define ANDAND 273
#define OROR 274
#define LPAREN 275
#define RPAREN 276
#define LBRACKET 277
#define RBRACKET 278
#define SEMICOLON 279
#define COMMA 280
#define PERIOD 281
#define BOOL 282
#define BVEC2 283
#define BVEC3 284
#define BVEC4 285
#define INT 286
#define IVEC2 287
#define IVEC3 288
#define IVEC4 289
#define FLOAT 290
#define VEC2 291
#define VEC3 292
#define VEC4 293
#define CONST 294
#define VOID 295
#define IFSYM 296
#define ELSESYM 297
#define WHILESYM 298
#define DP3 299
#define LIT 300
#define RSQ 301
#define IDENT 302
#define NUMBER 303
#define COMMENT 304




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 57 "parser.y"

  int num;
  char *id;



/* Line 2068 of yacc.c  */
#line 155 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


