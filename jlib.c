#include <string.h>
#include <stdio.h>
#include "jlib.h"

void write_to_file(char* data) {
    FILE* jasmine_file;
    jasmine_file = fopen("result.j", "a+");
    fwrite(data , 1 , strlen(data), jasmine_file);
    fclose(jasmine_file);
}

void process_function_definition(char* return_type, char* func_name, char* arg_types) {
    char func_buf[512] = {0};
    char func_ret_buf[64] = {0};

    if(strcmp(func_name, "main") == 0) {
        strcpy(arg_types, "[Ljava/lang/String;");
    }
    type_map(return_type, func_ret_buf);
    sprintf(func_buf, ".method public static %s(%s)%s\n.limit stack 50\n.limit locals 50\n", func_name, arg_types, func_ret_buf);
    write_to_file(func_buf);
}

void process_variable(char* name, char* value, char* type, int scope, int reg) {
    char var_buf[128] = {0};
    char type_buf[16] = {0};

    type_map(type, type_buf);
    
    // Global variables have scope 0
    if(scope == 0) {
        if(value) {
            sprintf(var_buf, ".field public static %s %s = %s\n", name, type_buf, value);
        }
        // if simply declared (ex: int a; then no need for the latter part)
        else {
            sprintf(var_buf, ".field public static %s %s\n", name, type_buf);
        }
    }
    // Local variables
    else {
        char store[32] = {0};
        if(strcmp(type, "float") == 0) {
            strcpy(store, "fstore");
        }
        else {
            strcpy(store, "istore");
        }

        if(value) {
            sprintf(var_buf, "\tldc %s\n\t%s %d\n", value, store, reg);
        }
        // if simply declared (ex: int a; then no need for the latter part)
        else {
            sprintf(var_buf, "\tldc 0\n\t%s %d\n", store, reg);
        }
    }
    write_to_file(var_buf);
}

void type_map(char* type, char* dest) {
    if(strcmp(type, "int") == 0) {
        strcat(dest, "I");
    }
    else if(strcmp(type, "float") == 0) {
        strcat(dest, "F");
    }
    else if(strcmp(type, "bool") == 0) {
        strcat(dest, "Z");
    }
    else if(strcmp(type, "string") == 0) {
        strcat(dest, "S");
    }
    else if(strcmp(type, "void") == 0) {
        strcat(dest, "V");
    }
    else {
        strcat(dest, "I");
    }
}