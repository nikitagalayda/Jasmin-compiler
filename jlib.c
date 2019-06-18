#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "jlib.h"

#define OUTPUT_BUF_SIZE 256

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

void process_arithmetic(char* operation, char* left_op, int left_reg, int left_scope, char* left_type, int left_arg_type, char* right_op, int right_reg, int right_scope, char* right_type, int right_arg_type, char* last_expr_type) {
    char arithmetic_print[256] = {0};
    // 
    generate_arithmetic_var_code(left_op, left_type, right_type, left_arg_type, left_reg, left_scope, operation);
    printf("left_op: %s\nleft_type: %s\nleft_arg_type: %d\nleft_reg: %d\nleft_scope: %d\n", left_op, left_type, left_arg_type, left_reg, left_scope);

    generate_arithmetic_var_code(right_op, right_type, left_type, right_arg_type, right_reg, right_scope, operation);
    printf("right_op: %s\nright_type: %s\nright_arg_type: %d\nright_reg: %d\nright_scope: %d\n", right_op, right_type, right_arg_type, right_reg, right_scope);

    generate_arithmetic_op_code(operation, left_type, right_type);

}

// Generates code for given variable
// name: var name
// t_type: data type (int/float)
// a_type: argument type (variable/constant/expression)
void generate_arithmetic_var_code(char* name, char* t_type, char* right_op_type, int a_type, int reg, int scope, char* operation) {
    char output_buf[OUTPUT_BUF_SIZE] = {0};
    char type_buf[16] = {0};
    // char operation_buf[8] = {0};
    char cast_buf[8] = {0};
    // char op_type = '\0';

    //------------------------------------------FLOAT OR INT LOAD------------------------------------------
    if(strcmp(t_type, "float") == 0) {
        sprintf(output_buf, "\tfload %d\n", reg);
    }
    else {
        sprintf(output_buf, "\tiload %d\n", reg);
    }

    //------------------------------------------CODE BASED ON TYPE------------------------------------------
    if(a_type == 1) {
        // Variable
        printf("----------name: %s\n-----------reg: %d\n------------scope: %d\n------------type: %d\n", name, reg, scope, a_type);
        if(scope > 0) {
            // Local variable
            // if(strcmp(t_type, "int")) {
            //     sprintf(output_buf, "\tiload %d\n", reg);
            // }
            // else if(strcmp(t_type, "float")) {
            //     sprintf(output_buf, "\tfload %d\n", reg);
            // }
            // else {
            //     sprintf(output_buf, "\tiload %d\n", reg);
            // }
        }
        else {
            // Global variable
            type_map(t_type, type_buf);
            sprintf(output_buf, "\tgetstatic compiler_hw3/%s %s\n", name, type_buf);
        }
    }
    else if(a_type == 2) {
        // Constant
        memset(output_buf, '\0', OUTPUT_BUF_SIZE);
        sprintf(output_buf, "\tldc %s\n", name);
        // strcpy(output_buf, "PLACEHOLDER\n");
    }
    else {
        // Expression
    }
    
    //------------------------------------------CASTING INT TO FLOAT------------------------------------------
    // Assume both operands are ints
    // strcat(operation_buf,"\ti");

    // Check if one of the operands is a float
    if(strcmp(t_type, right_op_type) != 0) {
        // Different types
        // operation_buf[1] = 'f';
        if(strcmp(t_type, "int") == 0) {
            strcpy(cast_buf, "\ti2f\n");
        }
    }

    //------------------------------------------CODE FOR ARITHMETIC OPERATION------------------------------------------
        // Use float instructions
    // if(strcmp(operation, "*") == 0) {
    //     strcat(operation_buf, "mul\n");
    // }
    // else if(strcmp(operation, "%") == 0) {
    //     strcat(operation_buf, "mod\n");
    // }
    // else if(strcmp(operation, "/") == 0) {
    //     strcat(operation_buf, "div\n");
    // }
    // else if(strcmp(operation, "+") == 0) {
    //     strcat(operation_buf, "add\n");
    // }
    // else if(strcmp(operation, "-") == 0) {
    //     strcat(operation_buf, "sub\n");
    // }
    // else {
    //     strcat(operation_buf, "arithmetic operator not supported\n");
    // }

    // strcat(output_buf, operation_buf);
    write_to_file(output_buf);
}

void generate_arithmetic_op_code(char* operation, char* left_type, char* right_type) {
    char output_buf[32] = {0};

    strcat(output_buf,"\ti");
    if(strcmp(left_type, right_type) != 0) {
        // Different types
        output_buf[1] = 'f';
    }

    if(strcmp(operation, "*") == 0) {
        strcat(output_buf, "mul\n");
    }
    else if(strcmp(operation, "%") == 0) {
        strcat(output_buf, "mod\n");
    }
    else if(strcmp(operation, "/") == 0) {
        strcat(output_buf, "div\n");
    }
    else if(strcmp(operation, "+") == 0) {
        strcat(output_buf, "add\n");
    }
    else if(strcmp(operation, "-") == 0) {
        strcat(output_buf, "sub\n");
    }
    else {
        strcat(output_buf, "\top not supported\n");
    }
    
    write_to_file(output_buf);
}