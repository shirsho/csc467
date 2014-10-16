%{
/**********************************************************************
 *
 * Justin Canton, 1000017910
 * Samprit
 *
 *  Interface to the scanner module for CSC467 course project
 **********************************************************************/


#include "common.h"
#include "parser.tab.h"
#include "string.h"


#define YY_USER_INIT { yyin = inputFile; }
#define	yyinput      input
#define yTRACE(x)    { if (traceScanner) fprintf(traceFile, "TOKEN %3d : %s\n", x, yytext); }
#define yERROR(x)    { fprintf(errorFile, "\nLEXICAL ERROR, LINE %d: %s\n", yyline, x); errorOccurred = TRUE; yyterminate(); }

int CheckInt(void);
int yyline = 1;

%}
%option noyywrap

WS          [ \t]
digit       [0-9]
letter      [a-zA-Z]

%%
"/*"        {
              int c1      = 0;
              int c2      = yyinput();
              int curline = yyline;
              for(;;) {
                if (c2 == EOF) {
                  fprintf(errorFile, "\nLEXICAL ERROR, LINE %d: Unmatched /*\n", curline);
                  errorOccurred = TRUE;
                  yyterminate();
                }
                if (c1 == '*' && c2 == '/'){
                  yTRACE(COMMENT);
                  break;
                }
                c1 = c2;
                c2 = yyinput();
                if (c1 == '\n' && c2 != EOF)
                  yyline++;
              }
            }

 /*********************************
 *Operators
 *********************************/
"+"         { yTRACE(PLUS);
              return PLUS;       }
"-"         { yTRACE(MINUS);
              return MINUS;      }
"*"         { yTRACE(TIMES);
              return TIMES;      }
"/"         { yTRACE(SLASH);
              return SLASH;      }
"="         { yTRACE(EQUAL);
              return EQUAL;      }
"!"         { yTRACE(NOT);
              return NOT;        }
"^"         { yTRACE(POWER);
              return POWER;      }
"=="        { yTRACE(EQL);
              return EQL;        }
"!="        { yTRACE(NEQL);
              return NEQL;       }
"<"         { yTRACE(LSS);
              return LSS;        }
">"         { yTRACE(GTR);
              return GTR;        }
"<="        { yTRACE(LEQ);
              return LEQ;        }
">="        { yTRACE(GEQ);
              return GEQ;        }
"&&"        { yTRACE(ANDAND);
              return ANDAND;     }
"||"        { yTRACE(OROR);
              return OROR;       }

 /*********************************
 *Terminal Symbols
 *********************************/
"("         { yTRACE(LPAREN);
              return LPAREN;     }
")"         { yTRACE(RPAREN);
              return RPAREN;     }
"["         { yTRACE(LBRACKET);
              return LBRACKET;   }
"]"         { yTRACE(RBRACKET);
              return RBRACKET;   }
";"         { yTRACE(SEMICOLON); 
              return SEMICOLON;  }
","         { yTRACE(COMMA);
              return COMMA;      }
"."         { yTRACE(PERIOD);
              return PERIOD;     }

 /*********************************
 *Boolean Variables
 *********************************/
"true"      { yTRACE(TRUEBOOL);
              return TRUEBOOL;   }
"false"     { yTRACE(FALSEBOOL);
              return FALSEBOOL;  }

 /*********************************
 *Types
 *********************************/
"bool"      { yTRACE(BOOL);
              return BOOL;       }
"bvec2"     { yTRACE(BVEC2);
              return BVEC2;      }
"bvec3"     { yTRACE(BVEC3);
              return BVEC3;      }
"bvec4"     { yTRACE(BVEC4);
              return BVEC4;      }
"int"       { yTRACE(INT);
              return INT;        }
"ivec2"     { yTRACE(IVEC2);
              return IVEC2;      }
"ivec3"     { yTRACE(IVEC3);
              return IVEC3;      }
"ivec4"     { yTRACE(IVEC4);
              return IVEC4;      }
"float"     { yTRACE(FLOAT); 
              return FLOAT;      }
"vec2"      { yTRACE(VEC2);
              return VEC2;       }
"vec3"      { yTRACE(VEC3);
              return VEC3;       }
"vec4"      { yTRACE(VEC4);
              return VEC4;       }
"const"     { yTRACE(CONST);
              return CONST;      }
"void"      { yTRACE(VOID);
              return VOID;       }

 /*********************************
 *Statements
 *********************************/
"if"        { yTRACE(IFSYM);
              return IFSYM;      }
"else"        { yTRACE(ELSESYM);
              return ELSESYM;      }
"while"     { yTRACE(WHILESYM);
              return WHILESYM;   }

 /*********************************
 *Function Names
 *********************************/
"dp3"       { yTRACE(DP3);
              return DP3;        }
"lit"       { yTRACE(LIT);
              return LIT;        }
"rsq"       { yTRACE(RSQ);
              return RSQ;        }

[ \t\r]            /* skip whitespace */
[\n]                yyline++;

 /*********************************
 *Identifiers
 *********************************/
{letter}({letter}|{digit})* {
                       yylval.id = strdup(yytext);
                       yTRACE(IDENT);
                       return IDENT;      }
{digit}+             { yylval.num = atoi(yytext);
                       yTRACE(NUMBER);
                       return NUMBER;     }
{digit}*"."{digit}*    { yylval.fnum = atof(yytext);
                       yTRACE(FLOATNUMBER);
                       return FLOATNUMBER;     }

.           { yERROR("Unknown token"); }

%%