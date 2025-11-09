#include "tree.h"
#include "y.tab.h"
#include "analyzer.h"

bool is_leaf_node(pnode node) {
    if (node->token == S_ATOM || node->token == D_ATOM)
    {
        return true;
    }
    return false;
}

ANSWER_TYPE exec_command(pnode node) {
    if (node == NULL) return NULL;
    ANSWER_TYPE res = 0;

    switch (node->token)
    {
    case S_ATOM:
        break;
    case D_ATOM:
        res = node->label.num;
        break;
    case ADD:
        res = exec_command(node->children[0]) + exec_command(node->children[1]);
        break;
    case SUB:
        res = exec_command(node->children[0]) - exec_command(node->children[1]);
        break;
    case MUL:
        res = exec_command(node->children[0]) * exec_command(node->children[1]);
        break;
    case DIVE:
        res = exec_command(node->children[0]) / exec_command(node->children[1]);
        break;
    default:
        puts("Syntax Error: Unknown command token\n");
        break;
    }

    return res;
}



ANSWER_TYPE exec_tree(pnode node) {
    if (node == NULL) return NULL;


}

int main(void) {
    get_AST_root();
    //print_tree(root, 0);
    

    printf("Result: %d\n", exec_command(root));
    return 0;
}


