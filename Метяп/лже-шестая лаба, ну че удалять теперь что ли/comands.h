#ifndef COMANDS_H
#define COMANDS_H
#define TABLE_SIZE 1024
#include <stdio.h>

typedef struct {
    int comand;
    char* param1;
    char* param2;
} comand_t;

typedef enum {
    PUSH_CONST = 1001,
    POP_CONST,
    PUSH_VAR, 
    GOTO
} specific_comands;

comand_t comand_table[TABLE_SIZE];
int current_size = 0;

void add_comand_to_table(int cmd, char* param1, char* param2){
    comand_table[current_size].comand = cmd;

    char* new_param1 = (char*)malloc(strlen(param1));
    strcpy(new_param1, param1);

    char* new_param2 = (char*)malloc(strlen(param2));
    strcpy(new_param2, param2);

    comand_table[current_size].param1 = new_param1;
    comand_table[current_size].param2 = new_param2;
    current_size++;
}

int get_current_table_size(){
    return current_size;
}

void add_comand_goto(char* param1){
    comand_table[current_size].comand = GOTO;

    char* new_param2 = (char*)malloc(1);
    strcpy(new_param2, "\0");

    comand_table[current_size].param1 = param1;
    comand_table[current_size].param2 = new_param2;
    current_size++;
}

void clear_comand_table(){
    current_size = 0;
}

void print_comand_table(){
    for(int i = 0; i < current_size; i++){
        printf("\033[32mCMD %d: %d, %s, %s\n", 
        i,
        comand_table[i].comand, 
        comand_table[i].param1, 
        comand_table[i].param2);
    }
}


#endif