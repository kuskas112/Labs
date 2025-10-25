%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "tree.h"

    Node* root = NULL;
    Node** atoms;
    int currentAtom = 0;
%}

%union {
    char* str;
    int num;
}

%token LP RP  QUOTE CAR CDR CONS ATOM_PREDICATE EQUAL ADD SUB MUL DIVE REM LE COND LAMBDA LET LETREC
%token <str> S_ATOM
%token <num> D_ATOM

%%
goal: S_EXPR
    { 
        printf("\033[32mВыражение принадлежит языку\033[0m\n"); 
    }
;

S_EXPR: ATOM
        {
            atoms[currentAtom] = $1;
            currentAtom++;
        }
        | LP QUOTE S_EXPR RP
        {
            printf("QUOTE + S_EXPR\n");
        }
        | LP CAR S_EXPR RP
        {
            printf("CAR + S_EXPR\n");
        }
        | LP CDR S_EXPR RP
        {
            printf("CDR + S_EXPR\n");
        }
        | LP CONS S_EXPR S_EXPR RP
        {
            printf("CONS + S_EXPR\n");
        }
        | LP ATOM_PREDICATE S_EXPR RP
        {
            printf("ATOM + S_EXPR\n");
        }
        | LP EQUAL S_EXPR S_EXPR RP
        {
            printf("EQUAL + S_EXPR + S_EXPR\n");
        }
        | LP ADD S_EXPR S_EXPR RP 
        {
            printf("ADD + S_EXPR + S_EXPR\n");
        }
        | LP SUB S_EXPR S_EXPR RP
        {
            printf("SUB + S_EXPR + S_EXPR\n");
        }
        | LP MUL S_EXPR S_EXPR RP 
        {
            printf("MUL + S_EXPR + S_EXPR\n");
        }
        | LP DIVE S_EXPR S_EXPR RP 
        {
            printf("DIVE + S_EXPR + S_EXPR\n");
        }
        | LP REM S_EXPR S_EXPR RP 
        {
            printf("REM + S_EXPR + S_EXPR\n");
        }
        | LP LE S_EXPR S_EXPR RP 
        {
            printf("LE + S_EXPR + S_EXPR\n");
        }
        | LP COND S_EXPR S_EXPR S_EXPR RP 
        {
            printf("COND + S_EXPR + S_EXPR + S_EXPR\n");
        }
        | LP LAMBDA LP PARAM RP S_EXPR RP 
        {
            printf("LAMBDA + PARAM + S_EXPR\n");
        }
        | LP LET S_EXPR PAIR_LIST  RP 
        {
            printf("LET + S_EXPR + PAIR_LIST\n");
        }
        | LP LETREC S_EXPR PAIR_LIST  RP 
        {
            printf("LETREC + S_EXPR + PAIR_LIST\n");
        }
        | LP LIST_S_EXPR RP
        | LP RP
        ;

PAIR:
    LP VAR S_EXPR RP
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
        $$ = create_node($1, S_ATOM);  // текст и тип токена S_ATOM
        printf("S_ATOM %s\n", $1);
    }
    | D_ATOM
    {
        printf("D_ATOM %d\n", $1);
    }
    | QUOTE 
    | CAR 
    | CDR 
    | CONS 
    | ATOM_PREDICATE 
    | EQUAL 
    | ADD 
    | SUB 
    | MUL 
    | DIVE 
    | REM 
    | LE 
    | COND 
    | LAMBDA 
    | LET 
    | LETREC
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

    root = create_node("root", 0);
    atoms = malloc(MAX_CHILDREN * sizeof(Node*));

    yyparse();

    for(int i = 0; i <= currentAtom; i++) {
        add_child(root, atoms[i]);
    }
    print_tree(root, 0);
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "\033[31mОшибка: %s\n\033[0m", s);
}