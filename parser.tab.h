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
     COMMENT = 260,
     PLUS = 261,
     MINUS = 262,
     TIMES = 263,
     SLASH = 264,
     EQUAL = 265,
     NOT = 266,
     POWER = 267,
     EQL = 268,
     NEQL = 269,
     LSS = 270,
     GTR = 271,
     LEQ = 272,
     GEQ = 273,
     ANDAND = 274,
     OROR = 275,
     LPAREN = 276,
     RPAREN = 277,
     LBRACKET = 278,
     RBRACKET = 279,
     SEMICOLON = 280,
     COMMA = 281,
     PERIOD = 282,
     TRUEBOOL = 283,
     FALSEBOOL = 284,
     BOOL = 285,
     BVEC2 = 286,
     BVEC3 = 287,
     BVEC4 = 288,
     INT = 289,
     IVEC2 = 290,
     IVEC3 = 291,
     IVEC4 = 292,
     FLOAT = 293,
     VEC2 = 294,
     VEC3 = 295,
     VEC4 = 296,
     CONST = 297,
     VOID = 298,
     IFSYM = 299,
     ELSESYM = 300,
     WHILESYM = 301,
     DP3 = 302,
     LIT = 303,
     RSQ = 304,
     IDENT = 305,
     NUMBER = 306,
     FLOATNUMBER = 307
   };
#endif
/* Tokens.  */
#define myToken1 258
#define myToken2 259
#define COMMENT 260
#define PLUS 261
#define MINUS 262
#define TIMES 263
#define SLASH 264
#define EQUAL 265
#define NOT 266
#define POWER 267
#define EQL 268
#define NEQL 269
#define LSS 270
#define GTR 271
#define LEQ 272
#define GEQ 273
#define ANDAND 274
#define OROR 275
#define LPAREN 276
#define RPAREN 277
#define LBRACKET 278
#define RBRACKET 279
#define SEMICOLON 280
#define COMMA 281
#define PERIOD 282
#define TRUEBOOL 283
#define FALSEBOOL 284
#define BOOL 285
#define BVEC2 286
#define BVEC3 287
#define BVEC4 288
#define INT 289
#define IVEC2 290
#define IVEC3 291
#define IVEC4 292
#define FLOAT 293
#define VEC2 294
#define VEC3 295
#define VEC4 296
#define CONST 297
#define VOID 298
#define IFSYM 299
#define ELSESYM 300
#define WHILESYM 301
#define DP3 302
#define LIT 303
#define RSQ 304
#define IDENT 305
#define NUMBER 306
#define FLOATNUMBER 307




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 58 "parser.y"

  int num;
  char *id;
  float fnum;



/* Line 2068 of yacc.c  */
#line 162 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


