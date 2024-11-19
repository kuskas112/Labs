#ifndef PARSE_TABLES_H
#define PARSE_TABLES_H

#include "tokens.h"

#define PARSE_TABLE_ROWS 11
#define PARSE_TABLE_COLS 12

#define TODO_TABLE_ROWS 12
#define TODO_TABLE_COLS 12

#define EMPTY -1
#define ERROR -1

int parse_table[PARSE_TABLE_ROWS][PARSE_TABLE_COLS];
int todo_table[TODO_TABLE_ROWS][TODO_TABLE_COLS];

void init_parse_table(void); void init_todo_table(void);
void print_parse_table(void); void print_todo_table(void);

void tables_init(void) {
    init_parse_table();
    init_todo_table();

    /*
    print_parse_table();
    print_todo_table();
    */
}

void init_parse_table(void) {
    for (int i = 0; i < PARSE_TABLE_ROWS; i++) {
            int index = i + GOAL; 
        for (int j = 0; j < PARSE_TABLE_COLS; j++) {
            switch (index)
            {
            case GOAL:
                switch (j)
                {
                case CREATE:
                    parse_table[i][j] = 0;
                    break;
                default:
                    parse_table[i][j] = ERROR;
                    break;
                }
                break;
            case NAMES_LIST:
                switch (j)
                {
                case _STRING:
                    parse_table[i][j] = 1;
                    break;
                default:
                    parse_table[i][j] = ERROR;
                    break;
                }
                break;
            case NAMES_LIST1:
                switch (j)
                {
                case RBRACKET:
                    parse_table[i][j] = 11;
                    break;
                case COMMA:
                    parse_table[i][j] = 2;
                    break;
                default:
                    parse_table[i][j] = ERROR;
                    break;
                }
                break;
            case ATTR_INIT:
                switch (j)
                {
                case _STRING:
                    parse_table[i][j] = 3;
                    break;
                case RBRACKET:
                    parse_table[i][j] = 11;
                    break;
                case PRIMARY:
                    parse_table[i][j] = 11;
                    break;
                default:
                    parse_table[i][j] = ERROR;
                    break;
                }
                break;
            case ATTR:
                switch (j)
                {
                case _STRING:
                    parse_table[i][j] = 4;
                    break;
                default:
                    parse_table[i][j] = ERROR;
                    break;
                }
                break;
            case IF_NULL:
                switch (j)
                {
                case NOT:
                    parse_table[i][j] = 7;
                    break;
                case _NULL:
                    parse_table[i][j] = 8;
                    break;
                default:
                    parse_table[i][j] = ERROR;
                    break;
                }
                break;
            case TYPE:
                switch (j)
                {
                case INT:
                    parse_table[i][j] = 5;
                    break;
                case CHAR:
                    parse_table[i][j] = 6;
                    break;
                default:
                    parse_table[i][j] = ERROR;
                    break;
                }
                break;
            case PKEY:
                switch (j)
                {
                case PRIMARY:
                    parse_table[i][j] = 9;
                    break;
                default:
                    parse_table[i][j] = ERROR;
                    break;
                }
                break;
            case FKEY:
                switch (j)
                {
                
                case RBRACKET:
                    parse_table[i][j] = 11;
                    break;
                
                case COMMA:
                    parse_table[i][j] = 10;
                    break;
                default:
                    parse_table[i][j] = ERROR;
                    break;
                }
                break;
            default:
                break;
            }
        }
    }
}

void init_todo_table(void) {
    for (int i = 0; i < TODO_TABLE_ROWS; i++) {
        for (int j = 0; j < TODO_TABLE_COLS; j++) {
            int inv_col = TODO_TABLE_COLS - 1 - j;
            switch (i)
            {
            case 0:
                switch (inv_col)
                {
                case 0:
                    todo_table[i][j] = CREATE;
                    break;
                case 1:
                    todo_table[i][j] = TABLE;
                    break;
                case 2:
                    todo_table[i][j] = _STRING;
                    break;
                case 3:
                    todo_table[i][j] = LBRACKET;
                    break;
                case 4:
                    todo_table[i][j] = ATTR_INIT;
                    break;
                case 5:
                    todo_table[i][j] = PKEY;
                    break;
                case 6:
                    todo_table[i][j] = FKEY;
                    break;
                case 7:
                    todo_table[i][j] = RBRACKET;
                    break;
                default:
                    todo_table[i][j] = EMPTY;
                    break;
                }
                break;
            case 1:
                switch (inv_col)
                {
                case 0:
                    todo_table[i][j] = _STRING;
                    break;
                case 1:
                    todo_table[i][j] = NAMES_LIST1;
                    break;
                default:
                    todo_table[i][j] = EMPTY;
                    break;
                }
                break;
            case 2:
                switch (inv_col)
                {
                case 0:
                    todo_table[i][j] = COMMA;
                    break;
                case 1:
                    todo_table[i][j] = _STRING;
                    break;
                case 2:
                    todo_table[i][j] = NAMES_LIST1;
                    break;
                default:
                    todo_table[i][j] = EMPTY;
                    break;
                }
                break;
            case 3:
                switch (inv_col)
                {
                case 0:
                    todo_table[i][j] = ATTR;
                    break;
                case 1:
                    todo_table[i][j] = ATTR_INIT;
                    break;
                default:
                    todo_table[i][j] = EMPTY;
                    break;
                }
                break;
            case 4:
                switch (inv_col)
                {
                case 0:
                    todo_table[i][j] = _STRING;
                    break;
                case 1:
                    todo_table[i][j] = TYPE;
                    break;
                case 2:
                    todo_table[i][j] = IF_NULL;
                    break;
                case 3:
                    todo_table[i][j] = COMMA;
                    break;
                default:
                    todo_table[i][j] = EMPTY;
                    break;
                }
                break;
            case 5:
                switch (inv_col)
                {
                case 0:
                    todo_table[i][j] = INT;
                    break;
                default:
                    todo_table[i][j] = EMPTY;
                    break;
                }
                break;
            case 6:
                switch (inv_col)
                {
                case 0:
                    todo_table[i][j] = CHAR;
                    break;
                case 1:
                    todo_table[i][j] = LBRACKET;
                    break;
                case 2:
                    todo_table[i][j] = NUM;
                    break;
                case 3:
                    todo_table[i][j] = RBRACKET;
                    break;
                default:
                    todo_table[i][j] = EMPTY;
                    break;
                }
                break;
            case 7:
                switch (inv_col)
                {
                case 0:
                    todo_table[i][j] = NOT;
                    break;
                case 1:
                    todo_table[i][j] = _NULL;
                    break;
                default:
                    todo_table[i][j] = EMPTY;
                    break;
                }
                break;
            case 8:
                switch (inv_col)
                {
                case 0:
                    todo_table[i][j] = _NULL;
                    break;
                default:
                    todo_table[i][j] = EMPTY;
                    break;
                }
                break;
            case 9:
                switch (inv_col)
                {
                case 0:
                    todo_table[i][j] = PRIMARY;
                    break;
                case 1:
                    todo_table[i][j] = KEY;
                    break;
                case 2:
                    todo_table[i][j] = LBRACKET;
                    break;
                case 3:
                    todo_table[i][j] = NAMES_LIST;
                    break;
                case 4:
                    todo_table[i][j] = RBRACKET;
                    break;
                default:
                    todo_table[i][j] = EMPTY;
                    break;
                }
                break;
            case 10:
                switch (inv_col)
                {
                case 0:
                    todo_table[i][j] = COMMA;
                    break;
                case 1:
                    todo_table[i][j] = FOREIGN;
                    break;
                case 2:
                    todo_table[i][j] = KEY;
                    break;
                case 3:
                    todo_table[i][j] = LBRACKET;
                    break;
                case 4:
                    todo_table[i][j] = NAMES_LIST;
                    break;
                case 5:
                    todo_table[i][j] = RBRACKET;
                    break;
                case 6:
                    todo_table[i][j] = REFERENCES;
                    break;
                case 7:
                    todo_table[i][j] = _STRING;
                    break;
                case 8:
                    todo_table[i][j] = LBRACKET;
                    break;
                case 9:
                    todo_table[i][j] = NAMES_LIST;
                    break;
                case 10:
                    todo_table[i][j] = RBRACKET;
                    break;
                case 11:
                    todo_table[i][j] = FKEY;
                    break;
                default:
                    todo_table[i][j] = EMPTY;
                    break;
                }
                break;
            case 11:
                todo_table[i][j] = EMPTY;
                break;
            default:
                break;
            }
        }
    }
}

void print_parse_table() {
    printf("PARSE TABLE:\n");
    for (int i = 0; i < PARSE_TABLE_ROWS; i++) {
        for (int j = 0; j < PARSE_TABLE_COLS; j++) {
            printf("%d, ", parse_table[i][j]);
        }
        printf("\n");
    }
}

void print_todo_table() {
    printf("TODODO TABLE:\n");
    for (int i = 0; i < TODO_TABLE_ROWS; i++) {
        for (int j = 0; j < TODO_TABLE_COLS; j++) {
            printf("%d, ", todo_table[i][j]);
        }
        printf("\n");
    }
}

#endif