#ifndef LIST_H
#define LIST_H

#include "tree.h"
//#include "analyzer.h"

typedef struct List List;
typedef struct Node_List Node_List;
typedef struct Enviroment Enviroment;
typedef struct lambda_struct lambda_struct;
typedef struct ANSWER_STRUCT ANSWER_STRUCT;

typedef union answer_value {
    int num;
    char* str;
    List* list;
    lambda_struct* lambda;
} answer_value;

typedef struct ANSWER_STRUCT
{
    union answer_value value;
    NODE_TYPE type;
} ANSWER_STRUCT;

typedef struct List {
    struct Node_List* first;
    struct Node_List* last;
    int length;
} List;


typedef struct Enviroment
{
    struct Binding
    {
        char* name;
        ANSWER_STRUCT* value;
        struct Binding* next;
    } *bindings;
    
    struct Enviroment* parent; 
    
} Enviroment;

typedef struct lambda_struct
{
    List* params;
    pnode body;
    struct Enviroment* env;
} lambda_struct;





typedef struct Node_List {
    struct Node_List* next;
    //struct Node_List* prev;
    //void* value;
    //union string_digit_union value;
    union answer_value node_value;
    NODE_TYPE node_type;
}Node_List;





List* create_list();
Node_List* create_node_list(union answer_value value, NODE_TYPE node_type);

void append_to_list(List* list, union answer_value value, NODE_TYPE node_type);
void prepend_to_list(List* list, union answer_value value, NODE_TYPE node_type);

List* copy_list(List* original);

Node_List* get_head(List* list);
List* get_tail(List* list);

void print_list(List* list);

void pop_list(List* list, int pos);

void delete_node_list(Node_List* node);
void delete_list(List* list);

#endif