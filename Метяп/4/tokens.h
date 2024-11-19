#ifndef TOKENS_H
#define TOKENS_H

    typedef enum tokens_terminal_type {
        CREATE = 1,
        LBRACKET, RBRACKET,
        COMMA,
        INT, CHAR,
        NOT, _NULL,
        PRIMARY,
        _STRING,
        REFERENCES, FOREIGN, KEY, NUM, TABLE
    } terminals_type;

    typedef enum tokens_non_terminal_type {
            GOAL = 100, 
            NAMES_LIST, NAMES_LIST1,
            ATTR_INIT, ATTR,
            IF_NULL, TYPE,
            PKEY, FKEY
    } non_terminals_type;

#endif