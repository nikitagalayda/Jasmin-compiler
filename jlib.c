#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "jlib.h"

#define OUTPUT_BUF_SIZE 256

void write_to_file(char* data) {
    FILE* jasmine_file;
    jasmine_file = fopen("compiler_hw3.j", "a+");
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
        else if(strcmp(type, "string") == 0) {
            strcpy(store, "astore");
        }
        else {
            strcpy(store, "istore");
        }

        if(value) {
            if(strcmp(type, "string") == 0) {
                sprintf(var_buf, "\tldc \"%s\"\n\t%s %d\n", value, store, reg);
            }
            else {
                sprintf(var_buf, "\tldc %s\n\t%s %d\n", value, store, reg);
            }
        }
        // if simply declared (ex: int a; then no need for the latter part)
        else {
            sprintf(var_buf, "\tldc 0\n\t%s %d\n", store, reg);
        }
    }
    write_to_file(var_buf);
}

void process_var_assgn_single(char* right_val, char* left_type, char* right_type, char* right_arg_type, int left_reg, int right_reg) {
    char output_buf[256] = {0};
    char right_type_str[8] = {0};
    char left_type_str[8] = {0};

    if((strcmp(right_arg_type, "function") != 0) && (strcmp(right_arg_type, "expr") != 0)) {
        if(right_reg < 0) {
            // Right side is a constant.
            sprintf(output_buf, "\tldc %s\n", right_val);
        }
        else {
            if(strcmp(right_type, "float") == 0) {
                sprintf(output_buf, "\tfload %d\n", right_reg);
            }
            else if(strcmp(right_type, "int") == 0) {
                sprintf(output_buf, "\tiload %d\n", right_reg);
            }
            // Right side is a constant.
        }
        // Write the correct load.
        write_to_file(output_buf);
    }

    generate_cast_code(left_type, right_type);

    if(strcmp(left_type, "int") == 0) {
            // Integer
            sprintf(output_buf, "\tistore %d\n", left_reg);
        }
    else if(strcmp(left_type, "float") == 0) {
        // Float
        sprintf(output_buf, "\tfstore %d\n", left_reg);
    }
    // strcat(output_buf, store_buf);
    // Write the correct store.
    write_to_file(output_buf);
}

void type_map(char* type, char* dest) {
    // changed from strcat --> strcpy
    if(strcmp(type, "int") == 0) {
        strcpy(dest, "I");
    }
    else if(strcmp(type, "float") == 0) {
        strcpy(dest, "F");
    }
    else if(strcmp(type, "bool") == 0) {
        strcpy(dest, "Z");
    }
    else if(strcmp(type, "string") == 0) {
        strcpy(dest, "S");
    }
    else if(strcmp(type, "void") == 0) {
        strcpy(dest, "V");
    }
    else {
        strcpy(dest, "I");
    }
}

void process_arithmetic(char* operation, char* left_op, int left_reg, int left_scope, char* left_type, int left_arg_type, char* right_op, int right_reg, int right_scope, char* right_type, int right_arg_type, char* last_expr_type) {
    // char arithmetic_print[256] = {0};
    // 
    // printf("left_op: %s\nleft_type: %s\nleft_arg_type: %d\nleft_reg: %d\nleft_scope: %d\n", left_op, left_type, left_arg_type, left_reg, left_scope);
    // printf("right_op: %s\nright_type: %s\nright_arg_type: %d\nright_reg: %d\nright_scope: %d\n", right_op, right_type, right_arg_type, right_reg, right_scope);

    generate_arithmetic_var_code(left_op, left_type, right_type, left_arg_type, left_reg, left_scope, operation, last_expr_type);
    generate_arithmetic_var_code(right_op, right_type, left_type, right_arg_type, right_reg, right_scope, operation, last_expr_type);

    generate_arithmetic_op_code(operation, left_type, right_type);

}

// Generates code for given variable
// name: var name
// t_type: data type (int/float)
// a_type: argument type (variable/constant/expression)
void generate_arithmetic_var_code(char* name, char* t_type, char* right_op_type, int a_type, int reg, int scope, char* operation, char* last_expr_type) {
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
        // printf("----------name: %s\n-----------reg: %d\n------------scope: %d\n------------type: %d\n", name, reg, scope, a_type);
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
        return;
    }
    
    //------------------------------------------CASTING INT TO FLOAT------------------------------------------
    // Assume both operands are ints
    // strcat(operation_buf,"\ti");
    // printf("\nt_type: %s\nright_op_type: %s\n", t_type, right_op_type);
    // Check if one of the operands is a float
    if(strcmp(t_type, right_op_type) != 0) {
        // printf("IN COMPARISON RIGHT_OP_TYPE\n");
        // Different types
        // operation_buf[1] = 'f';
        strcpy(last_expr_type, "float");
        if(strcmp(t_type, "int") == 0) {
            strcpy(cast_buf, "\ti2f\n");
        }
    }
    else {
        strcpy(last_expr_type, "int");
    }

    //------------------------------------------CODE FOR ARITHMETIC OPERATION------------------------------------------

    // strcat(output_buf, operation_buf);
    strcat(output_buf, cast_buf);
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
    //--------------------------OPERATION-ASSIGNMENT-----------------
    else if(strcmp(operation, "-=") == 0) {
        strcat(output_buf, "sub\n");
    }
    else if(strcmp(operation, "+=") == 0) {
        strcat(output_buf, "add\n");
    }
    else if(strcmp(operation, "*=") == 0) {
        strcat(output_buf, "mul\n");
    }
    else if(strcmp(operation, "/=") == 0) {
        strcat(output_buf, "div\n");
    }
    else if(strcmp(operation, "%=") == 0) {
        strcat(output_buf, "mod\n");
    }
    // -------------------------RELATIONAL---------------------------
    else if(strcmp(operation, ">") == 0) {
        strcat(output_buf, "sub\n");
    }
    else if(strcmp(operation, "<") == 0) {
        strcat(output_buf, "sub\n");
    }
    else if(strcmp(operation, ">=") == 0) {
        strcat(output_buf, "sub\n");
    }
    else if(strcmp(operation, "<=") == 0) {
        strcat(output_buf, "sub\n");
    }
    else if(strcmp(operation, "==") == 0) {
        strcat(output_buf, "sub\n");
    }
    else if(strcmp(operation, "!=") == 0) {
        strcat(output_buf, "sub\n");
    }
    else {
        strcat(output_buf, "\top not supported\n");
    }
    
    write_to_file(output_buf);
}

void generate_cast_code(char* left_type, char* right_type) {
    if(strcmp(left_type, right_type) != 0) {
        if(strcmp(left_type, "float") == 0) {
            write_to_file("\ti2f\n");
        }
        else if(strcmp(left_type, "int") == 0) {
            write_to_file("\tf2i\n");
        }
    }
}

void generate_func_definition_end(char* return_type) {
    if(strcmp(return_type, "int") == 0) {
        write_to_file("\tireturn\n");
    }
    else if(strcmp(return_type, "float") == 0) {
        write_to_file("\tfreturn\n");
    }
    else {
        write_to_file("\treturn\n");
    }
    write_to_file(".end method\n");
}

void generate_print_function(char* val, char* type, int reg, int scope) {
    char output_buf[256] = {0};
    char load_buf[16] = {0};
    char type_buf[64] = {0};


    if(strcmp(type, "float") == 0) {
            // float
            sprintf(load_buf, "\tfload %d\n", reg);
            // strcpy(type_buf, "F");
            strcpy(output_buf, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n\tinvokevirtual java/io/PrintStream/println(F)V\n");
    }
    else if(strcmp(type, "int") == 0) {
        //int 
        sprintf(load_buf, "\tiload %d\n", reg);
        // strcpy(type_buf, "I");
        strcpy(output_buf, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n\tinvokevirtual java/io/PrintStream/println(I)V\n");
    }
    else {
        // string 
        strcpy(output_buf, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
    }

    if(reg < 0) {
        // Constant or global variable
        if(scope == 0) {
            // Global variable

            char type_mapped[8] = {0};
            type_map(type, type_mapped);

            sprintf(load_buf, "\tgetstatic compiler_hw3/%s %s\n", val, type_mapped);
        }
        else {
            // Constant or string
            if(strcmp(type, "str") == 0) {
                sprintf(load_buf, "\tldc \"%s\"\n", val);
            }
            else {
                sprintf(load_buf, "\tldc %s\n", val);
            }
        }
    }
    write_to_file(load_buf);
    write_to_file(output_buf);
}

void generate_function_call(char* name, char* param_types, char* params, char* ret_type) {
    char params_buf[64] = {0};
    char output_buf[256] = {0};
    char return_type[8] = {0};
    type_map(ret_type, return_type);

    // load_func_params(param_types, params);

    char* token = strtok(param_types, ",");
    while( token != NULL ) {
        char mapped_type[8] = {0};
        type_map(token, mapped_type);
        strcat(params_buf, mapped_type);
        token = strtok(NULL, ",");
    }
    if(strlen(params_buf) == 0) {
        strcpy(params_buf, "V");
    }
    sprintf(output_buf, "\tinvokestatic compiler_hw3/%s(%s)%s\n", name, params_buf, return_type);
    write_to_file(output_buf);
}

void load_single_var(char* val, int arg_type, int scope, int reg, char* type) {
    char output_buf[256] = {0};
    if(arg_type == 1) {
        // Variable
        if(reg < 0) {
            // Global variable
        }
        else {
            // Local variable
            if(strcmp(type, "int") == 0) {
            // int
            sprintf(output_buf, "\tiload %d\n", reg);
            }
            else {
                // float
                sprintf(output_buf, "\tfload %d\n", reg);
            }
        }
    }
    else if(arg_type == 2) {
        sprintf(output_buf, "\tldc %s\n", val);
    }

    write_to_file(output_buf);
}

void generate_while_branch(char* operator) {
    char output_buf[256] = {0};
    
    if(strcmp(operator, ">") == 0) {
        sprintf(output_buf, "\tifgt LABEL_TRUE\n\tgoto LABEL_FALSE\nLABEL_TRUE:\n");
    }
    else if(strcmp(operator, "<") == 0) {
        sprintf(output_buf, "\tiflt LABEL_TRUE\n\tgoto LABEL_FALSE\nLABEL_TRUE:\n");
    }
    else if(strcmp(operator, ">=") == 0) {
        sprintf(output_buf, "\tifge LABEL_TRUE\n\tgoto LABEL_FALSE\nLABEL_TRUE:\n");
    }
    else if(strcmp(operator, "<=") == 0) {
        sprintf(output_buf, "\tifle LABEL_TRUE\n\tgoto LABEL_FALSE\nLABEL_TRUE:\n");
    }
    else if(strcmp(operator, "==") == 0) {
        sprintf(output_buf, "\tifeq LABEL_TRUE\n\tgoto LABEL_FALSE\nLABEL_TRUE:\n");
    }
    else if(strcmp(operator, "!=") == 0) {
        sprintf(output_buf, "\tifne LABEL_TRUE\n\tgoto LABEL_FALSE\nLABEL_TRUE:\n");
    }
    
    write_to_file(output_buf);
}