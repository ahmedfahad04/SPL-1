#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "shell.h"

int main()
{
    fprintf(stdout, "\e[1;1H\e[2J");


    char *commandLine, **tokens;

    do
    {
        commandLine = take_user_input();
        tokens = tokenizations(commandLine);

        // this is a temporary block to exit the loop
        // in final outcome the command will send a termination code
        // for specific command
        if (strcmp(tokens[0], "exit"))
            break;

        // this if block is used to clear the console
        if (strcmp(tokens[0], "clear"))
            fprintf(stdout, "\e[1;1H\e[2J"); // ansi code to clear the console

        
       
        //printf("%s\n", commandLine);
        cmd_execute(tokens);            
        

        // free(tokens);
        // free(commandLine);

    } while (1);
}