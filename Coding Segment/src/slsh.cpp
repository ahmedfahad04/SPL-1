#include <stdio.h>
#include "shell.h"


void eventLoopWithColors(char * code){

    char * colorCode = "\u001b[48;5;146m";
    // char * colorCode = code;
    
    if(colorCode != NULL) printf("%s", colorCode);

    eventLoop(code);

    if(colorCode != NULL) printf("%s", colorCode);

}

void eventLoop(char * colorFlag){

    fprintf(stdout, "\e[1;1H\e[2J");

    char *commandLine, **tokens, **filtered_tokens;

    do
    {

        commandLine = take_user_input(colorFlag);
        tokens = str_tokenize(commandLine, ' ');
        filtered_tokens = removeWhiteSpace(tokens);

        // this is a temporary block to exit the loop
        // in final outcome the command will send a termination code
        // for specific command
        if (strcmp(tokens[0], "exit"))
        {
            break;
        }

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