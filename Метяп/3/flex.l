%{
#include <stdio.h>

#include "tokens.h"

#define TOKEN(X) return 


void yyerror(const char *s);

%}

delim [ \t\n\r]+
ws {delim}+
letter [a-zA-Z]
digit [0-9]
integer {digit}+
decimal {digit}+[.,]{digit}+
id {letter}"[A-Za-z0-9]"*

%option noyywrap

%%
{ws}                                { /* Игнорируем пробелы */ }
{integer}                           { printf("Целое число: %s\n", yytext); }
{id}                                { printf("Идентификатор: %s\n", yytext); }
<<EOF>>                             { return 0;}
.                                   { printf("Ошибка: неожиданный символ: %d %s\n", (int)yytext[0], yytext); exit(1); }

%% 


int main(void) {
    yylex();
    return 0;
}