#ifndef TOKENS_H
#define TOKENS_H

#include <stdbool.h>





typedef enum tokens_terminal_type {
    SELECT = 1, 
    _STRING, 
    FROM,  
    WHERE, 
    COMPARISON,
    NUM,
    COMMA,
    OR, 
    AND,
    LBRACKET, 
    RBRACKET
} terminals_type;


typedef enum tokens_non_terminal_type {
    GOAL = 50, ATTR_LIST, WHERE_CASE,
    CONDITION_LIST, CONDITION
} non_termunal_type;

#define NON_TERMINAL_TYPE_BASE 50

typedef enum states_type {
    S0 = 100, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15, S16, S17, S18, S19, S20
} states_type;

#define STATES_TYPE_BASE 100

typedef enum reduce_type {
    R0 = 150, R1, R2, R3, R4, R5, R6, R7, R8, R9
} reduce_type;

#define REDUCE_TYPE_BASE 150

#define ACC 1000



#endif