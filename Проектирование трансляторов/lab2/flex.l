%{
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "y.tab.h"

enum yytokentype token_type;

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

{s_atom}                            {   if (scmp("QUOTE") == 1) {token_type = QUOTE;}
                                        else if (scmp("CAR") == 1) {token_type = CAR;}
                                        else if (scmp("CDR") == 1) {token_type = CDR;}
                                        else if (scmp("CONS") == 1) {token_type = CONS;}
                                        else if (scmp("ATOM") == 1) {token_type = ATOM_PREDICATE;}
                                        else if (scmp("EQUAL") == 1) {token_type = EQUAL;}
                                        else if (scmp("ADD") == 1) {token_type = ADD;}
                                        else if (scmp("SUB") == 1) {token_type = SUB;}
                                        else if (scmp("MUL") == 1) {token_type = MUL;}
                                        else if (scmp("DIVE") == 1) {token_type = DIVE;}
                                        else if (scmp("REM") == 1) {token_type = REM;}
                                        else if (scmp("LE") == 1) {token_type = LE;}
                                        else if (scmp("COND") == 1) {token_type = COND;}
                                        else if (scmp("LAMBDA") == 1) {token_type = LAMBDA;}
                                        else if (scmp("LET") == 1) {token_type = LET;}
                                        else if (scmp("LETREC") == 1) {token_type = LETREC;}
                                        else {  token_type = S_ATOM; }

                                        yylval.str = strdup(yytext);
                                        return token_type;
                                       
                                    }
{d_atom}                            { yylval.num = atoi(yytext); return D_ATOM; }
"("                                 { return LP; }
")"                                 { return RP; }
<<EOF>>                             { return 0;}
.                                   { printf("Ошибка: неожиданный символ: %d %s\n", (int)yytext[0], yytext); exit(1); }

%% 

