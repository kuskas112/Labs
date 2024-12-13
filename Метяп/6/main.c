#include <stdio.h>

#include "tokens.h"
#include "analyzer.h"

//extern int yylex();
//extern char* yytext;

int main(void) {

    set_debug_mode(2);
    generator_init();
    parse_start();
    run_comands();
    print_st();
    print_vt();
    return 1;
}