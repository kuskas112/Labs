%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "tree.h"

    #define NO_TOKEN -3

    pnode root = NULL;
    

    union string_digit_union label;

    pnode get_AST_root() {
        yyparse();
        return root;
    }
%}

%union {
    char* str;
    int num;
    pnode node;
}

%token <node> LP RP  QUOTE CAR CDR CONS ATOM_PREDICATE EQUAL ADD SUB MUL DIVE REM LE COND LAMBDA LET LETREC 
%token <str> S_ATOM
%token <num> D_ATOM

%type <node> goal S_EXPR ATOM PAIR PAIR_LIST PARAM_LIST PARAM VAR S_EXPR_LIST LIST_S_EXPR COMMAND

%left QUOTE CAR CDR CONS ATOM_PREDICATE
%left ADD SUB MUL DIVE REM
%left EQUAL LE
%left LAMBDA LET LETREC COND

%start goal

%%
goal: S_EXPR
    {
        root = $1;
        printf("\033[32mВыражение принадлежит языку\033[0m\n"); 
    }
    | error 
    {
        printf("\033[31mОшибка при выполнении\033[0m\n");
        YYABORT;
    }
;

S_EXPR: ATOM
        {
            $$ = $1;
        }
        | LP ADD S_EXPR S_EXPR RP 
        {
            printf("ADD + S_EXPR + S_EXPR\n");

            label.str = "ADD";
            $$ = create_node(label, ADD, NODE_STR); add_child($$, $3); add_child($$, $4);
        }
        | LP SUB S_EXPR S_EXPR RP
        {
            printf("SUB + S_EXPR + S_EXPR\n");
            
            label.str = "SUB";
            $$ = create_node(label, SUB, NODE_STR); add_child($$, $3); add_child($$, $4);
        }
        | LP QUOTE S_EXPR RP
        {
            printf("QUOTE + S_EXPR\n");
            
            label.str = "QUOTE";
            $$ = create_node(label, QUOTE, NODE_STR); add_child($$, $3);
        }
        | LP CAR S_EXPR RP
        {
            printf("CAR + S_EXPR\n");

            label.str = "CAR";
            $$ = create_node(label, CAR, NODE_STR); add_child($$, $3);
        }
        | LP CDR S_EXPR RP
        {
            printf("CDR + S_EXPR\n");

            label.str = "CDR";
            $$ = create_node(label, CDR, NODE_STR); add_child($$, $3);
        }
        | LP CONS S_EXPR S_EXPR RP
        {
            printf("CONS + S_EXPR\n");

            label.str = "CONS";
            $$ = create_node(label, CONS, NODE_STR); add_child($$, $3); add_child($$, $4);
        }
        | LP ATOM_PREDICATE S_EXPR RP
        {
            printf("ATOM + S_EXPR\n");

            label.str = "ATOM_PREDICATE";
            $$ = create_node(label, ATOM_PREDICATE, NODE_STR); add_child($$, $3);
        }
        | LP EQUAL S_EXPR S_EXPR RP
        {
            printf("EQUAL + S_EXPR + S_EXPR\n");

            label.str = "EQUAL";
            $$ = create_node(label, EQUAL, NODE_STR); add_child($$, $3); add_child($$, $4);
        }
        | LP MUL S_EXPR S_EXPR RP 
        {
            printf("MUL + S_EXPR + S_EXPR\n");

            label.str = "MUL";
            $$ = create_node(label, MUL, NODE_STR); add_child($$, $3); add_child($$, $4);
        }
        | LP DIVE S_EXPR S_EXPR RP 
        {
            printf("DIVE + S_EXPR + S_EXPR\n");

            label.str = "DIVE";
            $$ = create_node(label, DIVE, NODE_STR); add_child($$, $3); add_child($$, $4);
        }
        | LP REM S_EXPR S_EXPR RP 
        {
            printf("REM + S_EXPR + S_EXPR\n");

            label.str = "REM";
            $$ = create_node(label, REM, NODE_STR); add_child($$, $3); add_child($$, $4);
        }
        | LP LE S_EXPR S_EXPR RP 
        {
            printf("LE + S_EXPR + S_EXPR\n");

            label.str = "LE";
            $$ = create_node(label, LE, NODE_STR); add_child($$, $3); add_child($$, $4);
        }
        | LP COND S_EXPR S_EXPR S_EXPR RP 
        {
            printf("COND + S_EXPR + S_EXPR + S_EXPR\n");

            label.str = "COND";
            $$ = create_node(label, COND, NODE_STR); add_child($$, $3); add_child($$, $4); add_child($$, $5);
        }
        | LP LAMBDA LP PARAM_LIST RP S_EXPR RP 
        {
            printf("LAMBDA + PARAM + S_EXPR\n");

            label.str = "LAMBDA";
            $$ = create_node(label, LAMBDA, NODE_STR); add_child($$, $4); add_child($$, $6);
        }
        | LP LET S_EXPR PAIR_LIST  RP 
        {
            printf("LET + S_EXPR + PAIR_LIST\n");

            label.str = "LET";
            $$ = create_node(label, LET, NODE_STR); add_child($$, $3); add_child($$, $4);
        }
        | LP LETREC S_EXPR PAIR_LIST RP 
        {
            printf("LETREC + S_EXPR + PAIR_LIST\n");

            label.str = "LETREC";
            $$ = create_node(label, LETREC, NODE_STR); add_child($$, $3); add_child($$, $4);
        }
        | LP LIST_S_EXPR RP
        {
            printf("LIST_S_EXPR\n");
            
            label.str = "LIST";
            $$ = create_node(label, NO_PRINT_WITH_PAREN, NODE_STR);

        
            if ($2 != NULL) { 
                for (int i = 0; i < $2->num_children; i++) {
                    add_child($$, $2->children[i]);
                }
            }
        }
        | LP RP 
        {

            label.str = "NIL";
            $$ = create_node(label, NO_TOKEN, NODE_STR);
        }
        ;

PAIR:
    LP VAR S_EXPR RP
    {
        printf("PAIR: VAR + S_EXPR\n");

        label.str = "PAIR";
        $$ = create_node(label, NO_PRINT_WITH_PAREN, NODE_STR); add_child($$, $2); add_child($$, $3);
    }
    ;


PAIR_LIST:

    | PAIR
    {
        label.str = "PAIR_LIST";
        $$ = create_node(label, NO_PRINT, NODE_STR);
        add_child($$, $1);
    }
    | PAIR_LIST PAIR
    {
        add_child($1, $2);
        $$ = $1;
    }

PARAM:
    S_ATOM 
    {
        printf("S_ATOM %s | from PARAM\n", $1);

        label.str = $1;
        $$ = create_node(label, S_ATOM, NODE_STR);
    }
    ;

PARAM_LIST:
    
    | PARAM 
    {
        label.str = "PARAM_LIST";
        $$ = create_node(label, NO_PRINT, NODE_STR);
        add_child($$, $1);
    }
    | PARAM_LIST PARAM
    {
        add_child($1, $2);
        $$ = $1;
    }
    ;


VAR:
    S_ATOM 
    {
        printf("S_ATOM %s | from VAR\n", $1);

        label.str = $1;
        $$ = create_node(label, S_ATOM, NODE_STR);
    }
    ;

ATOM: 
    S_ATOM 
    {
        printf("S_ATOM %s | from ATOM\n", $1);

        label.str = $1;
        $$ = create_node(label, S_ATOM, NODE_STR);
    }
    | D_ATOM
    {
        printf("D_ATOM %d\n", $1);

        label.num = $1;
        $$ = create_node(label, D_ATOM, NODE_NUM);
    }
    ///*
    | COMMAND 
    {
        printf("COMMAND as S_EXPR\n");

        label.str = $1;
        $$ = create_node(label, S_ATOM, NODE_STR);
    }
    ;
    //*/

COMMAND:
     QUOTE 
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
    S_EXPR_LIST {
        $$ = $1;
    }
    ;

S_EXPR_LIST:
    S_EXPR
    {
        printf("S_ATOM %s | from S_EXPR_LIST\n", $1);

        label.str = "S_EXPR_LIST";
        $$ = create_node(label, NO_TOKEN, NODE_STR);
        add_child($$, $1);
    }
    | S_EXPR_LIST S_EXPR 
    {
        add_child($1, $2);
        $$ = $1;
    }
    ;

%%

/*
int main (void) {
    yyparse();

    
    //print_tree(root, 0);
    print_tree_string(root);

    return 0;
}
*/

void yyerror(const char* s) {
    fprintf(stderr, "\033[31mОшибка: %s\n\033[0m", s);
}