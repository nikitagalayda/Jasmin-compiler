/*	Definition section */
%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "jlib.h"

extern void yyerror(char*);

// typedef struct func_node {
//     char name[64];
//     struct func_node* next;
// } func_node_t;

typedef struct node {
    char name[64];
    char entry_type[16];
    char data_type[16];
    int scope_level;
    char formal_param[256];
    struct node* next;
    bool f_decl;
    int reg_id;
} node_t;

bool udecl_func = false;
bool check_undeclared = false;
node_t* symbol_table[10];
int curr_scope = 0;
char curr_dtype[16];
char curr_etype[16];
char* params;
bool parsing_func = false;
bool semantic_error = false;
bool function_error = false;
char error_msg[128];
char error_cause_name[32];
node_t* curr_node;
char func_def_param_types[32] = {0};    // functions parameter type list, used for jasmine code generation for functions
char* last_expr_type = NULL;            // the type of last arithmetic expression
FILE* jasmine_file;                     // final file that is written to


#define TRAVERSE_LIST(i) for(node_t* it = symbol_table[i]; it; it=it->next)
#define TRAVERSE_LIST_AFTER_HEAD(i) for(node_t* it = symbol_table[i]->next; it; it=it->next)
#define TRAVERSE_SCOPE_AFTER_HEAD(i) for(node_t* it = symbol_table[i]->next; it; it=it->next)
//#define TRAVERSE_FUNC_LIST for(func_node_t* it = decl_func_head; it; it=it->next)

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[1024];  // Get current code line from lex

/* Symbol table function - you can add new function if needed. */
void yyerror(char*);
int lookup_symbol(char*, int);
void create_symbol();
void insert_symbol(char*, char*, char*, int);
void dump_symbol(bool);
void set_err_msg(bool, bool, char*);
void erase_table_scope(int);
int find_highest_reg(int);
int find_var_reg(char*, int);
int find_var(char*, int, int*, int*, char*);
%}

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 */
%union {
    int i_val;
    double f_val;
    char string[32];
    _Bool bool_val;
}

/* Token without return */
%token ADD SUB MUL DIV MOD INC DEC
%token MT LT MTE LTE EQ NE  
%token ASGN ADDASGN SUBASGN MULASGN DIVASGN MODASGN
%token AND OR NOT
%token LB RB LCB RCB LSB RSB COMMA
%token PRINT 
%token IF ELSE  
%token FOR WHILE
%token ID SEMICOLON
%token RET QUOTA
%token INT FLOAT STRING VOID BOOL

/* Token with return, which need to specify type */
%token <i_val> I_CONST
%token  <f_val> F_CONST
%token <string> STR_CONST
%token <bool_val> TRUE
%token <bool_val> FALSE

/* Nonterminal with return, which need to sepcify type */
%type <string> type
%type <string> id_expression
%type <string> func_item    // Recursively return argument types of function
%type <string> expression
%type <string> assignment_expression
%type <string> logical_expression
%type <string> relational_expression
// %type <string> arithmetic_expression
%type <string> unary_expression
%type <string> postfix_expression
%type <string> primary_expression
%type <string> constant

%type <string> cast_expression

// Arithmetics
%type <string> additive_expression
%type <string> multiplicative_expression
%type <string> arithmetic_operator_high
%type <string> arithmetic_operator_low


// Assigment expressions (a = b + c)
%type <string> assignment_operator

//%type <string> func_item_list // A string containing types of function arguments (ex: III...I)
/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%
program
    : program stat
    |
;

stat
    : declaration
    | compound_stat
    | expression_stat
    | print_func
    | selection_statement
    | iteration_statement
    | return_expression

;

return_expression
    : RET SEMICOLON
    | RET assignment_expression SEMICOLON
;

declaration
    : type id_expression ASGN expression SEMICOLON { 
        insert_symbol($1, $2, "variable", curr_scope);
        int reg = 0;
        if(curr_scope != 0) {
            reg =  find_var_reg($2, curr_scope);
        }
        process_variable($2, $4, $1, curr_scope, reg);
    }
    | type id_expression SEMICOLON { 
        insert_symbol($1, $2, "variable", curr_scope); 
        int reg = 0;
        if(curr_scope != 0) {
            reg =  find_var_reg($2, curr_scope);
        }
        process_variable($2, NULL, $1, curr_scope, reg);
    }
    | type id_expression LB func_item_list RB { 
        insert_symbol($1, $2, "function", curr_scope); 
        process_function_definition($1, $2, func_def_param_types);
    }
    | type id_expression LB func_item_list RB SEMICOLON {
        insert_symbol($1, $2, "function_decl", curr_scope);
        erase_table_scope(curr_scope+1); 
    }
;

func_item_list
    : func_item_list COMMA func_item {
        type_map($3, func_def_param_types);
        printf("%s\n", func_def_param_types);
    }
    | func_item {
        type_map($1, func_def_param_types);
    }
    
;

func_item
    : type id_expression { 
        insert_symbol($1, $2, "parameter", curr_scope+1); 
        strcpy($$, $1);
        // another production that I deleted | assignment_expression   
    }
    |
;

compound_stat
    : LCB {++curr_scope;} RCB {--curr_scope;}
    | LCB {++curr_scope;} block_item_list RCB { /*dump_symbol(false);*/ --curr_scope; } 
;

block_item_list
    : block_item 
    | block_item_list block_item
;

block_item
    : stat
;

expression_stat
    : SEMICOLON
    | expression SEMICOLON
;

print_func
    : PRINT LB QUOTA STR_CONST QUOTA RB SEMICOLON
    | PRINT LB postfix_expression RB SEMICOLON
;

primary_expression
	: ID { strcpy($$, yytext); lookup_symbol(yytext, curr_scope); strcat(error_msg, error_cause_name); }
	| constant {
        strcpy($$, $1);
    }
	| LB expression RB {
        strcpy($$, $2);
    }
;

constant
    : F_CONST {
        // Convert the specific types into string (float/int/etc --> int)
        char conv_type[32] = {0};
        sprintf(conv_type, "%f", $1);
        strcpy($$, conv_type);
    }
    | I_CONST {
        char conv_type[32] = {0};
        sprintf(conv_type, "%d", $1);
        strcpy($$, conv_type);
    }
    | QUOTA STR_CONST QUOTA {
        char conv_type[32] = {0};
        sprintf(conv_type, "%s", $2);
        strcpy($$, conv_type);
    }
    | TRUE {
        char conv_type[32] = {0};
        sprintf(conv_type, "%s", "true");
        strcpy($$, conv_type);
    }
    | FALSE {
        char conv_type[32] = {0};
        sprintf(conv_type, "%s", "false");
        strcpy($$, conv_type);
    }
;

unary_operator
	: ADD
	| SUB
	| NOT
;

expression
	: assignment_expression {
        strcpy($$, $1);
    }
	| expression COMMA assignment_expression
;

assignment_expression
	: unary_expression assignment_operator logical_expression {

    }
    | logical_expression {
        strcpy($$, $1);
    }
;

logical_expression
    : logical_expression OR relational_expression
    | logical_expression AND relational_expression
    | relational_expression {
        strcpy($$, $1);
    }
;
/*
relational_expression
    : relational_expression relational_operator arithmetic_expression
    | arithmetic_expression {
        strcpy($$, $1);
    }
;
*/

relational_expression
    : relational_expression relational_operator additive_expression
    | additive_expression {
        // strcpy($$, $1);
    }
;


additive_expression
	: multiplicative_expression
	| additive_expression arithmetic_operator_low multiplicative_expression {
        sprintf($$, "%s %s %s", $1, $2, $3);
        int var_scope, var_scope2;
        int var_reg, var_reg2;
        char var_type[32] = {0};
        char var_type2[32] = {0};
        if(!last_expr_type) {
            last_expr_type = (char*)malloc(128);
        }
        
        // check whether the arguments of multiplication are variables or constants
        // arg_type { 1 : variable, 2 : constant, 3 : expression}

        printf("VAR1: %s\nVAR2: %s\n", $1, $3);
        int arg_type = find_var($1, curr_scope, &var_reg, &var_scope, var_type);
        printf("1st arg:%s\narg_type: %d\nvar_type: %s\nvar_reg: %d\n", $1, arg_type, var_type, var_reg);

        int arg_type2 = find_var($3, curr_scope, &var_reg2, &var_scope2, var_type2);
        printf("2nd arg:%s\narg_type: %d\nvar_type: %s\nvar_reg: %d\n", $3, arg_type2, var_type2, var_reg2);

        // Send all information to function which produces Jasmine code
        // void process_arithmetic(char* operation, char* left_op, int left_reg, int left_scope, char* left_type, int left_arg_type, char* right_op, int right_reg, int right_scope, char* right_type, char* operator, int right_arg_type, char* last_expr_type) {
        process_arithmetic($2, $1, var_reg, var_scope, var_type, arg_type, $3, var_reg2, var_scope2, var_type2, arg_type2, last_expr_type);
    }
;

multiplicative_expression
	: cast_expression
	| multiplicative_expression arithmetic_operator_high cast_expression {
        sprintf($$, "%s %s %s", $1, $2, $3);
        int var_scope, var_scope2;
        int var_reg, var_reg2;
        char var_type[32] = {0};
        char var_type2[32] = {0};
        if(!last_expr_type) {
            last_expr_type = (char*)malloc(128);
        }
        
        // check whether the arguments of multiplication are variables or constants
        // arg_type { 1 : variable, 2 : constant, 3 : expression}

        printf("VAR1: %s\nVAR2: %s\n", $1, $3);
        int arg_type = find_var($1, curr_scope, &var_reg, &var_scope, var_type);
        printf("1st arg:%s\narg_type: %d\nvar_type: %s\nvar_reg: %d\n", $1, arg_type, var_type, var_reg);

        int arg_type2 = find_var($3, curr_scope, &var_reg2, &var_scope2, var_type2);
        printf("2nd arg:%s\narg_type: %d\nvar_type: %s\nvar_reg: %d\n", $3, arg_type2, var_type2, var_reg2);

        // Send all information to function which produces Jasmine code
        // void process_arithmetic(char* operation, char* left_op, int left_reg, int left_scope, char* left_type, int left_arg_type, char* right_op, int right_reg, int right_scope, char* right_type, char* operator, int right_arg_type, char* last_expr_type) {
        process_arithmetic($2, $1, var_reg, var_scope, var_type, arg_type, $3, var_reg2, var_scope2, var_type2, arg_type2, last_expr_type);

    }
;

/*
arithmetic_expression
    : arithmetic_expression arithmetic_operator unary_expression {
        // CALL ARITHMETIC FUNCTION

    }
    | unary_expression {
        strcpy($$, $1);
    }
;
*/

relational_operator
    : MT
    | LT
    | MTE
    | LTE
    | EQ
    | NE
;

unary_expression
	: postfix_expression {
        strcpy($$, $1);
    }
	| INC unary_expression
	| DEC unary_expression
	| unary_operator cast_expression
;

cast_expression
    : unary_expression {
        strcpy($$, $1);
    }
    | LB type RB cast_expression
;

postfix_expression
	: primary_expression {
        strcpy($$, $1);
    }
	| postfix_expression LB RB {
        //printf("FUNCTION\n");
        if(semantic_error) {
            strcpy(strstr(error_msg, "variable"), "function ");
            strcat(error_msg, error_cause_name);
        }
    }
	| postfix_expression LB argument_expression_list RB {
        if(semantic_error) {
            strcpy(strstr(error_msg, "variable"), "function ");
            strcat(error_msg, error_cause_name);
        }
    }
	| postfix_expression INC
	| postfix_expression DEC
;

argument_expression_list
	: assignment_expression
	| argument_expression_list COMMA assignment_expression
;

arithmetic_operator_low
    : ADD {
        strcpy($$, "+");
    }
    | SUB {
        strcpy($$, "-");
    }
;

arithmetic_operator_high
    : MUL {
        strcpy($$, "*");
    }
    | DIV {
        strcpy($$, "/");
    }
    | MOD {
        strcpy($$, "%");
    }
;

assignment_operator
	: ASGN {
        strcpy($$, "=");
    }
	| ADDASGN {
        strcpy($$, "+=");
    }
	| SUBASGN {
        strcpy($$, "-=");
    }
	| MULASGN {
        strcpy($$, "*=");
    }
	| DIVASGN {
        strcpy($$, "/=");
    }
	| MODASGN {
        strcpy($$, "%=");
    }
;

selection_statement
    : IF LB expression RB compound_stat ELSE compound_stat
    | IF LB expression RB compound_stat
;

iteration_statement
    : WHILE LB expression RB compound_stat 
    | FOR LB declaration expression_stat expression RB
;

/* actions can be taken when meet the token or rule */
type
    : INT { strcpy($$, "int"); }
    | FLOAT { strcpy($$, "float"); }
    | BOOL { strcpy($$, "bool"); }
    | STRING { strcpy($$, "string"); }
    | VOID { strcpy($$, "void"); }
;

id_expression
    : ID { strcpy($$, yytext); }
;

%%

/* C code section */
int main(int argc, char** argv)
{
    write_to_file(".class public compiler_hw3\n.super java/lang/Object\n");

    create_symbol();
    yylineno = 0;

    int syn_error = yyparse();
    if(!syn_error) {
        //dump_symbol(true);
        //printf("\n\nTotal lines: %d \n",yylineno);
    }
    //free_func_list();
    return 0;
}

void yyerror(char *s)
{
    // if semantic error is present, we want to display it before the syntax
    // error stops execution
    if(semantic_error) {
        printf("%d: %s\n", yylineno+1, buf); 
        printf("\n|-----------------------------------------------|\n");
        printf("| Error found in line %d: %s\n", yylineno+1, buf);
        printf("| %s", error_msg);
        printf("\n|-----------------------------------------------|\n\n");
    }
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno+1, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
}

void create_symbol() {
    // Create the symbol table
    for(int i = 0; i < 10; i++) {
        symbol_table[i] = (node_t*)malloc(sizeof(node_t));
        symbol_table[i]->next = NULL;
    }
}

void insert_symbol(char* dtype, char* name, char* etype, int scope) { 
    node_t* new_node = (node_t* )malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->f_decl = false;
    new_node->scope_level = scope;
    strcpy(new_node->name, name);
    strcpy(new_node->entry_type, etype);
    strcpy(new_node->data_type, dtype);
    strcpy(new_node->formal_param, "");
    
    // Find the highest taken register r, so that we can put variable in r+1
    if(((strcmp(etype, "variable") == 0) || (strcmp(etype, "parameter") == 0)) && scope != 0) {
        new_node->reg_id = find_highest_reg(scope);
    }
    else {
        new_node->reg_id = -1;
    }

    // printf("ASSIGN %s REG %d\n", name, new_node->reg_id);

    if(strcmp(etype, "parameter") == 0) {
        // is a parameter
        if(params) {
            strcat(params, ", ");
        }
        else {
            params = (char*)malloc(64);
            memset(params, 0, 64);
        }
        strcat(params, dtype);
    } 
    if(strcmp(etype, "function") == 0) {
        if(params) {
            strcpy(new_node->formal_param, params);
            free(params);
            params = NULL;
        }
    }
    if(strcmp(etype, "function_decl") == 0) {
        strcpy(new_node->entry_type, "function");
        if(params) {
            strcpy(new_node->formal_param, params);
            free(params);
            params = NULL;
        }
        new_node->f_decl = true;
    }

    TRAVERSE_LIST(scope) {
        if(it->next == NULL) {
            if(strcmp(it->name, name) == 0) {
                // redeclaration
                set_err_msg(false, true, name);
                strcpy(error_msg, "Redeclared ");
                strcat(error_msg, it->entry_type);
                strcat(error_msg, " ");
                strcat(error_msg, it->name);
                // if(it->f_decl == true) {
                //     continue;
                // }
                if(!it->f_decl) {
                    semantic_error = true;
                    return;
                }
            }
            it->next = new_node;
            break;
        }
    }
    curr_node = new_node;
    parsing_func = false;
}

int lookup_symbol(char* name, int scope) {
    for(int i = scope; i >= 0; i--) {
        TRAVERSE_LIST(i) {  
            if(strcmp(it->name, name) == 0) {
                check_undeclared = false;
                return 0;
            }
        }
    }
        semantic_error = true;
        set_err_msg(false, true, name);
}

int find_highest_reg(int scope) {
    int curr_highest = 0;
    for(int i = scope; i >= 1; i--) {
        // because head is not a true node of the table (just there for reference)
        // we don't want to traverse it. So we start from the node after it.
        TRAVERSE_LIST_AFTER_HEAD(i) {
            if(it->reg_id > curr_highest) {
                curr_highest = it->reg_id;
            }
            else {
                curr_highest++;
            }
        }
    }
    return curr_highest;
}

int find_var_reg(char* name, int scope) {
    TRAVERSE_SCOPE_AFTER_HEAD(scope) {
        if(strcmp(name, it->name) == 0) {
            return it->reg_id;
        }
    }
    return -1;
}

int find_var(char* name, int scope, int* req_reg, int* req_scope, char* req_type) {
    *req_scope = -1;
    *req_reg = -1;
    for(int i = scope; i >= 0; i--) {
        // because head is not a true node of the table (just there for reference)
        // we don't want to traverse it. So we start from the node after it.
        TRAVERSE_LIST_AFTER_HEAD(i) {
            if(strcmp(name, it->name) == 0) {
                *req_scope = it->scope_level;
                *req_reg = it->reg_id;
                strcpy(req_type, it->data_type);
                // Is a variable
                return 1;
            }
        }
    }

    int is_float = 0;
    // Get the type of the constant
    for(int i = 0; i < strlen(name); i++) {
        if(((name[i] >= 48) && (name[i] <= 57)) || (name[i] == 45)) {
            // Current char is a number
            continue;
        }
        else if(name[i] == 46) {
            // Has a '.', is a float
            is_float = 1;
        }
        else {
            // Is an expression
            // Insert last expression type
            strcpy(req_type, last_expr_type);
            return 3;
        }
    }
    if(is_float) {
        strcpy(req_type, "float");
    }
    else {
        strcpy(req_type, "int");
    }
    return 2;
}

void dump_symbol(bool last_print) {

    if(symbol_table[curr_scope]->next == NULL) {
        return;
    }
    int table_index = 0;
    if(!last_print) {
        printf("\n");
    }
    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");


    TRAVERSE_LIST(curr_scope) {
        // since the first node will be empty, it is skipped
        if(it == symbol_table[curr_scope]) {
            continue;
        }
        if(it->f_decl) {
            continue;
        }
        printf("\n%-10d%-10s%-12s%-10s%-10d%s",
            table_index++, it->name, it->entry_type, it->data_type, it->scope_level, it->formal_param);
    }
    printf("\n");

    node_t* tmp = symbol_table[curr_scope]->next;
    node_t* tmp_prev = NULL;

    while(tmp) {
        tmp_prev = tmp;
        tmp = tmp->next;
        free(tmp_prev);
    }

    // reset the table
    symbol_table[curr_scope]->next = NULL;
}

void set_err_msg(bool is_redeclare, bool is_function_error, char* name) {
    memset(error_cause_name, '\0', sizeof(error_cause_name));
    memset(error_msg, 0, 128);
    strcpy(error_msg, "Undeclared ");
    strcat(error_msg, "variable ");
    strcpy(error_cause_name, name);
    
}

void erase_table_scope(int scope) {
    node_t* tmp = symbol_table[scope]->next;
    node_t* tmp_prev = NULL;

    while(tmp) {
        tmp_prev = tmp;
        tmp = tmp->next;
        free(tmp_prev);
    }
    symbol_table[scope]->next = NULL;
}