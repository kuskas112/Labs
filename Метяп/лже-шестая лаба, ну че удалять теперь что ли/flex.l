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
id {letter}+"[A-Za-z0-9]"*
operator [+\-*/]
comp [<>]=|[<>]|=

%option noyywrap

%%
{ws}                                { /* Игнорируем пробелы */ }
"integer"                           { return VARIABLE_TYPE; }
{integer}                           { return INTEGER; }
{decimal}                           { return DECIMAL; }

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
"read"                              { return READ; }
"write"                             { return WRITE; }
"round"                             { return ROUND; }
["+"]                               { return ADD; }
["/"]                               { return DIV; }
\-                                  { return SUB; }
["*"]                               { return MUL; }
"."                                 { return DOT; }

[a-zA-Z][a-zA-Z0-9]*                { return IDENTIFIER; }

<<EOF>>                             { return 0;}
.                                   { printf("Ошибка: неожиданный символ: %d %s\n", (int)yytext[0], yytext); exit(1); }

%% 
