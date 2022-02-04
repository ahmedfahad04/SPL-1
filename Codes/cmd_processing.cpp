#include <stdio.h>
#include <unistd.h>
#include "shell.h"

void cmd_execute(char *cmd, char *args)
{
    // temporarily I'll send the pure text
    // in future I'll send the tokenize text for execution
    //cmd_execute(commandLine);

    current_directory();
    
    if (strcmp(cmd, "chngdir"))
        change_directory(args);

    current_directory();
}

void change_directory(char *path)
{

    if (chdir(path) != 0)
        printf("csh: cd: %s: No such file or directory\n", path);
}

void current_directory()
{

    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working dir: %s\n", cwd);
        
    }
    else
    {
        perror("getcwd() error");
        //return 1;
    }
}
