#include <stdio.h>


// Command Prompt
void prompt();
char *take_user_input();
char **tokenizations(char *ch);


// string opearation
size_t strlen(char *str);
bool strcmp(char *a, char *b);
char* strcpy(char *b);
char* strchr(char *a, char ch);
char* strcatt(char *with, char *str);

// Command Execution
void cmd_execute(char *cmd, char *path);
void change_directory(char *path);
char* current_directory();
char* hostname();