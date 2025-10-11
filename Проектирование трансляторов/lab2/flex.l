%{
#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"

void yyerror(const char *s);

%}

delim   [ \t\n\r]+
ws      {delim}+
letter  [a-zA-Z]
digit   [0-9]
integer [-]?{digit}+
id      {letter}({letter}|{digit})*
s_atom  {id}
d_atom  {integer} 

%option noyywrap
%option case-insensitive

%%
{ws}                                { /* Игнорируем пробелы */ }
"QUOTE"                             { return QUOTE; }
"CAR"                               { return CAR; }
"CDR"                               { return CDR; }
"CONS"                              { return CDR; }
"ATOM"                              { return ATOM_PREDICATE; }
"EQUAL"                             { return EQUAL; }
"ADD"                               { return ADD; } 
"SUB"                               { return SUB; }
"MUL"                               { return MUL; }
"DIVE"                              { return DIVE; }
"REM"                               { return REM; }
"LE"                                { return LE; }
"COND"                              { return COND; }
"LAMBDA"                            { return LAMBDA; }
"LET"                               { return LET; }
"LETREC"                            { return LETREC; }
{s_atom}                            { yylval.str = strdup(yytext); return S_ATOM; }
{d_atom}                            { yylval.num = atoi(yytext); return D_ATOM; }
"("                                 { return LEFT_PARENTHESIS; }
")"                                 { return RIGHT_PARENTHESIS; }
<<EOF>>                             { return 0;}
.                                   { printf("Ошибка: неожиданный символ: %d %s\n", (int)yytext[0], yytext); exit(1); }

%% 

