void execute_program(char* userinput[]);
char *get_command(char* command);
bool file_exist(char* file_path);
char *string_concat(char* path, char* command);
char **get_input(char *input);
pid_t run_command(char* command, char** command_list);
void store_history(char* command);
void history();
void control_c();
void control_z();
bool is_redirect(char** command_list);
char** get_redirect_commands(char** command_list);
void control_c_handler(int dummy);
void control_z_handler(int dummy);

