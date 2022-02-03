#include <stdio.h>
#include <unistd.h>

void cmd_execute(char *cmd)
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
        //return 1;
    }

    if (chdir(cmd) != 0) printf("csh: cd: %s: No such file or directory\n", cmd);
    
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
