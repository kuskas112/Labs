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

%token <str> SELECT FROM WHERE AND OR COMMA _STRING COMPARISON
%token <num> NUM
%%
goal: SELECT attr_list FROM _STRING where_case 
    { 
        //printf("%s\n", $4);
        if (find_table_name($4)) {
            printf("Такая строка есть\n");
        }
        else {
            printf("Такой строки нет\n");
        }


        printf("\033[32mВыражение принадлежит языку\033[0m\n"); 
    }
;

attr_list: _STRING 
            { 
                if (find_table_attr($1)) {
                    printf("Такой атрибут есть\n");
                }
                else {
                    printf("Такого атрибута нет\n");
                }
                //printf("%s\n", $1); 
            }
         | _STRING COMMA attr_list 
         { 
            if (find_table_attr($1)) {
               printf("Такой атрибут есть\n");
            }
            else {
                printf("Такого атрибута нет\n");
            }
            //printf("%s\n", $1); 
        }
         ;

where_case: WHERE condition_list
          | /* epsilon */ ;

condition_list: condition
              | condition AND condition_list
			  | condition OR condition_list;

condition: _STRING COMPARISON NUM;

%%


int main (void) {
    /*
    file = fopen("table.db", "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    char buffer[256];
    */

    start_scan();
    print_attrs();


    return yyparse();
}

void yyerror(const char* s) {
    fprintf(stderr, "Ошибка: %s\n", s);
}