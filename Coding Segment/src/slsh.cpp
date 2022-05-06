#include <cstdio>
#include <signal.h>
#include <thread>
#include "shell.h"

void restart(int sig)
{
    puts("Start again");
    eventLoop();
}

void eventLoopWithColors(char *cmd, char *type)
{

    char *BGCode, *FGCode;

    if (cmd == NULL)
    {
        // perror("Wrong color code\n");
        return;
    }

    if (strcmp(type, "user") || strcmp(type, "host"))
    {
        FGCode = cmd;
        eventLoop(FGCode, type);
    }

    else
    {
        BGCode = cmd;

        if (BGCode != NULL)
            printf("%s", BGCode);

        eventLoop(BGCode);
    }
}

void eventLoop(char *colorFlag, char *colorType)
{
    fprintf(stdout, "\e[1;1H\e[2J");

    char *commandLine, **tokens, **filtered_tokens;
    commandLine = (char *)malloc(sizeof(char) * 500);

    // history
    struct history ht[1000];
    int historyCounter = 0;
    int historySerial = historySerialLocator() + 1;
    int saveInputFileDescriptor, saveOutputFileDescriptor;

    saveInputFileDescriptor = dup(STDIN_FILENO);
    saveOutputFileDescriptor = dup(STDOUT_FILENO);

    do
    {

        dup2(saveInputFileDescriptor, STDIN_FILENO);
        dup2(saveOutputFileDescriptor, STDOUT_FILENO);

        commandLine = take_user_input(colorFlag, colorType);
        commandLine = strip(commandLine);
        ht[historyCounter].cmd = commandLine;
        ht[historyCounter++].order = historySerial++;

        // ==> control ctrl+C button
        // signal(SIGINT, &restart);

        // checking for pipelined and IO redirected commands
        int flag = 0;
        for (int i = 0; i < strlen(commandLine); i++)
        {
            if (commandLine[i] == '|' or commandLine[i] == '>' or commandLine[i] == '<')
            {
                flag = 1;
                break;
            }
        }

        // ==> will start from here
        if (flag)
        {
            filtered_tokens = str_tokenize(commandLine, '|');
            // filtered_tokens = checkForAliasing(filtered_tokens);

            char *simpleCMD[100];
            int cmdCounter = 0;

            while (*filtered_tokens)
            {
                // filtered_tokens = checkForWildCards(filtered_tokens);
                // puts(*filtered_tokens);
                simpleCMD[cmdCounter++] = *filtered_tokens;
                filtered_tokens++;
            }

            struct ShellCommands command = parse(commandLine);
            executePipelinedCommands(cmdCounter, simpleCMD, command);
        }
        else
        {

            // ==> ----- CAREFUL -----
            if (commandLine[0] == '!')
            {
                commandLine = showParticularHistory(commandLine);
            }
            // ----- CAREFUL -----

            tokens = str_tokenize(commandLine, ' ');
            filtered_tokens = checkForWildCards(tokens);
            filtered_tokens = checkForAliasing(tokens);

            if (strcmp(filtered_tokens[0], "exit"))
            {
                puts(RESET);
                fprintf(stdout, "\e[1;1H\e[2J");
                break;
            }

            // printf("EXE: %s\n", filtered_tokens[0]);
            // printf("LENGTH: %s\n", strlen2(filtered_tokens));
            execute(filtered_tokens);
        }

    } while (1);

    writeHistory(historyCounter, ht);
    return;
}
