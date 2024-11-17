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
id {letter}+"[A-Za-z0-9]"*

%option noyywrap

%%
{ws}                                { /* Игнорируем пробелы */ }
"int"                               { return INT; }
"char"                              { return CHAR; }
{integer}                           { return NUM; }

\(                                  { return LBRACKET; }
\)                                  { return RBRACKET; }
"CREATE"                            { return CREATE; }
"TABLE"                             { return TABLE; }
","                                 { return COMMA; }
"NOT"                               { return NOT; }
"NULL"                              { return _NULL; }
"PRIMARY"                           { return PRIMARY; }
"FOREIGN"                           { return FOREIGN; }
"KEY"                               { return KEY; }
"REFERENSES"                        { return REFERENCES;}

[a-zA-Z]*                           { return _STRING; }

<<EOF>>                             { return 0;}
.                                   { printf("Ошибка: неожиданный символ: %d %s\n", (int)yytext[0], yytext); exit(1); }

%% 
