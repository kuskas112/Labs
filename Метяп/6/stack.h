#ifndef STACK_H
#define STACK_H

#include <malloc.h>
#include <stdio.h>

#define STACK_SIZE 30
#define STACK_INIT_VALUE -1

#define ERROR -1

typedef struct
{
    int values[STACK_SIZE];
    int head_num;
} stack;

int stack_len(stack *s) {
    return s->head_num + 1;
}

void stack_init(stack *s){
    s->head_num = STACK_INIT_VALUE;
}

void stack_push(stack *s, int val) {
    s->values[++s->head_num] = val;
}

int stack_pop(stack *s) {
    //return s->values[s->head_num--]; //first realization

    if (s->head_num < 0) return ERROR;

    int ans = s->values[s->head_num];

    s->values[s->head_num] = ERROR;
    s->head_num--;

    return ans;
}

int stack_top(stack *s) {
    return s->values[s->head_num];
}

void stack_clear(stack *s) {
    for (int i = 0; i <= s->head_num; i++) {
        s->values[i] = -1;
    }

    s->head_num  = STACK_INIT_VALUE;
}

stack* stack_alloc() {
    stack* st = (stack*)malloc(sizeof(stack));
    stack_init(st);
    return st;
}

void print_stack(stack* s){
    for (int i = 0; i <= s->head_num; i++) {
        printf("%d ", s->values[i]);
    }
}


#endif