#ifndef TOKENS_H
#define TOKENS_H

#include <malloc.h>

token::Token tok;

namespace token {
    enum tokens_t {
        IF, THEN, ELSE,
        BEGIN, END,
        INTEGER, DECIMAL,
        IDENTIFIER,
        EQ, NQ, GT, LT, GE, TE,
        ASSIGN,
        OPERATOR
    };

    struct Token {
        tokens_t token;
        char* value;
    };

    void createToken(tokens_t token, char* value) {
        tok.token = token;
        tok.value = value;
        return;
    }

    Token* allocToken(tokens_t token, char* value) { // If you want save many tokens in list
        return nullptr;
    }
}

#endif