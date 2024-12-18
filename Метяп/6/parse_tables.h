#ifndef PARSE_TABLES_H
#define PARSE_TABLSE_H

#include "tokens.h"

#define ACTION_TABLE_RAWS 21
#define ACTION_TABLE_COLS 11

#define GOTO_TABLE_RAWS 21
#define GOTO_TABLE_COLS 5

#define RULES_COUNT 10

#define EMPTY -1
#define ERR -1

int action_table[ACTION_TABLE_RAWS][ACTION_TABLE_COLS] = {
/*      EOF|SELECT|STR|FROM|WHERE|COMP|NUM|COMMA|AND|OR    */
/*S0 */{ERR, S1,  ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
/*S1 */{ERR, ERR, S3,  ERR, ERR, ERR, ERR, ERR, ERR, ERR},
/*S2 */{S5,  ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
/*S3 */{ERR, ERR, ERR, R2,  ERR, ERR, ERR, S6,  ERR, ERR},
/*S4 */{ERR, ERR, ERR, S7,  ERR, ERR, ERR, ERR, ERR, ERR},
/*S5 */{ACC, ACC, ACC, ACC, ACC, ACC, ACC, ACC, ACC, ACC},
/*S6 */{ERR, ERR, S3,  ERR, ERR, ERR, ERR, ERR, ERR, ERR},
/*S7 */{ERR, ERR, S9,  ERR, ERR, ERR, ERR, ERR, ERR, ERR},
/*S8 */{R3,  R3,  R3,  R3,  R3,  R3,  R3,  R3,  R3,  R3 },
/*S9 */{R5,  R5,  R5,  R5,  S10, R5,  R5,  R5,  R5,  R5 },
/*S10*/{ERR, ERR, S12, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
/*S11*/{R1,  R1,  R1,  R1,  R1,  R1,  R1,  R1,  R1,  R1 },
/*S12*/{ERR, ERR, ERR, ERR, ERR, S15, ERR, ERR, ERR, ERR},
/*S13*/{R4,  R4,  R4,  R4,  R4,  R4,  R4,  R4,  R4,  R4 },
/*S14*/{R6,  R6,  R6,  R6,  R6,  R6,  R6,  R6,  S16, S17},
/*S15*/{ERR, ERR, ERR, ERR, ERR, ERR, S18, ERR, ERR, ERR},
/*S16*/{ERR, ERR, S12, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
/*S17*/{ERR, ERR, S12, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
/*S18*/{R9,  R9,  R9,  R9,  R9,  R9,  R9,  R9,  R9,  R9 },
/*S19*/{R7,  R7,  R7,  R7,  R7,  R7,  R7,  R7,  R7,  R7 },
/*S20*/{R8,  R8,  R8,  R8,  R8,  R8,  R8,  R8,  R8,  R8 }


};

int goto_table[GOTO_TABLE_RAWS][GOTO_TABLE_COLS] = {
/*    GOAL|AT_LST|WH_C|CON_L|COND        */
/*S0 */{S2,  ERR, ERR, ERR, ERR},
/*S1 */{ERR, S4,  ERR, ERR, ERR},
/*S2 */{ERR, ERR, ERR, ERR, ERR},
/*S3 */{ERR, ERR, ERR, ERR, ERR},
/*S4 */{ERR, ERR, ERR, ERR, ERR},
/*S5 */{ERR, ERR, ERR, ERR, ERR},
/*S6 */{ERR, S8,  ERR, ERR, ERR},
/*S7 */{ERR, ERR, ERR, ERR, ERR},
/*S8 */{ERR, ERR, ERR, ERR, ERR},
/*S9 */{ERR, ERR, S11, ERR, ERR},
/*S10*/{ERR, ERR, ERR, S13, S14},
/*S11*/{ERR, ERR, ERR, ERR, ERR},
/*S12*/{ERR, ERR, ERR, ERR, ERR},
/*S13*/{ERR, ERR, ERR, ERR, ERR},
/*S14*/{ERR, ERR, ERR, ERR, ERR},
/*S15*/{ERR, ERR, ERR, ERR, ERR},
/*S16*/{ERR, ERR, ERR, S19, S14},
/*S17*/{ERR, ERR, ERR, S20, S14},
/*S18*/{ERR, ERR, ERR, ERR, ERR},
/*S19*/{ERR, ERR, ERR, ERR, ERR},
/*S20*/{ERR, ERR, ERR, ERR, ERR},
};

//int rules_len[RULES_COUNT] = {2, 5, 1, 3, 2, 0, 1, 3, 3, 3};
#define RULE_LEN 1
#define RULE_RES 0

int rules[RULES_COUNT][2] = {
    {ACC, 2},
    {GOAL, 5},
    {ATTR_LIST, 1},
    {ATTR_LIST, 3},
    {WHERE_CASE, 2},
    {WHERE_CASE, 0},
    {CONDITION_LIST, 1},
    {CONDITION_LIST, 3},
    {CONDITION_LIST, 3},
    {CONDITION, 3}
};

#endif