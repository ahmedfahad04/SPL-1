#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

int main()
{
    fprintf(stdout, "\e[1;1H\e[2J");

    char *commandLine, **tokens, **filtered_tokens;

    do
    {
        commandLine = take_user_input();
        tokens = str_tokenize(commandLine, ' ');
        filtered_tokens = removeWhiteSpace(tokens);

        // this is a temporary block to exit the loop
        // in final outcome the command will send a termination code
        // for specific command
        if (strcmp(tokens[0], "exit"))
            break;

        // this if block is used to clear the console
        if (strcmp(tokens[0], "clear"))
            fprintf(stdout, "\e[1;1H\e[2J"); // ansi code to clear the console

        // printf("%s\n", commandLine);
        execute(filtered_tokens);

        free(tokens);
        free(filtered_tokens);
        free(commandLine);

    } while (1);
}