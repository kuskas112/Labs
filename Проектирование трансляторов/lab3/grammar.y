%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "tree.h"

    //#define add_node_test(label) $$ = create_node(label, 0); add_child($$, $2); add_child($$, $3)

    typedef struct Node Node;

    pnode root = NULL;
    //Node** atoms;
    //int currentAtom = 0;

    //static inline pnode add_node_test(const char* label)
%}

%union {
    char* str;
    int num;
    pnode node;
}

%token <node> LP RP  QUOTE CAR CDR CONS ATOM_PREDICATE EQUAL ADD SUB MUL DIVE REM LE COND LAMBDA LET LETREC
%token <str> S_ATOM
%token <num> D_ATOM

%type <node> goal S_EXPR ATOM PAIR PAIR_LIST PARAM PARAM_REC VAR S_EXPR_LIST LIST_S_EXPR

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
;

S_EXPR: ATOM
        {
            //atoms[currentAtom] = $1;
            //currentAtom++;

            $$ = $1;

            //$$ = create_node($1, 0);
        }
        | LP ADD S_EXPR S_EXPR RP 
        {
            printf("ADD + S_EXPR + S_EXPR\n");

            $$ = create_node("ADD", 0); add_child($$, $3); add_child($$, $4);
        }
        | LP SUB S_EXPR S_EXPR RP
        {
            printf("SUB + S_EXPR + S_EXPR\n");

            $$ = create_node("SUB", 0); add_child($$, $3); add_child($$, $4);
        }
        | LP QUOTE S_EXPR RP
        {
            printf("QUOTE + S_EXPR\n");

           $$ = create_node("QUOTE", 0); add_child($$, $3);
        }
        | LP CAR S_EXPR RP
        {
            printf("CAR + S_EXPR\n");

           $$ = create_node("CAR", 0); add_child($$, $3);
        }
        | LP CDR S_EXPR RP
        {
            printf("CDR + S_EXPR\n");

            $$ = create_node("CDR", 0); add_child($$, $3);
        }
        | LP CONS S_EXPR S_EXPR RP
        {
            printf("CONS + S_EXPR\n");

            $$ = create_node("CONS", 0); add_child($$, $3); add_child($$, $4);
        }
        | LP ATOM_PREDICATE S_EXPR RP
        {
            printf("ATOM + S_EXPR\n");

            $$ = create_node("ATOM_PREDICATE", 0); add_child($$, $3);
        }
        | LP EQUAL S_EXPR S_EXPR RP
        {
            printf("EQUAL + S_EXPR + S_EXPR\n");

            $$ = create_node("EQUAL", 0); add_child($$, $3); add_child($$, $4);
        }
        | LP MUL S_EXPR S_EXPR RP 
        {
            printf("MUL + S_EXPR + S_EXPR\n");

            $$ = create_node("MUL", 0); add_child($$, $3); add_child($$, $4);
        }
        | LP DIVE S_EXPR S_EXPR RP 
        {
            printf("DIVE + S_EXPR + S_EXPR\n");

            $$ = create_node("DIVE", 0); add_child($$, $3); add_child($$, $4);
        }
        | LP REM S_EXPR S_EXPR RP 
        {
            printf("REM + S_EXPR + S_EXPR\n");

            $$ = create_node("REM", 0); add_child($$, $3); add_child($$, $4);
        }
        | LP LE S_EXPR S_EXPR RP 
        {
            printf("LE + S_EXPR + S_EXPR\n");

            $$ = create_node("LE", 0); add_child($$, $3); add_child($$, $4);
        }
        | LP COND S_EXPR S_EXPR S_EXPR RP 
        {
            printf("COND + S_EXPR + S_EXPR + S_EXPR\n");

            $$ = create_node("COND", 0); add_child($$, $3); add_child($$, $4); add_child($$, $5);
        }
        | LP LAMBDA LP PARAM RP S_EXPR RP 
        {
            printf("LAMBDA + PARAM + S_EXPR\n");

            $$ = create_node("LAMBDA", 0); add_child($$, $3); add_child($$, $6);
        }
        | LP LET S_EXPR PAIR_LIST  RP 
        {
            printf("LET + S_EXPR + PAIR_LIST\n");

            $$ = create_node("LET", 0); add_child($$, $3); add_child($$, $4);
        }
        | LP LETREC S_EXPR PAIR_LIST  RP 
        {
            printf("LETREC + S_EXPR + PAIR_LIST\n");

            $$ = create_node("LETREC", 0); add_child($$, $3); add_child($$, $4);
        }
        | LP LIST_S_EXPR RP
        {
            printf("LIST_S_EXPR\n");
            
            $$ = create_node("LIST", 0);

            if ($2 != NULL) {
                printf("NE nol blya\n");
                for (int i = 0; i < $2->num_children; i++) {
                    add_child($$, $2->children[i]);
                }
            }
            else {
                printf("nol blya\n");
            }
            
        }
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
    {
        printf("S_ATOM %s | from PARAM_REC\n", $1);
        $$ = create_node($1, S_ATOM);  // текст и тип токена S_ATOM

    }
    | PARAM_REC S_ATOM
    ;

VAR:
    S_ATOM 
    {
        printf("S_ATOM %s | from VAR\n", $1);
        $$ = create_node($1, S_ATOM);  // текст и тип токена S_ATOM

    }
    ;

ATOM: 
    S_ATOM 
    {
        printf("S_ATOM %s | from ATOM\n", $1);
        $$ = create_node($1, S_ATOM);  // текст и тип токена S_ATOM
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
    /*|*/ S_EXPR_LIST {
        $$ = $1;
    }
    ;

S_EXPR_LIST:
    S_EXPR
    {
        //printf("S_ATOM %s | from S_EXPR_LIST\n", $1);
        //$$ = create_node($1, S_ATOM);

        $$ = create_node("S_EXPR_LIST", 0);
        add_child($$, $1);
    }
    | S_EXPR_LIST S_EXPR 
    {
        add_child($1, $2);
        $$ = $1;
    }
    ;

%%


int main (void) {

    //root = create_node("root", 0);
    // atoms = malloc(MAX_CHILDREN * sizeof(Node*));

    yyparse();

    
    print_tree(root, 0);
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "\033[31mОшибка: %s\n\033[0m", s);
}