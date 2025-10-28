#include "tree.h"
#include "y.tab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define NO_PRINT_TEXT 300



void if_command(char * str) {

}

bool if_command_node(Node* node) {
    //printf("if command\n");
    //if ((node->node_type == NODE_STR) && ((strcmp(node->label.str, "PAIR_LIST") == 0) || (strcmp(node->label.str, "PARAM_LIST") == 0))) return false;
    if ((node->node_type == NODE_STR) && ((strcmp(node->label.str, "PAIR_LIST") == 0))) return false; 


    switch (node->token)
    {
    case QUOTE:
    case CAR:
    case CDR:
    case CONS:
    case ATOM_PREDICATE:
    case EQUAL:
    case ADD:
    case SUB:
    case MUL:
    case DIVE:
    case REM:
    case LE:
    case COND:
    case LAMBDA:
    case LET:
    case LETREC:
    case NO_PRINT_TEXT:
        return true;
        break;
    default:
        return false;
        break;
    }
}

void print_tree(Node *root, int depth) {
    if (root == NULL) return;
    
    for (int i = 0; i < depth; ++i) {
        if(depth - 1 == i) printf("- ");
        else printf("| ");
    }
    

    if (root->node_type == NODE_NUM)
        printf("%d\n", root->label.num);
    else if (root->node_type == NODE_STR) {
        printf("%s\n", root->label.str);
    }
    
    for (int i = 0; i < root->num_children; ++i) {
        print_tree(root->children[i], depth + 1);
    }
}

void print_tree_string(Node* root) {
    if (root == NULL) return;

    bool is_command;
    is_command = if_command_node(root);

    if (is_command == 1) {
        printf("(");
    }


    if (root->token != NO_PRINT_TEXT) {
        if (root->node_type == NODE_NUM)
        printf("%d ", root->label.num);
        else if (root->node_type == NODE_STR) {
            printf("%s ", root->label.str);
        }
    }
        
    for (int i = 0; i < root->num_children; ++i) {
        print_tree_string(root->children[i]);
    }

    if (is_command) {
        printf(")");
    }
}

Node *create_node(union string_digit_union label, int token, NODE_TYPE node_type) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;

    node->token = token;

    if (node_type == NODE_STR) {
        node->label.str = (char*)malloc(strlen(label.str) + 1);
        strcpy(node->label.str, label.str);
    } 
    else if (node_type == NODE_NUM) {
        node->label.num = label.num;
    }
    node->node_type = node_type;

    node->num_children = 0;

    for (int i = 0; i < MAX_CHILDREN; ++i) {
        node->children[i] = NULL;
    }

    return node;
}

void add_child(Node *parent, Node *child) {
    if (parent->num_children < MAX_CHILDREN) {
        parent->children[parent->num_children++] = child;
    } else {
        fprintf(stderr, "Maximum number of children reached.\n");
    }
}
