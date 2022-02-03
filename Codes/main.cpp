#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int main()
{

    char *commandLine;

    do
    {
        commandLine = take_user_input();

        // this is a temporary block to exit the loop
        // in final outcome the command will send a termination code
        // for specific command
        if (strcmp(commandLine, "exit"))
            break;
        else
        {
            printf("%s\n", commandLine);
        }

    } while (1);
}