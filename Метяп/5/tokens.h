#ifndef TOKENS_H
#define TOKENS_H

typedef enum tokens_terminal_type {
    SELECT = 1, STAR, FROM, _STRING, WHERE, COMPARISON,
    LBRACKET, RBRACKET,
    COMMA,
    NUM,
    OR, AND
} terminals_type;

typedef enum tokens_non_terminal_type {
    GOAL = 50, ATTR_LIST, WHERE_CASE,
    CONDITION_LIST, OPER, CONDITION
} non_termunal_type;

typedef enum states_type {
    S0 = 100
} states_type;



#endif