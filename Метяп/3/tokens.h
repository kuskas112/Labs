#ifndef TOKENS_H
#define TOKENS_H

#include <malloc.h>

    typedef enum tokens_type {
        BEGIN_P = 1, END,
        VAR, VARIABLE_TYPE,
        IF, THEN, ELSE,
        INTEGER, DECIMAL,
        IDENTIFIER,
        EQ, NQ, GT, LT, GE, TE, COMPARISON,
        AND, OR,
        ASSIGN,
        OPERATOR,
        LBRACKET, RBRACKET,
        DELIMITER, COLON,
        ROUND
    } tokens_t;

    /*

    typedef struct Token_struct {
        tokens_t token;
        char* value;
    } Token;
    

    Token tok;

    void create_token(tokens_t token, char* value) {
        tok.token = token;
        tok.value = value;
        return;
    }
    */

#endif