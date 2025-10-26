#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>



void print_tree(Node *root, int depth) {
    if (root == NULL) return;
    
    for (int i = 0; i < depth; ++i) {
        if(depth - 1 == i) printf("- ");
        else printf("| ");
    }
    
    printf("%s\n", root->label);
    
    for (int i = 0; i < root->num_children; ++i) {
        print_tree(root->children[i], depth + 1);
    }
}

Node *create_node(char *label, int token) {
    Node *node = (Node *)malloc(sizeof(Node));
    
    char* node_label = (char*)malloc(strlen(label) + 1);
    strcpy(node_label, label);

    node->token = token;
    node->label = node_label;
    node->num_children = 0;
    for (int i = 0; i < MAX_CHILDREN; ++i) {
        node->children[i] = NULL;
    }
    return node;
}

int has_child_with_token(Node* node, int child_token){
    if(node == NULL) return -1;
    for(int i = 0; i < node->num_children; i++){
        if(node->children[i]->token == child_token){
            return i;
        }
    }
    return -1;
}

Node* get_child_with_token(Node* node, int child_token){
    int childIndex = has_child_with_token(node, child_token);
    if(childIndex == -1) return NULL;
    return node->children[childIndex];
}

void add_child(Node *parent, Node *child) {
    if (parent->num_children < MAX_CHILDREN) {
        parent->children[parent->num_children++] = child;
    } else {
        fprintf(stderr, "Maximum number of children reached.\n");
    }
}
