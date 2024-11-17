#ifndef STACK_H
#define STACK_H

#include <malloc.h>

#define STACK_SIZE 15
#define STACK_INIT_VALUE -1

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
    return s->values[s->head_num--];
}

int stack_top(stack *s) {
    return s->values[s->head_num];
}

stack* stack_alloc() {
    stack* st = (stack*)malloc(sizeof(stack));
    stack_init(st);
    return st;
}


#endif