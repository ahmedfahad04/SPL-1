#include <stdio.h>
#include "shell.h"


void eventLoopWithColors(char * args){

    char * colorCode;
    // if(strcmp(args, "yel")) code = BG_YEL;
    // else 

    // colorCode = "\u001b[48;5;230m";
    colorCode = args;
    //char * tmp = showCode();
    
    if(colorCode != NULL) printf("%s", colorCode);

    eventLoop(colorCode);

}

void eventLoop(char * colorFlag){

    
    fprintf(stdout, "\e[1;1H\e[2J");

    char *commandLine, **tokens, **filtered_tokens;

    
    do
    {
        //printf("SURE?\n");
        // ==> need to remove redundant prompt input
        commandLine = take_user_input(colorFlag);
        tokens = str_tokenize(commandLine, ' ');
        filtered_tokens = removeWhiteSpace(tokens);

        // this is a temporary block to exit the loop
        // in final outcome the command will send a termination code
        // for specific command
        if (strcmp(filtered_tokens[0], "exit"))
        {
            puts(RESET);
            fprintf(stdout, "\e[1;1H\e[2J");
            exit(EXIT_FAILURE);
        }

        // this if block is used to clear the console
        if (strcmp(filtered_tokens[0], "clear"))
            fprintf(stdout, "\e[1;1H\e[2J"); // ansi code to clear the console
        
        // printf("%s\n", commandLine);
        
        printf("%s %s %s\n", filtered_tokens[0], filtered_tokens[1], filtered_tokens[2]);
        execute(filtered_tokens);

        free(tokens);
        free(filtered_tokens);
        free(commandLine);    
        

    } while (1);

}