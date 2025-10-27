#ifndef TREE_NODE_H
#define TREE_NODE_H

#define MAX_CHILDREN 30



//typedef struct Node Node;

typedef struct Node {
    char *label;
    int token;
    struct Node *children[MAX_CHILDREN];
    int num_children;
} Node;

typedef Node* pnode;

void print_tree(Node *root, int depth);
Node *create_node(char *label, int token);
int has_child_with_token(Node* node, int child_token);
Node* get_child_with_token(Node* node, int child_token);
void add_child(Node *parent, Node *child);

#endif