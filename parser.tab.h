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
     TRUEBOOL = 284,
     FALSEBOOL = 285,
     BOOL = 286,
     BVEC2 = 287,
     BVEC3 = 288,
     BVEC4 = 289,
     INT = 290,
     IVEC2 = 291,
     IVEC3 = 292,
     IVEC4 = 293,
     FLOAT = 294,
     VEC2 = 295,
     VEC3 = 296,
     VEC4 = 297,
     CONST = 298,
     VOID = 299,
     IFSYM = 300,
     ELSESYM = 301,
     WHILESYM = 302,
     DP3 = 303,
     LIT = 304,
     RSQ = 305,
     GLCOLOR = 306,
     GLDEPTH = 307,
     GLCOORD = 308,
     GLTEX = 309,
     GLC = 310,
     GLSEC = 311,
     GLFOG = 312,
     GLLHALF = 313,
     GLLAMBIENT = 314,
     GLMS = 315,
     ENV1 = 316,
     ENV2 = 317,
     ENV3 = 318,
     IDENT = 319,
     NUMBER = 320,
     FLOATNUMBER = 321
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
#define TRUEBOOL 284
#define FALSEBOOL 285
#define BOOL 286
#define BVEC2 287
#define BVEC3 288
#define BVEC4 289
#define INT 290
#define IVEC2 291
#define IVEC3 292
#define IVEC4 293
#define FLOAT 294
#define VEC2 295
#define VEC3 296
#define VEC4 297
#define CONST 298
#define VOID 299
#define IFSYM 300
#define ELSESYM 301
#define WHILESYM 302
#define DP3 303
#define LIT 304
#define RSQ 305
#define GLCOLOR 306
#define GLDEPTH 307
#define GLCOORD 308
#define GLTEX 309
#define GLC 310
#define GLSEC 311
#define GLFOG 312
#define GLLHALF 313
#define GLLAMBIENT 314
#define GLMS 315
#define ENV1 316
#define ENV2 317
#define ENV3 318
#define IDENT 319
#define NUMBER 320
#define FLOATNUMBER 321




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 58 "parser.y"

  int num;
  char *id;
  float fnum;



/* Line 2068 of yacc.c  */
#line 190 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


