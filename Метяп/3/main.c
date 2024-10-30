#include <stdio.h>
#include "tokens.h"

extern int yylex();

extern char* yytext;

int main(void) {

    int token;
    while ((token = yylex()) != 0)
    {
        printf("%d\n", token);
    }
    

    return 1;
}