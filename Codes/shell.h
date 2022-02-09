#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024


// Command Prompt
void prompt();
char *take_user_input();
char **tokenizations(char *ch);
void sig_handler(int signum);


// string opearation
size_t strlen(char *str);
bool strcmp(char *a, char *b);
char* strcpy(char *b);
char* strchr(char *a, char ch);
char* strcatt(char *with, char *str);
char* strreplace(char *info, char *with, char *str);


// Command Execution
void cmd_execute(char **args);
void change_directory(char *path);
char* current_directory();
char* hostname();
void launch_nano();
void execute(char **args);
bool isBuiltInCmd(char *cmd);