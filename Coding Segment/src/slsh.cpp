#include <stdio.h>
#include "shell.h"

void eventLoopWithColors(char *args, char *type)
{

    char *BGCode, *FGCode;

    if (args == NULL)
    {
        // perror("Wrong color code\n");
        return;
    }

    if (strcmp(type, "user") || strcmp(type, "host"))
    {
        FGCode = args;
        eventLoop(FGCode, type);
    }

    else
    {
        BGCode = args;

        if (BGCode != NULL)
            printf("%s", BGCode);

        eventLoop(BGCode);
    }
}

void eventLoop(char *colorFlag, char *colorType)
{

    fprintf(stdout, "\e[1;1H\e[2J");

    char *commandLine, **tokens, **filtered_tokens;

    do
    {
        //  ==> need to remove redundant prompt input
        commandLine = take_user_input(colorFlag, colorType);

        // checking for pipelined commands
        int flag = 0;
        for (int i = 0; i < strlen(commandLine); i++)
        {
            if (commandLine[i] == '|')
            {
                flag = 1;
                break;
            }
        }

        if (flag)
        {
            filtered_tokens = str_tokenize(commandLine, '|');

            char *simpleCMD[100];
            int size = 0;

            while (*filtered_tokens)
            {
                // filtered_tokens = checkForWildCards(filtered_tokens);
                simpleCMD[size++] = *filtered_tokens;
                filtered_tokens++;
            }

            executePipelinedCommands(size, simpleCMD);
        }
        else
        {
            tokens = str_tokenize(commandLine, ' ');
            filtered_tokens = removeWhiteSpace(tokens);
            filtered_tokens = checkForWildCards(filtered_tokens);
            // filtered_tokens = checkForAliasing(filtered_tokens);

            // this is a temporary block to exit the loop
            // in final outcome the command will send a termination code
            // for specific command
            if (strcmp(filtered_tokens[0], "exit"))
            {
                puts(RESET);
                fprintf(stdout, "\e[1;1H\e[2J");
                exit(EXIT_FAILURE);
            }

            // printf("%s\n", commandLine);
            execute(filtered_tokens);
        }

    } while (1);
}