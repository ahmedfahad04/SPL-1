#include <stdio.h>
#include "shell.h"


void eventLoopWithColors(char * args){

    char * colorCode;
    // if(strcmp(args, "yel")) code = BG_YEL;
    // else 
    colorCode = "\u001b[48;5;230m";
    // colorCode = colorManager();
    
    if(colorCode != NULL) printf("%s", colorCode);

    eventLoop(colorCode);

}

void eventLoop(char * colorFlag){

   // printf("SURE?\n");
    fprintf(stdout, "\e[1;1H\e[2J");

    char *commandLine, **tokens, **filtered_tokens;

    
    do
    {
        // ==> need to remove redundant prompt input
        commandLine = take_user_input(colorFlag);
        tokens = str_tokenize(commandLine, ' ');
        filtered_tokens = removeWhiteSpace(tokens);

        // this is a temporary block to exit the loop
        // in final outcome the command will send a termination code
        // for specific command
        if (strcmp(tokens[0], "exit"))
        {
            puts(RESET);
            fprintf(stdout, "\e[1;1H\e[2J");
            exit(EXIT_FAILURE);
        }

        // this if block is used to clear the console
        if (strcmp(tokens[0], "clear") || strcmp(tokens[0], "bgclr"))
            fprintf(stdout, "\e[1;1H\e[2J"); // ansi code to clear the console
        
        // printf("%s\n", commandLine);
        execute(filtered_tokens);

        free(tokens);
        free(filtered_tokens);
        free(commandLine);    
        

    } while (1);

}