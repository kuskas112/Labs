%{
#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"

void yyerror(const char *s);

%}

delim [ \t\n\r]+
ws {delim}+
letter [a-zA-Z]
digit [0-9]
integer {digit}+
decimal {digit}+[.,]{digit}+
id {letter}"[A-Za-z0-9]"*
operator [+\-*/]
comp [<>]=|[<>]|=

%option noyywrap

%%
{ws}                                { /* Игнорируем пробелы */ }
{integer}                           { return INTEGER; }
{decimal}                           { return DECIMAL; }
{id}                                { return IDENTIFIER; }
{operator}                          { return OPERATOR; }
:=                                  { return ASSIGN; }
;                                   { return DELIMITER;}
:                                   { return COLON; }
\(                                  { return LBRACKET; }
\)                                  { return RBRACKET; }
{comp}                              { return COMPARISON; }
"begin"                             { return BEGIN_P; }
"end"                               { return END; }
"var"                               { return VAR; }
"if"                                { return IF; }
"then"                              { return THEN; }
"else"                              { return ELSE; }
"or"                                { return OR; }
"and"                               { return AND; }
"round"                             { return ROUND; }

<<EOF>>                             { return 0;}
.                                   { printf("Ошибка: неожиданный символ: %d %s\n", (int)yytext[0], yytext); exit(1); }

%% 
