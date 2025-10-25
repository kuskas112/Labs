%{
#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"

void yyerror(const char *s);

int scmp(char* str) {
    if (strcasecmp(yytext, str) == 0) return 1;
    return 0;
}
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

{s_atom}                            {   if (scmp("QUOTE") == 1) return QUOTE;
                                        if (scmp("CAR") == 1) return CAR;
                                        if (scmp("CDR") == 1) return CDR;
                                        if (scmp("CONS") == 1) return CONS;
                                        if (scmp("ATOM") == 1) return ATOM_PREDICATE;
                                        if (scmp("EQUAL") == 1) return EQUAL;
                                        if (scmp("ADD") == 1) return ADD;
                                        if (scmp("SUB") == 1) return SUB;
                                        if (scmp("MUL") == 1) return MUL;
                                        if (scmp("DIVE") == 1) return DIVE;
                                        if (scmp("REM") == 1) return REM;
                                        if (scmp("LE") == 1) return LE;
                                        if (scmp("COND") == 1) return COND;
                                        if (scmp("LAMBDA") == 1) return LAMBDA;
                                        if (scmp("LET") == 1) return LET;
                                        if (scmp("LETREC") == 1) return LETREC;
                                        yylval.str = strdup(yytext); return S_ATOM; }
{d_atom}                            { yylval.num = atoi(yytext); return D_ATOM; }
"("                                 { return LP; }
")"                                 { return RP; }
<<EOF>>                             { return 0;}
.                                   { printf("Ошибка: неожиданный символ: %d %s\n", (int)yytext[0], yytext); exit(1); }

%% 

