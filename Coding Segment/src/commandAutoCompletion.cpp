#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

void updateCmdFrequency()
{

    FILE *currFrq, *temp;
    struct cmdFreq unMatchedCMD[1000];
    char *distinctCMD[1000];
    int distinctCounter[1000] = {0};
    int id = 0;

    if ((currFrq = fopen(".tempfqr", "r")) == NULL)
    {
        puts("Failed to Open tmpFreqency file");
    }

    if ((temp = fopen(".cmdFrequency", "w")) == NULL)
    {
        puts("Failed to Open Cmd Freqency file");
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read1;
    int newCounter = 0;
    int dsize = 0;
    char **chunks;

    // let's fetch the distinct command
    while ((read1 = getline(&line, &len, currFrq)) != -1)
    {
        chunks = (char **)malloc(sizeof(char) * 100);
        chunks = str_tokenize(line, ' ');

        int isExist = count(distinctCMD, chunks[1], dsize);

        if (isExist == -1)
        {
            distinctCMD[dsize] = chunks[1];
            distinctCounter[dsize++] = atoi(chunks[0]);
        }
        else
        {
            distinctCounter[isExist] += atoi(chunks[0]);
        }
    }

    // test run
    for (int i = 0; i < dsize; i++)
    {

        // printf("Distinct CMD: %s, CNT: %d\n", distinctCMD[i], distinctCounter[i]);

        len = 0;
        *line = NULL;
        ssize_t read;

        // first read the cmd feq file to get the current freq of specific command "CMD"
        while ((read = getline(&line, &len, currFrq)) != -1)
        {
            chunks = (char **)malloc(sizeof(char) * 100);
            chunks = str_tokenize(line, ' ');

            // puts(chunks[1]);
            // puts(chunks[0]);

            if (strcmp(chunks[1], strcpy(distinctCMD[i])))
            {
                int cnt = atoi(chunks[0]);
                distinctCounter[i] += cnt;
            }
            else // no need
            {
                unMatchedCMD[id].cmd = chunks[1];
                unMatchedCMD[id++].freq = atoi(chunks[0]);
            }
        }

        if (distinctCounter[i])
        {
            fprintf(temp, "%d %s\n", distinctCounter[i], strcpy(distinctCMD[i]));
        }
    }

    // also add the new freq
    // newCounter += newFreq;

    // temp close both file
    fclose(currFrq);
    fclose(temp);

    return;
}

void frequencyCalculator(char *command, FILE *save)
{

    FILE *fp;

    // ==> becareful about file path name
    if((fp = fopen("/home/ahmedfahad/.bash_history", "r")) == NULL){
        printf("Failed to open history file");
    }


    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int counter = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        char **chunks = (char **)malloc(sizeof(char) * 100);
        char *simplecmd = (char *)malloc(sizeof(char) * 100);

        chunks = str_tokenize(line, ' ');
        simplecmd = chunks[0];
        // will handle case of ./run -> commands


        // puts(strip(simplecmd[0]));
        // printf(">> %s\n", command);

        if (strcmp(strcpy(command), strip(simplecmd)))
        {
            counter++;
        }
    }

    fclose(fp);

    // need to think do we need this counter condition??
    if(counter > 0) fprintf(save, "%d %s\n", counter, strcpy(command));
}

int count(char *data[], char *info, int size)
{

    for (int i = 0; i < size; i++)
    {
        if (strcmp(data[i], info))
            return i;
    }

    return -1;
}

int generateAutoCommand(char *cmd)
{

    FILE *fp;

    if ((fp = fopen(".cmdFrequency", "r+")) == NULL)
    {
        puts("FILE cmd frequency not found");
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int counter = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        char **chunks = (char **)malloc(sizeof(char) * 100);
        chunks = str_tokenize(line, ' ');

        if (strcmp(strcpy(cmd), strip(chunks[1])))
        {
            return atoi(chunks[0]);
        }
    }

    fclose(fp);

    return 0;
}

void mergeAndExecute(char *command, char **data)
{


    puts("INSIDE MERGE");
    puts(command);

    char *newargs[500];
    int id = 0;

    while (*data)
    {
        if (id == 0)
        {
            newargs[id++] = command;
        }
        else
        {
            newargs[id++] = *data;
        }

        puts(*data);
        data++;
    }

    // free(newargs);
    newargs[id] = NULL;

    execute(newargs);
}



