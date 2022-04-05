#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <math.h>
#include "shell.h"

int historySerialLocator()
{
    if (access(".history", F_OK) != 0)
    {
        FILE *fp;
        fp = fopen(".history", "w");
        fclose(fp);
    }
    else
    {

        FILE *fp;
        fp = fopen(".history", "r+");

        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        int serial = 0;

        while ((read = getline(&line, &len, fp)) != -1)
        {
            char **chunks = (char **)malloc(sizeof(char) * 500);

            chunks = str_tokenize(line, ': ');
            if (strlen(chunks[1]) == 0)
                continue;
            else
            {
                serial = atoi(chunks[0]);
                // printf("SL: %d\n", serial);
            }
        }

        printf("CUR: %d\n", serial);
        fclose(fp);
        return serial;
    }
}

void writeHistory(int size, struct history ht[])
{

    FILE *fhist = fopen(".history", "a+");

    for (int i = 0; i < size; i++)
    {
        if (ht[i].cmd[0] == '!')
            continue;
        else
            fprintf(fhist, "%d: %s\n", ht[i].order, ht[i].cmd);
    }

    fclose(fhist);
}

char *readHistory(int order)
{

    FILE *fp = fopen(".history", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int serial = 0;

    if (order == -1)
    {
        while ((read = getline(&line, &len, fp)) != -1)
        {
            printf("%s", line);
        }
    }
    else
    {
        char *sl = numToStr(order);
        int i = 0;
        while ((read = getline(&line, &len, fp)) != -1)
        {

            char **chunks = (char **)malloc(sizeof(char) * 100);
            chunks = str_tokenize(line, ':');

            if (strcmp(sl, chunks[0]))
            {

                return chunks[1];
            }
        }
    }

    return NULL;
}

char *showParticularHistory(char *input)
{

    int num = 0;
    int len = strlen(input) - 1;

    for (int i = 1; i < strlen(input); i++)
    {
        num += (input[i] - '0') * pow(10, len - i);
    }

    char *ans = readHistory(num);
    return ans;
}