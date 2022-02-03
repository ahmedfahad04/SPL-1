#include <stdio.h>
#include <unistd.h>

int cmd_execution(char *cmd)
{
    // temporarily I'll send the pure text
    // in future I'll send the tokenize text for execution
    //cmd_execute(commandLine);

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working dir: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }

    if (chdir("..") != 0)
    {
        printf("Operation Unsuccessful");
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working dir: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }
}
