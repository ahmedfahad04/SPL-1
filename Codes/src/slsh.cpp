#include <cstdio>
#include <signal.h>
#include <thread>
#include "shell.h"


int processPipelinedCommand(char *command)
{

    char **filtered_tokens;

    int flag = 0;

    for (int i = 0; i < strlen(command); i++)
    {
        if (command[i] == '|' or command[i] == '>' or command[i] == '<')
        {
            flag = 1;
            break;
        }
    }

    if (flag)
    {
        filtered_tokens = strTokenize(command, '|');

        char *simpleCMD[100];
        int cmdCounter = 0;

        while (*filtered_tokens)
        {
            simpleCMD[cmdCounter++] = *filtered_tokens;
            filtered_tokens++;
        }

        struct ShellCommands parsedCommand = parse(command);
        executePipelinedCommands(cmdCounter, simpleCMD, parsedCommand);
        return 1;
    }

    return 0;
}

int porcessSingleCommand(char *command)
{

    if (strlen(command) == 0)
        return 1;

    char **tokens, **filtered_tokens;

    if (command[0] == '!')
    {
        command = showParticularHistory(command);
    }

    tokens = strTokenize(command, ' ');
    filtered_tokens = checkForAliasing(tokens);
    // filtered_tokens = checkForWildCards(filtered_tokens);

    if (strcmp(filtered_tokens[0], "exit"))
    {
        puts(RESET);
        fprintf(stdout, "\e[1;1H\e[2J");
        return 0;
    }

    // printf("%s\n", filtered_tokens[0]);
    // printf("LENGTH: %d\n", strlen2(filtered_tokens));
    execute(filtered_tokens);
    return 1;
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
    intro();

    char *commandLine, **tokens, **filtered_tokens;
    commandLine = (char *)malloc(sizeof(char) * 500);

    // history
    struct history ht[1000];
    int historyCounter = 0;
    int historySerial = historySerialLocator() + 1;
    int saveInputFileDescriptor, saveOutputFileDescriptor, status;

    saveInputFileDescriptor = dup(STDIN_FILENO);
    saveOutputFileDescriptor = dup(STDOUT_FILENO);

    do
    {

        dup2(saveInputFileDescriptor, STDIN_FILENO);
        dup2(saveOutputFileDescriptor, STDOUT_FILENO);

        commandLine = takeUserInput(colorFlag, colorType);
        commandLine = strip(commandLine);

        if (strlen(commandLine) != 0)
        {
            ht[historyCounter].cmd = commandLine;
            ht[historyCounter++].order = historySerial++;
        }

        // execute commands
        status = processPipelinedCommand(commandLine);

        if (status == 0)
            status = porcessSingleCommand(commandLine);

    } while (status != 0);

    ht[historyCounter].cmd = "exit";
    ht[historyCounter++].order = historySerial++;

    writeHistory(historyCounter, ht);
    return;
}
