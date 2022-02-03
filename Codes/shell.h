#include <stdio.h>


// Read command 
char *take_user_input();
char **splitstr(char *ch);


// string opearation
size_t strlen(char *str);
bool strcmp(char *a, char *b);


// Command Execution
void cmd_execute(char *cmd);