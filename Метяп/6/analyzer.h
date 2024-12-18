#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tokens.h"
#include "stack.h"
#include "tree.h"
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

void get_string_token(int term, char* buffer){
    switch(term){
        case ATTR_LIST:
            sprintf(buffer, "attr_list");
            break;
        case WHERE_CASE:
            sprintf(buffer, "where_case");
            break;
        case CONDITION_LIST:
            sprintf(buffer, "condition_list");
            break;
        case CONDITION:
            sprintf(buffer, "condition");
            break;
        case GOAL:
            sprintf(buffer, "goal");
            break;
        case SELECT:
            sprintf(buffer, "SELECT");
            break;
        case _STRING:
            sprintf(buffer, "STRING");
            break;
        case FROM:
            sprintf(buffer, "FROM");
            break;
        case WHERE:
            sprintf(buffer, "WHERE");
            break;
        case COMPARISON:
            sprintf(buffer, "COMPARISON");
            break;
        case NUM:
            sprintf(buffer, "NUM");
            break;
        case COMMA:
            sprintf(buffer, "COMMA");
            break;
        case OR:
            sprintf(buffer, "OR");
            break;
        case AND:
            sprintf(buffer, "AND");
            break;
        case LBRACKET:
            sprintf(buffer, "LBRACKET");
            break;
        case RBRACKET:
            sprintf(buffer, "RBRACKET");
            break;
        default:
            printf("unknown token %d!!\n", term);
            break;
    }
}

int curr_token;

void parse_start() {
    init();
    pair_stack_push_pair(parse_stack, S0, _EOF);
    curr_token = yylex();
    char token_name[20];
    int token_buffer[10];
    Node* previous_nodes[30];
    int total_prev_nodes = 0;
    while (1) {
        int curr_state = pair_stack_get_top_state(parse_stack);

        int action = action_table[curr_state - STATES_TYPE_BASE][curr_token];

        if (is_accept(action)) {
            printf("\033[32mВыражение принадлежит языку!!!!!!!!!!!!!!!!!!!!!!!\033[0m\n");
            for(int i = 0; i < total_prev_nodes; i++){
                Node* child_node = previous_nodes[i];
                for(int j = i+1; j < total_prev_nodes; j++){
                    int child_index = has_child_with_token(previous_nodes[j], child_node->token);
                    if(child_index != -1){
                        previous_nodes[j]->children[child_index] = child_node;
                    }
                }
            }
            print_tree(previous_nodes[total_prev_nodes-1], 0);
            break;
        }
        else if (is_states_type(action)) {
            pair_stack_push_pair(parse_stack, action, curr_token);
            curr_token = yylex();
        }
        else if (is_reduce_type(action)) {
            int rule = action - REDUCE_TYPE_BASE;
            for (int i = 0; i < rules[rule][RULE_LEN]; i++) {
                parse_pair popped_pair = pair_stack_pop_pair(parse_stack);
                token_buffer[i] = popped_pair.token;
            }
            get_string_token(rules[rule][RULE_RES], token_name); // rule result token
            Node* node = create_node(token_name, rules[rule][RULE_RES]);
            for (int i = rules[rule][RULE_LEN] - 1; i >= 0; i--) {
                get_string_token(token_buffer[i], token_name);
                add_child(node, create_node(token_name, token_buffer[i]));
            }
            previous_nodes[total_prev_nodes++] = node;
            int curr_state = pair_stack_get_top_state(parse_stack);
            int new_state = goto_table[curr_state - STATES_TYPE_BASE][rules[rule][RULE_RES] - NON_TERMINAL_TYPE_BASE];
            get_string_token(rules[rule][RULE_RES], token_name);            
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