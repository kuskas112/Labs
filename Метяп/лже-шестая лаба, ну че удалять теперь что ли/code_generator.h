#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include "variable_table.h"
#include "comands.h"

void push_constant(int constant);

stack* stk;
variable_table* vt;


void generator_init(){
    stk = stack_alloc();
    vt = variable_table_alloc();

}

void run_comands(){
    for(int i = 0; i < current_size; i++){
        printf("cmd¹ %d: ", i);
        int cmd = comand_table[i].comand;
        char* param1 = comand_table[i].param1;
        char* param2 = comand_table[i].param2;
        switch(cmd){
            case PUSH_CONST:
                push_const(param1);
                break;
            case PUSH_VAR:
                push_var(param1);
                break;
            case ADD:
                comand_add();
                break;
            case SUB:
                comand_sub();
                break;
            case MUL:
                comand_mul();
                break;
            case DIV:
                comand_div();
                break;
            case ASSIGN:
                comand_assign(param1);
                break;
            case READ:
                comand_read(param1);
                break;
            case WRITE:
                comand_write(param1);
                break;
            case COMPARISON:
                bool res;
                comand_comparison(param1, &res);
                if (res) i++;
                break;
            case GOTO:
                i = atoi(param1) - 1;
                printf("GOTO %s\n", param1);
                break;

            default:
                printf("Unknown comand %d(%s, %s)\n", cmd, param1, param2);
                break;
        }
    }
}

void comand_comparison(char* sign, bool* res){
    int p1 = pop_const();
    int p2 = pop_const();
    bool val;
    if(strcmp(sign, ">") == 0){
        val = p2>p1;
    }
    else if(strcmp(sign, "<") == 0){
        val = p2<p1;
    }
    else if(strcmp(sign, ">=") == 0){
        val = p2>=p1;
    }
    else if(strcmp(sign, "<=") == 0){
        val = p2<=p1;
    }
    else if(strcmp(sign, "=") == 0){
        val = p2==p1;
    }
    printf("comparison %d %s %d = %d;\n", p2, sign, p1, val);
    *res = val;
}

void comand_add(){
    int p1 = pop_const();
    int p2 = pop_const();
    stack_push(stk, p1+p2);
    printf("push %d\n", p1+p2);
}

void comand_mul(){
    int p1 = pop_const();
    int p2 = pop_const();
    stack_push(stk, p1*p2);
    printf("push %d\n", p1*p2);
}

void comand_div(){
    int p1 = pop_const();
    int p2 = pop_const();
    stack_push(stk, p2/p1);
    printf("push %d\n", p2/p1);
}

void comand_sub(){
    int p1 = pop_const();
    int p2 = pop_const();
    stack_push(stk, p2-p1);
    printf("push %d\n", p2-p1);
}

void comand_assign(char* name){
    int val = stack_pop(stk);
    update_var(name, val);
    printf("assign %s = %d\n", name, val);
}

void comand_read(char* name){
    int val;
    printf("Enter integer: ");
    scanf("%d", &val);
    update_var(name, val);
    printf("read %s = %d\n", name, val);
}

void comand_write(char* name){
    int val = get_value_i(vt, name);
    printf("write %s = %d\n", name, val);
}



void add_var(char* name){
    add_value_i(vt, name);
}

void update_var(char* name, int value){
    update_value_i(vt, name, value);
}

void push_const(char* constant){
    printf("push const %s\n", constant);
    int val = atoi(constant);
    stack_push(stk, val);
}

void push_var(char* name){
    int val = get_value_i(vt, name);
    stack_push(stk, val);
    printf("push var %d\n", val);
}

int pop_const(){
    int val = stack_pop(stk);
    printf("pop %d\n", val);
    return val;
}


void print_st(){
    printf("\n========================\nSTK: ");
    print_stack(stk);
    printf("\n");
    printf("COMANDS TABLE:\n");
    print_comand_table();
}

void print_vt(){
    print_variables(vt);
}



#endif