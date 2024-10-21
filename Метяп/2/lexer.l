%{
#include <stdio.h>
%}

%%
[0-9]+              { printf("Число: %s\n", yytext); }
[a-zA-Z]+          { printf("Слово: %s\n", yytext); }
[ \t\n]+           { /* игнорируем пробелы */ }
.                  { printf("Неизвестный символ: %s\n", yytext); }
%% 

int main(void) {
    yylex(); // Начинаем лексический анализ
    return 0;
}