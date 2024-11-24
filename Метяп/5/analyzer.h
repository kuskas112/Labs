#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tokens.h"
#include "stack.h"
#include "parse_tables.h"

#define DEBIG_MODE true

extern int yylex();
extern char* yytext;

stack *parse_stack;

void reduce(); void shift();

void drop_parse_error() {
    printf("\033[31mParse error!!!!!!\033[0m\n");
    exit(EXIT_FAILURE);
}

void init() {
    parse_stack = stack_alloc();
}

void parse_start() {
    init();

    int curr_token = yylex();

    while (stack_top(parse_stack) != GOAL) {
        switch (stack_top(parse_stack))
        {
        case /* constant-expression */:
            /* code */
            break;
        
        default:
            break;
        }
    }
    



    printf("\033[32mВыражение принадлежит языку!!!!!!!!!!!!!!!!!!!!!!!\033[0m\n");
}

#endif