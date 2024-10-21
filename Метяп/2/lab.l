%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
%}

%option noyywrap

%%
[ \t\n]+                           { /* Игнорируем пробелы */ }
[0-9]+                             { printf("Целое число: %s\n", yytext); }
[0-9]+[.,][0-9]+                   { printf("Десятичное: %s\n", yytext); }
"var"                               { printf("Служебное слово: var\n"); }
"if"                                { printf("Служебное слово: if\n"); }
"then"                              { printf("Служебное слово: then\n"); }
"else"                              { printf("Служебное слово: else\n"); }
"begin"                             { printf("Служебное слово: begin\n"); }
"end"                               { printf("Служебное слово: end\n"); }
"or"                                { printf("Логическая операция: or\n"); }
"and"                               { printf("Логическая операция: and\n"); }
[a-zA-Z][a-zA-Z0-9]*               { printf("Идентификатор: %s\n", yytext); }
:=                                  { printf("Присваивание: %s\n", yytext); }
[+\-*/]                             { printf("Знак операции: %s\n", yytext); }
[<>]=|[<>]|=                        { printf("Знак сравнения: %s\n", yytext); }
;                                   { printf("Разделитель команд: %s\n", yytext); }
:                                   { printf("Двоеточие: %s\n", yytext); }
.                                   { printf("Ошибка: неожиданный символ: %s\n", yytext); exit(1); }

%% 

int main(void) {
    yylex(); // Начинаем лексический анализ
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}