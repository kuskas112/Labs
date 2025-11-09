#ifndef ANALYZER_H
#define ANALYZER_H

#include "tree.h"
#include "y.tab.h"
#include <stdbool.h>

extern pnode root;
extern pnode get_AST_root();

#define ANSWER_TYPE int

bool is_leaf_node(pnode node);
ANSWER_TYPE exec_tree(pnode node);
ANSWER_TYPE exec_command(pnode node);




#endif