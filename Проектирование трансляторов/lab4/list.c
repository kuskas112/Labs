#include "list.h"

List* create_list() {
    List* list = (List*)malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return list;
}

Node_List* create_node_list(union answer_value value, NODE_TYPE node_type) {
    Node_List* node = (Node_List*)malloc(sizeof(Node_List));
    node->next = NULL;
    //node->prev = NULL;

    if (node_type == NODE_STR) {
        char* str_value = (char*)malloc(strlen(value.str) + 1);
        strcpy(str_value, value.str);
        node->node_type =  NODE_STR;
        node->node_value.str = str_value;
    }
    else if (node_type == NODE_NUM) {
        //int* num_value = (int*)malloc(sizeof(int));
        //*num_value = value.num;
        node->node_type = NODE_NUM;
        node->node_value.num = value.num;
    }
    else if (node_type == NODE_LIST)
    {
        node->node_type = NODE_LIST;
        node->node_value.list = value.list;
    }
    return node;
}

void append_to_list(List* list, union answer_value value, NODE_TYPE node_type) {
    Node_List* new_node = create_node_list(value, node_type);
    if (list->length == 0) {
        list->first = new_node;
        list->last = new_node;
    } else {
        //new_node->prev = list->last;
        list->last->next = new_node;
        list->last = new_node;
    }
    list->length++;
}

void prepend_to_list(List* list, union answer_value value, NODE_TYPE node_type) {
    Node_List* new_node = create_node_list(value, node_type);
    if (list->length == 0) {
        list->first = new_node;
        list->last = new_node;
    } else {
        new_node->next = list->first;
        //list->first->prev = new_node;
        list->first = new_node;
    }
    list->length++;
}

Node_List* get_head(List* list) {
    return list->first;
}

List* get_tail(List* list) {
    if (list->length <= 1) {
        return NULL;
    }

    List* tail_list = create_list();
    tail_list = copy_list(list);
    pop_list(tail_list, 0);
    return tail_list;
}

/*
void print_list(List* list, NODE_TYPE node_type) {
    Node_List* current = list->first;
    printf("[");
    while (current != NULL) {
        if (node_type == NODE_NUM) {
            printf("%d", *((int*)current->value));
        } else if (node_type == NODE_STR) {
            printf("%s", (char*)current->value);
        }
        current = current->next;
        if (current != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}
*/

void print_list(List* list)
{
    Node_List* curr = list->first;
    printf("[");

    while (curr != NULL)
    {
        if (curr->node_type == NODE_NUM)
        {
            printf("%d", curr->node_value.num);
        }
        else if (curr->node_type == NODE_STR)
        {
            printf("%s", curr->node_value.str);
        }
        else if (curr->node_type == NODE_LIST)
        {
            print_list(curr->node_value.list);
        }

        curr = curr->next;
        if (curr != NULL)
        {
            printf(", ");
        }
    }
    
    printf("]");
}

List* copy_list(List* original)
{
    if (!original) return NULL;

    List* new_list = create_list();
    Node_List* current = original->first;

    while (current != NULL)
    {
        union answer_value val;
        if (current->node_type == NODE_NUM)
        {
            val.num = current->node_value.num;
            append_to_list(new_list, val, NODE_NUM);
        }
        else if (current->node_type == NODE_STR)
        {
            val.str = current->node_value.str;
            append_to_list(new_list, val, NODE_STR);
        }
        else if (current->node_type == NODE_LIST)
        {
            List* copied_sublist = copy_list(current->node_value.list);
            val.list = copied_sublist;
            append_to_list(new_list, val, NODE_LIST);
        }

        current = current->next;
    }

    new_list->length = original->length;
    return new_list;
}

void pop_list(List* list, int pos)
{
    if (!list) return;
    if (pos == 0)
    {
        Node_List* to_delete = list->first;
        list->first = list->first->next;
        delete_node_list(to_delete);
        list->length--;
        return;
    }
}

void delete_node_list(Node_List* node)
{
    if (!node) return;

    if (node->node_type == NODE_STR)
    {
        free(node->node_value.str);
    }
    else if (node->node_type == NODE_LIST)
    {
        delete_list(node->node_value.list);
    }

    free(node);
}

void delete_list(List* list)
{
    if (!list) return;

    Node_List* current = list->first;
    Node_List* next_node = NULL;

    while (current != NULL)
    {
        next_node = current->next;
        delete_node_list(current);
        current = next_node;
    }

    free(list);
}