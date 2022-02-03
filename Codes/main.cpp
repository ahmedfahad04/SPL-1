#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"


int main()
{

    char *commandLine, **tokens;

    do
    {
        commandLine = take_user_input();
        tokens = splitstr(commandLine);

        // this is a temporary block to exit the loop
        // in final outcome the command will send a termination code
        // for specific command
        if (strcmp(commandLine, "exit"))
            break;

        // this if block is used to clear the console
        if (strcmp(commandLine, "clear"))
        {
            fprintf(stdout, "\e[1;1H\e[2J");
        }

        else
        {
            printf("%s\n", commandLine);

            // display the words given in the prompt
            // for(int i=0; i<100; i++){
            //     if(tokens[i] != NULL) printf("%d. %s\n", i+1, tokens[i]);
            // }

            cmd_execute(tokens[1]);
        }

        free(tokens);
        free(commandLine);

    } while (1);
}