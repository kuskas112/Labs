#ifndef TOKENS_H
#define TOKENS_H

    typedef enum tokens_terminal_type {
        CREATE = 1, TABLE,
        LBRACKET, RBRACKET,
        COMMA,
        INT, CHAR, NUM,
        NOT, _NULL,
        PRIMARY, FOREIGN, KEY, REFERENCES, 
        _STRING
    } terminals_type;

    typedef enum tokens_non_terminal_type {
            GOAL = 100, 
            NAME, NAMES_LIST, NAMES_LIST1,
            ATTR_INIT, ATTR,
            IF_NULL, TYPE,
            PKEY, FKEY
    } non_terminals_type;

#endif