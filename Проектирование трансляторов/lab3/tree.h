#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <stdbool.h>

#define MAX_CHILDREN 30

union string_digit_union
{
    int num;
    char* str;
};

typedef enum {
    NODE_NUM,
    NODE_STR
} NODE_TYPE;


typedef struct Node {
    int token;
    union string_digit_union label;
    NODE_TYPE node_type;
    struct Node *children[MAX_CHILDREN];
    int num_children;
} Node;

typedef Node* pnode;

void print_tree(Node *root, int depth);
void print_tree_string(Node* root);
Node *create_node(union string_digit_union label, int token, NODE_TYPE node_type);
int has_child_with_token(Node* node, int child_token);
Node* get_child_with_token(Node* node, int child_token);
void add_child(Node *parent, Node *child);

bool if_command_node(Node* node);

#endif