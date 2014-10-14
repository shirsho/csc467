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
     TRUEBOOL = 282,
     FALSEBOOL = 283,
     BOOL = 284,
     BVEC2 = 285,
     BVEC3 = 286,
     BVEC4 = 287,
     INT = 288,
     IVEC2 = 289,
     IVEC3 = 290,
     IVEC4 = 291,
     FLOAT = 292,
     VEC2 = 293,
     VEC3 = 294,
     VEC4 = 295,
     CONST = 296,
     VOID = 297,
     IFSYM = 298,
     ELSESYM = 299,
     WHILESYM = 300,
     DP3 = 301,
     LIT = 302,
     RSQ = 303,
     IDENT = 304,
     NUMBER = 305,
     COMMENT = 306
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
#define TRUEBOOL 282
#define FALSEBOOL 283
#define BOOL 284
#define BVEC2 285
#define BVEC3 286
#define BVEC4 287
#define INT 288
#define IVEC2 289
#define IVEC3 290
#define IVEC4 291
#define FLOAT 292
#define VEC2 293
#define VEC3 294
#define VEC4 295
#define CONST 296
#define VOID 297
#define IFSYM 298
#define ELSESYM 299
#define WHILESYM 300
#define DP3 301
#define LIT 302
#define RSQ 303
#define IDENT 304
#define NUMBER 305
#define COMMENT 306




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 57 "parser.y"

  int num;
  char *id;



/* Line 2068 of yacc.c  */
#line 159 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


