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
     LCURLYBRACE = 280,
     RCURLYBRACE = 281,
     SEMICOLON = 282,
     COMMA = 283,
     PERIOD = 284,
     TRUEBOOL = 285,
     FALSEBOOL = 286,
     BOOL = 287,
     BVEC2 = 288,
     BVEC3 = 289,
     BVEC4 = 290,
     INT = 291,
     IVEC2 = 292,
     IVEC3 = 293,
     IVEC4 = 294,
     FLOAT = 295,
     VEC2 = 296,
     VEC3 = 297,
     VEC4 = 298,
     CONST = 299,
     VOID = 300,
     IFSYM = 301,
     ELSESYM = 302,
     WHILESYM = 303,
     DP3 = 304,
     LIT = 305,
     RSQ = 306,
     IDENT = 307,
     NUMBER = 308,
     FLOATNUMBER = 309
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
#define LCURLYBRACE 280
#define RCURLYBRACE 281
#define SEMICOLON 282
#define COMMA 283
#define PERIOD 284
#define TRUEBOOL 285
#define FALSEBOOL 286
#define BOOL 287
#define BVEC2 288
#define BVEC3 289
#define BVEC4 290
#define INT 291
#define IVEC2 292
#define IVEC3 293
#define IVEC4 294
#define FLOAT 295
#define VEC2 296
#define VEC3 297
#define VEC4 298
#define CONST 299
#define VOID 300
#define IFSYM 301
#define ELSESYM 302
#define WHILESYM 303
#define DP3 304
#define LIT 305
#define RSQ 306
#define IDENT 307
#define NUMBER 308
#define FLOATNUMBER 309




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 58 "parser.y"

  int num;
  char *id;
  float fnum;



/* Line 2068 of yacc.c  */
#line 166 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


