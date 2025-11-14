#include "tree.h"
#include "y.tab.h"
#include "analyzer.h"

// === LAMBDA ==

lambda_struct* create_lambda(List* params, pnode body, Enviroment* env)
{
    lambda_struct* lambda = (lambda_struct*)malloc(sizeof(lambda_struct));

    lambda->params = params;
    lambda->body = body;
    lambda->env = env;

    return lambda;
}


Enviroment* create_env(Enviroment* parent)
{
    Enviroment* env = (Enviroment*)malloc(sizeof(Enviroment));

    env->bindings = NULL;
    env->parent = parent;

    return env;
}

void enviroment_bind(Enviroment* env, const char* name, ANSWER_TYPE value)
{
    struct Binding* bind = (struct Binding*)malloc(sizeof(struct Binding));

    bind->name = strdup(name);
    bind->value = value;
    bind->next = env->bindings;
    env->bindings = bind;

}

ANSWER_TYPE enviroment_lookup(Enviroment* env, const char* name)
{
    Enviroment* current_env = env;

    while (current_env != NULL)
    {
        struct Binding* current_bind = current_env->bindings;

        while (current_bind != NULL)
        {
            if (strcmp(current_bind->name, name) == 0)
            {
                return current_bind->value;
            }
            current_bind = current_bind->next;
        }

        current_env = current_env->parent;
    }

    return NULL; // Not found
}


// === END LAMBDA ===

void drop_error()
{
    puts("EXECUTE ERROR");
    exit(EXIT_FAILURE);
}

bool is_leaf_node(pnode node) {
    if (node->token == S_ATOM || node->token == D_ATOM)
    {
        return true;
    }
    return false;
}

bool check_types(pnode node, NODE_TYPE expected_type) {
    return node->node_type == expected_type;
}

bool is_num(ANSWER_TYPE node)
{
    return node->type == NODE_NUM;
}

void num_check(ANSWER_TYPE a, ANSWER_TYPE b)
{
    if (!(is_num(a) && is_num(b)))
    {
        puts("ERRR");
        exit(EXIT_FAILURE);    
    }  
}

bool is_atom(ANSWER_TYPE node)
{
    return node->type != NODE_LIST;
}

bool is_list(ANSWER_TYPE node)
{
    return node->type == NODE_LIST;
}

ANSWER_TYPE create_answer() {
    return (ANSWER_TYPE)malloc(sizeof(ANSWER_STRUCT));
}

void set_val(union answer_value *val, Node_List *node)
{
    //if (!(val && node)) puts("AAAAAAAAAAAAAAAA");

    switch (node->node_type)
    {
    case NODE_STR:
        val->str = node->node_value.str;
        break;
    case NODE_NUM:
        val->num = node->node_value.num;
        break;
    case NODE_LIST:
        val->list = node->node_value.list;
        break;
    default:
        
        break;
    }
}


void fill_answer(ANSWER_TYPE answer, union answer_value val, NODE_TYPE type) {
    answer->type = type;
    switch (type)
    {
    case NODE_NUM:
        answer->value.num = val.num;
        break;
    case NODE_STR:
        answer->value.str = val.str;
        break;
    case NODE_LIST:
        answer->value.list = val.list;
        break;
    case NODE_BOOL:
        answer->value.num = val.num;
        break;
    default:
        puts("Error: Unknown type in fill_answer\n");
        break;
    }
}

ANSWER_TYPE apply_lambda(lambda_struct* lambda, List* args)
{
    if (lambda->params->length != args->length) drop_error();

    Enviroment* lambda_env = create_env(lambda->env);

    Node_List* param_node = lambda->params->first;
    Node_List* arg_node = args->first;

    while (param_node != NULL && arg_node != NULL)
    {
        if (param_node->node_type != NODE_STR) drop_error();
    }

    
}

ANSWER_TYPE exec_command(pnode node) {
    if (node == NULL) return NULL;
    ANSWER_TYPE res = create_answer();

    union answer_value val;

    ANSWER_STRUCT *a, *b, *c;

    if (false) 
    {
        
        
    }
    else 
    {
        switch (node->token)
        {
        /* BAZED */
        case S_ATOM:
            val.str = node->label.str;
            fill_answer(res, val, NODE_STR);
            break;
        case D_ATOM:
            //res = node->label.num;
            //fill_answer(res, (union answer_value){.num = node->label.num}, NODE_NUM);
            
            val.num = node->label.num;
            fill_answer(res, val, NODE_NUM);
            break;

        /* MATH */
        
        case ADD:
            a = exec_command(node->children[0]); b = exec_command(node->children[1]);
            num_check(a, b);         
            val.num = a->value.num + b->value.num;
            fill_answer(res, val, NODE_NUM);
            break;
        case SUB:
            a = exec_command(node->children[0]); b = exec_command(node->children[1]);
            num_check(a, b);         
            val.num = a->value.num - b->value.num;
            fill_answer(res, val, NODE_NUM);
            break;
        case MUL:
            a = exec_command(node->children[0]); b = exec_command(node->children[1]);
            num_check(a, b);         
            val.num = a->value.num * b->value.num;
            fill_answer(res, val, NODE_NUM);
            break;
        case DIVE:
            a = exec_command(node->children[0]); b = exec_command(node->children[1]);
            num_check(a, b);         
            val.num = a->value.num / b->value.num;
            fill_answer(res, val, NODE_NUM);
            break;
        case REM:
            a = exec_command(node->children[0]); b = exec_command(node->children[1]);
            num_check(a, b);         
            val.num = a->value.num % b->value.num;
            fill_answer(res, val, NODE_NUM);
            break;

        /* LIST */

        case CAR:
            Node_List* head = get_head(exec_command(node->children[0])->value.list);
            
            /*
            if (head->node_type == NODE_STR)
            {
                val.str = head->node_value.str;
            }
            else if (head->node_type == NODE_NUM)
            {
                val.num = head->node_value.num;
            }
            else if (head->node_type == NODE_LIST)
            {
                val.list = head->node_value.list;
            }
            */
           
           set_val(&val, head);
           fill_answer(res, val, head->node_type);

            break;
        case CDR:

            List* tail = get_tail(exec_command(node->children[0])->value.list);
            val.list = tail;
            fill_answer(res, val, NODE_LIST);

            break;

        case CONS:
            a = exec_command(node->children[0]); b = exec_command(node->children[1]);
            if (!(is_list(b))) drop_error();

            prepend_to_list(b->value.list, a->value, a->type);

            val.list = b->value.list;
            fill_answer(res, val, NODE_LIST);
            break;

        case QUOTE:
            val = exec_command(node->children[0])->value;
            fill_answer(res, val, node->children[0]->node_type);
            break;

        


        
        /*
        case LIST:
        List* list = create_list();
        for (int i = 0; i < node->num_children; i++) {
            union answer_value list_el = {0};

            if (node->children[i]->node_type == NODE_STR) 
            {
                list_el.str = node->children[i]->label.str;
                append_to_list(list, list_el, NODE_STR);
            }
            else if (node->children[i]->node_type == NODE_NUM)
            {
                    list_el.num = node->children[i]->label.num;
                    append_to_list(list, list_el, NODE_NUM);
                }
                else if (node->children[i]->node_type == NODE_LIST)
                {
                    list_el.list = 
                    
                }
                
            }

            val.list = list;
            fill_answer(res, val, NODE_LIST);
            
            break;
        */
        case LIST:
            List* list = create_list();

            for (int i = 0; i < node->num_children; i++)
            {
                ANSWER_TYPE child_answer = exec_command(node->children[i]);

                if (!child_answer)
                {
                    puts("ERROR: Child");
                    return NULL;
                }

                union answer_value list_el = {0};

                switch (child_answer->type)
                {
                case NODE_NUM:
                    list_el.num = child_answer->value.num;
                    append_to_list(list, list_el, NODE_NUM);
                    break;
                case NODE_STR:
                    list_el.str = child_answer->value.str;
                    append_to_list(list, list_el, NODE_STR);
                    break;
                case NODE_LIST:
                    list_el.list = child_answer->value.list;
                    append_to_list(list, list_el, NODE_LIST);
                    break;
                default:
                    puts("ERROR: unsupported type in LIST");
                    return NULL;
                    break;
                }
            }

            val.list = list;
            fill_answer(res, val, NODE_LIST);

            break;
        /* BOOL */
        case ATOM_PREDICATE:
            a = exec_command(node->children[0]);
            val.num = is_atom(a);
            fill_answer(res, val, NODE_BOOL);
            break;
        case LE:
            a = exec_command(node->children[0]); b = exec_command(node->children[1]);
            num_check(a, b);
            val.num = a->value.num <= b->value.num;
            fill_answer(res, val, NODE_BOOL);
            break;
        case EQUAL:
            a = exec_command(node->children[0]); b = exec_command(node->children[1]);
            if (!(is_atom(a) || !(is_atom(b)))) drop_error();
            val.num = a->value.num == b->value.num;
            fill_answer(res, val, NODE_BOOL);
            break;
        case COND:
            a = exec_command(node->children[0]);
            if (a->value.num)
            {
                b = exec_command(node->children[1]);
            }
            else
            {
                b = exec_command(node->children[2]);
            }
            val = b->value;
            fill_answer(res, val, b->type);
            break;
        
        /* LAMBDA */
        case LAMBDA:
            if (node->num_children != 2) drop_error();

            pnode params_node = node->children[0];
            pnode body_node = node->children[1];

            if (params_node->token != PARAM_LIST) drop_error();

            List* params_list = create_list();
            for (int i = 0; i < params_node->num_children; i++)
            {
                pnode param_node = params_node->children[i];
                if (param_node->token != S_ATOM) drop_error();

                union answer_value param_val;
                param_val.str = param_node->label.str;
                append_to_list(params_list, param_val, NODE_STR);
            }

            lambda_struct* lambda = create_lambda(params_list, body_node, NULL);

            val.lambda = lambda;
            fill_answer(res, val, NODE_LAMBDA);
            break;
        case LET:
            //TODO
            break;
        default:
            //puts("Syntax Error: Unknown command token\n");
            printf("Syntax Error: Unknown command \ntoken: %d\n", node->token);
            break;
        }
    }
    

    //print_answer(res);
    return res;
}

void print_answer(ANSWER_TYPE answer) {
    switch (answer->type)
    {
    case NODE_NUM:
        printf("Answer (num): %d\n", answer->value.num);
        break;
    case NODE_STR:
        printf("Answer (str): %s\n", answer->value.str);
        break;
    case NODE_LIST:
        printf("Answer (list): ");
        print_list(answer->value.list); // Assuming list of numbers for simplicity
        printf("\n");
        break;
    case NODE_BOOL:
        if (answer->value.num)
        {
            printf("TRUE\n");
        }
        else
        {
            printf("FALSE\n");
        }
        break;
    default:
        printf("Answer: Unknown type - %d\n", answer->type);
        break;
    }
}


int main(void) {
    get_AST_root();
    print_tree(root, 0);
    puts("END PRINT\n");
    

    ANSWER_TYPE answer = exec_command(root);
    print_answer(answer);


    /*
    List* list = create_list();
    prepend_to_list(list, (union answer_value){.num = 1}, NODE_NUM);
    prepend_to_list(list, (union answer_value){.num = 2}, NODE_NUM);
    prepend_to_list(list, (union answer_value){.num = 3}, NODE_NUM);
    print_list(list);
    */
    return 0;
}


