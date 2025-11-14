#ifndef ANALYZER_H
#define ANALYZER_H

#include "types.h"
#include "tree.h"
#include "y.tab.h"
#include "list.h"
#include <stdbool.h>

extern pnode root;
extern pnode get_AST_root();


#define ANSWER_TYPE ANSWER_STRUCT*




void drop_error();

//ANSWER_TYPE create_answer(union value val, NODE_TYPE type);
ANSWER_TYPE create_answer();
void fill_answer(ANSWER_TYPE answer, union answer_value val, NODE_TYPE type);
void print_answer(ANSWER_TYPE answer);

bool is_leaf_node(pnode node);
bool check_types(pnode node, NODE_TYPE expected_type);
bool is_num(ANSWER_TYPE node);
bool is_atom(ANSWER_TYPE);

ANSWER_TYPE exec_tree(pnode node);
ANSWER_TYPE exec_command(pnode node);

void num_check(ANSWER_TYPE a, ANSWER_TYPE b);
void set_val(union answer_value *val, Node_List *node);

// === LAMBDA ===

lambda_struct* create_lambda(List* params, pnode body, Enviroment* env);
lambda_struct* copy_lambda(lambda_struct orig);

ANSWER_TYPE apply_lambda(lambda_struct*, List*);

Enviroment* create_env(Enviroment* parent);
#endif