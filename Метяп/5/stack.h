#ifndef STACK_H
#define STACK_H

#include <malloc.h>

#define STACK_SIZE 15
#define STACK_INIT_VALUE -1

#define PAIR_STACK_SIZE 15
#define PAIR_STACK_INIT_VALUE -1

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

stack* stack_alloc() {
    stack* st = (stack*)malloc(sizeof(stack));
    stack_init(st);
    return st;
}

//=========================================================
// Стек для восходящего разбора с парами <Состояние, Токен>
//=========================================================

typedef struct
{
    int state;
    int token;
} parse_pair;

typedef struct
{
    parse_pair pair[PAIR_STACK_SIZE];
    int head_num;
    
} pair_stack;

void pair_stack_init(pair_stack *s) {
    s->head_num = PAIR_STACK_INIT_VALUE;
}

int pair_stack_get_top_state(pair_stack *s) {
    return s->pair[s->head_num].state;
}

int pair_stack_get_top_token(pair_stack *s) {
    return s->pair[s->head_num].token;
}

parse_pair pair_stack_pop_pair(pair_stack *s) {
    return s->pair[s->head_num--];
}

void pair_stack_push_pair(pair_stack *s, int st, int tok) {
    s->pair[++s->head_num].state = st;
    s->pair[s->head_num].token = tok;
}

pair_stack* alloc_pair_stack() {
    pair_stack *ps = (pair_stack*)malloc(sizeof(pair_stack));
    pair_stack_init(ps);
    return ps;
}


#endif