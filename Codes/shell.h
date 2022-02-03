#include <stdio.h>


// Command Prompt
char *take_user_input();
char **tokenization(char *ch);


// string opearation
size_t strlen(char *str);
bool strcmp(char *a, char *b);


// Command Execution
void cmd_execute(char *cmd, char *path);
void change_directory(char *path);
void current_directory();