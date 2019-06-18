void write_to_file(char* data);
void process_function_definition(char* return_type, char* func_name, char* arg_types);
void type_map(char* type, char* dest);
void process_variable(char* name, char* value, char* type, int scope, int reg);
void process_arithmetic(char* operation, char* left_op, int left_reg, int left_scope, char* left_type, int left_arg_type, char* right_op, int right_reg, int right_scope, char* right_type, int right_arg_type, char* last_expr_type);
void generate_arithmetic_var_code(char* name, char* t_type, char* right_op_type, int a_type, int reg, int scope, char* operation);
void generate_arithmetic_op_code(char* operation, char* left_type, char* right_type);