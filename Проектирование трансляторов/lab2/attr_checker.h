#ifndef ATTR_CHECKER_H
#define ATTR_CHECKER_H

    #include <stdbool.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>

    #define ATTRS_INIT_VALUE 20


    FILE* file;
    //char* attrs_ex[] = {"table_name", "id", "name"};
    char* attrs[ATTRS_INIT_VALUE];
    int attrs_count;

    bool find_table_name(char* name) {
        printf("%s <=> %s\n", attrs[0], name);
        if(strcmp(name, attrs[0]) == 0) {
            return true;
        }
        else
            return false;
    }

    bool find_table_attr(char* name) {
        if (attrs_count < 2 ) return false;
        for (int i = 1; i < attrs_count; i++) {
            if (attrs[i] == NULL) return false;
            printf("%s <=> %s\n", attrs[i], name);
            if (strcmp(name, attrs[i]) == 0) 
                return true;
        }
        return false;
    }

    bool open_file() {
        file = fopen("table.db", "r");
        if (file == NULL) {
            return false;
        }
        return true;
    }

    void scan_attrs() {
        attrs_count = 0;
        char buffer[32];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            //printf("%s", buffer);
            //attrs[attrs_count++] = buffer;
            printf("Buffer: %s", buffer);

            attrs[attrs_count] = (char *)malloc(strlen(buffer) + 1);
            if (attrs[attrs_count] == NULL) {
                printf("Ошибка при выделении памяти");
                return; 
            }
            size_t len = strlen(buffer);
            buffer[len-2] = '\0';
            strcpy(attrs[attrs_count], buffer);
            attrs_count++;
        }
        printf("\nAttr_count: %d\n", attrs_count);
    }

    void start_scan() {
        open_file();
        scan_attrs();
    }

    void print_attrs() {
        for (int i = 0; i < attrs_count; i++) {
            printf("%s", attrs[i]);
        }
        int size = sizeof(attrs) / sizeof(attrs[0]);
        printf("\nArray size: %d elements\n", size);
    }

#endif