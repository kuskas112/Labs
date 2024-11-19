#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "parse_tables.h"

extern int yylex();
extern char* yytext;

stack* parse_stack;

#define DEBUG_MODE false

void debug_info(char* text) {
    if (DEBUG_MODE) {
        printf("\033[36m%s\033[0m\n", text);
    }

}

void show_stack(stack* s) {
    if (!DEBUG_MODE) return;
    printf("Stack content: ");
    for (int i = 0; i <= s->head_num; i++) {
        printf("\033[35m%d, \033[0m", s->values[i]);
    }
    printf("\n");
}
/*
void stacks_init() {
    stack_init(parse_stack);
    stack_init(value_stack);
}
*/

void alloc_stack_init() {
    parse_stack = stack_alloc();
}

void drop_parse_error(int token) {
    fprintf(stderr, "\033[31mParse error! token: %d | text: %s\033[0m\n", token, yytext);
    exit(EXIT_FAILURE);
}

void parse_stack_substitute(int value) {
    for (int i = 0; i < TODO_TABLE_COLS; i++) {
        if (todo_table[value][i] >= 0) {
            stack_push(parse_stack, todo_table[value][i]);
        }
    }
}


void parse_start() {
    alloc_stack_init();
    tables_init();



    int curr_token = yylex();
    stack_push(parse_stack, GOAL);

    while (parse_stack->head_num >= 0)
    {
        if (DEBUG_MODE) printf("head_num: %d\n", parse_stack->head_num);
        show_stack(parse_stack);
        if (stack_top(parse_stack) >= GOAL) {
            debug_info("nonterm detected");
            int top = stack_pop(parse_stack);

            int index = top - GOAL;

            int action = parse_table[index][curr_token];


            if (action < 0) {
                drop_parse_error(curr_token);     
            }
            else {
                parse_stack_substitute(action);
            }
        }
        else {
            debug_info("term detected");
            int top = stack_pop(parse_stack);

            if (top < 0 || top != curr_token)
                drop_parse_error(curr_token);

            debug_info(yytext);
            curr_token = yylex();
        }
    }
    

    free(parse_stack);
    printf("\033[32mВыражение принадлежит языку!!!!!!!!!!!\033[0m\n");
}

#endif