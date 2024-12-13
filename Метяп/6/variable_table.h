#ifndef VARIABLE_TABLE_H
#define VARIABLE_TABLE_H

#define VARIABLE_TABLE_LEN 15
#define VARIABLE_TABLE_RECORD_COUNT_INIT_VALUE 0

#include <malloc.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
    INT = 1, FLOAT, CHAR_STRING
} variables_types;

typedef union {
    int i;
    float f;
    char* s;
} variable_value;

typedef struct
{
    char* name;
    variables_types type;
    variable_value value;
} variable_description;

typedef struct 
{
    variable_description variables[VARIABLE_TABLE_LEN];
    int records_count;
} variable_table;

variable_table* variable_table_alloc() {
    variable_table* vt = (variable_table*)malloc(sizeof(variable_table));
    variable_table_init(vt);
    return vt;
}


void variable_table_init(variable_table* vt) {
    vt->records_count = VARIABLE_TABLE_RECORD_COUNT_INIT_VALUE;
}

// int variable_table_add_value(variable_table* vt) {
//     return 1;
// }


int variable_table_get_index(variable_table* vt, char* name) {
    for (int i = 0; i < vt->records_count; i++) {
        if (strcmp(vt->variables[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

int variable_table_get_value_int(variable_table* vt, int index) {
    return vt->variables[index].value.i;
}

void add_value_i(variable_table* vt, char* name) {
    char* new_name = (char*)malloc(strlen(name));
    strcpy(new_name, name);
    vt->variables[vt->records_count].name = new_name;
    vt->variables[vt->records_count].type = INT;
    //vt->variables[vt->records_count].value.i = value;
    vt->records_count++;
}

int get_value_i(variable_table* vt, char* name) {
    int index = variable_table_get_index(vt, name);

    if (index < 0) return -1;

    return variable_table_get_value_int(vt, index);
}

int update_value_i(variable_table* vt, char* name, int new_value) {
    int index = variable_table_get_index(vt, name);

    if (index < 0) return -1;

    vt->variables[index].value.i = new_value;
    return 1;
}

void print_variables(variable_table* vt){
    for (int i = 0; i < vt->records_count; i++) {
        printf("VAR: %s = %d;\n", vt->variables[i].name, vt->variables[i].value.i);
    }
}


#endif