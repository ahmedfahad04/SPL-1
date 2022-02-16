#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024


// Command Prompt
void prompt();
char *take_user_input();
char **str_tokenize(char *ch, char sep);
void sig_handler(int signum);


// string opearation
size_t strlen(const char *str);
bool strcmp(const char *a, const char *b);
char* strcpy(const char *b);
char* strchr(const char *a, const char ch);
char* strcatt(const char *with, const char *str);
char* strreplace(const char *info, const char *with, const char *str);
bool strcontain(const char *data, const char *substr);
char **removeWhiteSpace(char **raw_data);



// Command Execution
void cmd_execute(char **args);
void change_directory(char *path);
char* current_directory();
char* hostName();
char* userName();
void launch_nano();
void execute(char **args);
bool isBuiltInCmd(char *cmd);
char *getCurrentDirectory();