%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "attr_checker.h"

%}

%union {
    char* str;
    int num;
}

%token LEFT_PARENTHESIS RIGHT_PARENTHESIS  QUOTE CAR CDR CONS ATOM_PREDICATE EQUAL ADD SUB MUL DIVE REM LE COND LAMBDA LET LETREC
%token <str> S_ATOM
%token <num> D_ATOM


%%
goal: S_EXPR
    { 
        printf("\033[32mВыражение принадлежит языку\033[0m\n"); 
    }
;

S_EXPR: ATOM
        | LEFT_PARENTHESIS QUOTE S_EXPR RIGHT_PARENTHESIS
        {
            printf("QUOTE + S_EXPR\n");
        }
        | LEFT_PARENTHESIS CAR S_EXPR RIGHT_PARENTHESIS
        {
            printf("CAR + S_EXPR\n");
        }
        | LEFT_PARENTHESIS CDR S_EXPR RIGHT_PARENTHESIS
        {
            printf("CDR + S_EXPR\n");
        }
        | LEFT_PARENTHESIS CONS S_EXPR S_EXPR RIGHT_PARENTHESIS
        {
            printf("CONS + S_EXPR\n");
        }
        | LEFT_PARENTHESIS ATOM_PREDICATE S_EXPR RIGHT_PARENTHESIS
        {
            printf("ATOM + S_EXPR\n");
        }
        | LEFT_PARENTHESIS EQUAL S_EXPR S_EXPR RIGHT_PARENTHESIS
        {
            printf("EQUAL + S_EXPR + S_EXPR\n");
        }
        | LEFT_PARENTHESIS ADD S_EXPR S_EXPR RIGHT_PARENTHESIS 
        {
            printf("ADD + S_EXPR + S_EXPR\n");
        }
        | LEFT_PARENTHESIS SUB S_EXPR S_EXPR RIGHT_PARENTHESIS
        {
            printf("SUB + S_EXPR + S_EXPR\n");
        }
        | LEFT_PARENTHESIS MUL S_EXPR S_EXPR RIGHT_PARENTHESIS 
        {
            printf("MUL + S_EXPR + S_EXPR\n");
        }
        | LEFT_PARENTHESIS DIVE S_EXPR S_EXPR RIGHT_PARENTHESIS 
        {
            printf("DIVE + S_EXPR + S_EXPR\n");
        }
        | LEFT_PARENTHESIS REM S_EXPR S_EXPR RIGHT_PARENTHESIS 
        {
            printf("REM + S_EXPR + S_EXPR\n");
        }
        | LEFT_PARENTHESIS LE S_EXPR S_EXPR RIGHT_PARENTHESIS 
        {
            printf("LE + S_EXPR + S_EXPR\n");
        }
        | LEFT_PARENTHESIS COND S_EXPR S_EXPR S_EXPR RIGHT_PARENTHESIS 
        {
            printf("COND + S_EXPR + S_EXPR + S_EXPR\n");
        }
        | LEFT_PARENTHESIS LAMBDA LEFT_PARENTHESIS PARAM RIGHT_PARENTHESIS S_EXPR RIGHT_PARENTHESIS 
        {
            printf("LAMBDA + PARAM + S_EXPR\n");
        }
        | LEFT_PARENTHESIS LET S_EXPR PAIR_LIST  RIGHT_PARENTHESIS 
        {
            printf("LET + S_EXPR + PAIR_LIST\n");
        }
        | LEFT_PARENTHESIS LETREC S_EXPR PAIR_LIST  RIGHT_PARENTHESIS 
        {
            printf("LETREC + S_EXPR + PAIR_LIST\n");
        }
        | LEFT_PARENTHESIS LIST_S_EXPR RIGHT_PARENTHESIS
        ;



PAIR:
    LEFT_PARENTHESIS VAR S_EXPR RIGHT_PARENTHESIS
    ;

PAIR_LIST:
   PAIR
    | PAIR_LIST PAIR
    ;

PARAM:
    PARAM_REC
    ;

PARAM_REC:
    S_ATOM
    | PARAM_REC S_ATOM
    ;

VAR:
    S_ATOM
    ;

ATOM: 
    S_ATOM 
    {
        printf("S_ATOM %s\n", $1);
    }
    | D_ATOM
    {
        printf("D_ATOM %d\n", $1);
    }
    ;

LIST_S_EXPR:
    /* epsilon - пустой список */
    | S_EXPR_LIST
    ;

S_EXPR_LIST:
    S_EXPR
    | S_EXPR_LIST S_EXPR
    ;

%%


int main (void) {

    return yyparse();
}

void yyerror(const char* s) {
    fprintf(stderr, "Ошибка: %s\n", s);
}