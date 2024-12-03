#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tokens.h"
#include "stack.h"
#include "parse_tables.h"

#define DEBUG_MODE true
#define _EOF 0

extern int yylex();
extern char* yytext;

pair_stack *parse_stack;

void reduce(); void shift();

void drop_parse_error() {
    printf("\033[31mParse error!!!!!!\033[0m\n");
    exit(EXIT_FAILURE);
}

void show_pair_stack(pair_stack* s) {
    if (!DEBUG_MODE) return;
    printf("Stack content: ");
    for (int i = 0; i <= s->head_num; i++) {
        printf("\033[35m[St: %d, El: %d], \033[0m", s->pair[i].state, s->pair[i].token);
    }
    printf("\n");
}


bool is_terminal(int tok) { return tok < NON_TERMINAL_TYPE_BASE; }
bool is_non_terminal(int tok) { return tok >= NON_TERMINAL_TYPE_BASE && tok < STATES_TYPE_BASE; }
bool is_states_type(int tok) { return tok >= STATES_TYPE_BASE && tok < REDUCE_TYPE_BASE; }
bool is_reduce_type(int tok) { return tok >= REDUCE_TYPE_BASE && tok < ACC; }
bool is_accept(int tok) { return tok == ACC; }

void init() {
    parse_stack = pair_stack_alloc();
}

void update_curr_state() {

}

int curr_token;

void parse_start() {
    init();


    pair_stack_push_pair(parse_stack, S0, _EOF);
    
    curr_token = yylex();

    while (1) {
        int curr_state = pair_stack_get_top_state(parse_stack);

        int action = action_table[curr_state - STATES_TYPE_BASE][curr_token];


        show_pair_stack(parse_stack);
        printf("Current action: %d\n", action);
        printf("Action cell: %d, %d\n", curr_state - STATES_TYPE_BASE, curr_token);
        printf("lex: %s\n", yytext);

        if (is_accept(action)) {
            printf("\033[32mВыражение принадлежит языку!!!!!!!!!!!!!!!!!!!!!!!\033[0m\n");
            break;
        }
        else if (is_states_type(action)) {
            pair_stack_push_pair(parse_stack, action, curr_token);
            curr_token = yylex();
        }
        else if (is_reduce_type(action)) {
            int rule = action - REDUCE_TYPE_BASE;
            printf("rule %d\n", rule);
            
            for (int i = 0; i < rules[rule][RULE_LEN]; i++) {
                pair_stack_pop_pair(parse_stack);
            }
            
            int curr_state = pair_stack_get_top_state(parse_stack);


            printf("Cell %d, %d\n", curr_state - STATES_TYPE_BASE, rules[rule][RULE_RES] - NON_TERMINAL_TYPE_BASE);

            int new_state = goto_table[curr_state - STATES_TYPE_BASE][rules[rule][RULE_RES] - NON_TERMINAL_TYPE_BASE];


            pair_stack_push_pair(parse_stack, new_state, rules[rule][RULE_RES]);
        }
        else {
            drop_parse_error();
        }
    }
}

void shift() {

    curr_token = yylex();
}

void reduce() {

}
#endif