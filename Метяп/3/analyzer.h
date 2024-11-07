#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tokens.h"

#define NUM_TYPE int

int debug = 0;

extern int yylex();
extern char* yytext;

int curr_token;

bool goat(); // main func

int expr(); int expr1();
int factor();
int term(); int term1();


bool number();


bool comand_list();
bool comand();
bool assigment();
bool read(); bool write(); bool round_p();
bool out_info();
bool if_statement(); bool else_statement();
bool condition(); bool condition_member(); bool condition_sign();

bool var_decl(); bool var_decl_list();

void set_debug_mode(int deb) {
    debug = deb;
}

void print_current_token() {
    printf("Current token: %d | symbol: %s\n", curr_token, yytext);
    return;
}

void drop_parse_error(int ttype) {
    fprintf(stderr, "!!!Error: unexpected token!!!\nExpected: %d | Get: %d\n", curr_token, ttype);
    exit(EXIT_FAILURE);
    return;
}

bool eat(int ttype) {
    if (curr_token == ttype) {
        if (debug == 1) print_current_token();
        curr_token = yylex();
        return true;
    }
    else {
        drop_parse_error(ttype);
        return false;
    }
}

/*
bool number() {
    if (curr_token == INTEGER) {
        yylex
    }
}
*/

bool goat() {
    if (curr_token == VAR) {
        eat(VAR);
        var_decl_list();
    }
    eat(BEGIN_P);
    comand_list();
    eat(END);
    return true;
}

bool var_decl_list() {
    if (curr_token == IDENTIFIER) {
        var_decl(),
        eat(DELIMITER);
        var_decl_list();
    }
    else {
        return false;
    }
    return true;
}

bool var_decl() {
    eat(IDENTIFIER);
    eat(COLON);
    eat(VARIABLE_TYPE);
    return true;
}

bool comand_list() {
    if (comand() == true) comand_list();
    return false;
}

bool comand() {
    bool is_action = false;
    if (assigment()) {
        is_action = true;
    }
    else if (read()) {
        is_action = true;
    }
    else if (write()) {
        is_action = true;
    }
    else if (if_statement()) {
        is_action = true;
    }
    else if (round_p()) {
        is_action = true;
    }
    return is_action;
}

bool assigment() {
    if (curr_token == IDENTIFIER) {
        eat(IDENTIFIER);
        eat(ASSIGN);
        expr();
        eat(DELIMITER);
    }
    else {
        return false;
    }
    return true;
}

bool read() {
    if (curr_token == READ) {
        eat(READ);
        eat(LBRACKET);
        eat(IDENTIFIER);
        eat(RBRACKET);
        eat(DELIMITER);
    }
    else {
        return false;
    }
    return true;
}

bool write() {
    if (curr_token == WRITE) {
        eat(WRITE);
        eat(LBRACKET);
        out_info();
        eat(RBRACKET);
        eat(DELIMITER);
    }
    else {
       return false;
    }
    return true;
}

bool round_p() {
    if (curr_token == ROUND) {
        eat(ROUND);
        eat(LBRACKET);
        eat(IDENTIFIER);
        eat(RBRACKET);
        eat(DELIMITER);
    }
    else {
        return false;
    }
    return true;
}

bool out_info() {
    if (curr_token == IDENTIFIER) {
        eat(IDENTIFIER);
    }
    // tyt doljna byt regularka dlya stroki
    else {
        return false;
    }
    return true;
}

bool if_statement() {
    if (curr_token == IF) {
        eat(IF);
        eat(LBRACKET);
        condition();
        eat(THEN);
        eat(BEGIN_P);
        comand_list();
        eat(END);
        else_statement();
    }
    else {
        return false;
    }
    return true;
}

bool else_statement() {
    if (curr_token == ELSE) {
        eat(ELSE);
        eat(BEGIN_P);
        comand_list();
        eat(END);
    }
    else {
        return false;
    }
    return true;
}

bool condition() {
    condition_member();
    condition_sign();
    condition_member();
    return true;
}

bool condition_member() {
    if (curr_token == IDENTIFIER) {
        eat(IDENTIFIER);
    }
    else if (curr_token == DECIMAL) {
        eat(DECIMAL);
    }
    else {
        return false;
    }
    return true;
}

bool condition_sign() {
    if (curr_token == COMPARISON) {
        eat(COMPARISON);
    }
    else {
        return false;
    }
    return true;
}

//old math func 
/*
int factor() {
    if (curr_token == INTEGER) {
        int val = atoi(yytext);
        eat(INTEGER);
        return val;
    }
    else if (curr_token == LBRACKET) {
        eat(LBRACKET);
        int res = expr();
        eat(RBRACKET);
        return res;
    }
    else {
        print_parse_error();
    }
}

int term() {
    int res = factor();
    while(curr_token == MUL || curr_token == DIV) {
        if (curr_token == MUL) {
            eat(MUL);
            res *= factor();
        }
        else if (curr_token == DIV) {
            eat(DIV);
            int div = factor();
            if (div == 0) {
                fprintf(stderr, "Error: Division by zero\n");
            }
            res /= div;
        }
    }
    return res;
}

int expr() {
    int res = term();
    while (curr_token == ADD || curr_token == SUB) {
        if (curr_token == ADD) {
            eat(ADD);
            res += term();
        }
        else if (curr_token == SUB) {
            eat(SUB);
            res -= term();
        }
    }
    return res;
}
*/

NUM_TYPE expr() {
    term();
    expr1();
}

NUM_TYPE expr1() {
    if (curr_token == ADD) {
        eat(ADD);
        term();
        expr1();
    }
    else if (curr_token == SUB) {
        eat(SUB);
        term();
        expr1();
    }
}

NUM_TYPE term() {
    factor();
    term1();
}

NUM_TYPE term1() {
    if (curr_token == MUL) {
        eat(MUL);
        factor();
        term1();
    }
    else if (curr_token == DIV) {
        eat(DIV);
        factor();
        term1();
    }
    
}

NUM_TYPE factor() {
    if (curr_token == INTEGER) {
        eat(INTEGER);
    }
    else if (curr_token == IDENTIFIER) {
        eat(IDENTIFIER);
    }
    else if (curr_token == LBRACKET) {
        eat(LBRACKET);
        expr();
        eat(RBRACKET);
    }
    else if (curr_token == ROUND) {
        eat(ROUND);
        eat(LBRACKET);
        expr();
        eat(RBRACKET);
    }
    else {
        exit(EXIT_FAILURE);
    }
}


void parse_start() {
    curr_token = yylex();
    //printf("%d\n", curr_token);
    goat();
    printf("Выражение принадлежит языку\n");
}

#endif