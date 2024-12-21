%{
#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"

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
{integer}                           { yylval.num = atoi(yytext); return NUM; }
"SELECT"                            { return SELECT; }
"FROM"                              { return FROM; }
"WHERE"                             { return WHERE; }
"OR"                                { return OR; }
"AND"                               { return AND; }

","                                 { return COMMA; }
{comp}                              { return COMPARISON; }

[a-zA-Z]*                           { yylval.str = strdup(yytext); return _STRING; }

<<EOF>>                             { return 0;}
.                                   { printf("Ошибка: неожиданный символ: %d %s\n", (int)yytext[0], yytext); exit(1); }

%% 
