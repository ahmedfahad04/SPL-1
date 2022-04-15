#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

void frequencyCalculator(char *command, FILE *save)
{
    FILE *fp;
    fp = fopen(".history", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int counter = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        char **chunks = (char **)malloc(sizeof(char) * 100);
        char **simplecmd = (char **)malloc(sizeof(char) * 100);

        chunks = str_tokenize(line, ':');
        simplecmd = str_tokenize(chunks[1], ' ');

        // puts(strip(simplecmd[0]));
        // puts(command);

        if (strcmp(strcpy(command), strip(simplecmd[0])))
        {
            counter++;
        }
    }

    fclose(fp);

    fprintf(save, "%d %s\n", counter, strcpy(command));
}

bool count(char *data[], char *info, int size)
{

    for (int i = 0; i < size; i++)
    {
        if (strcmp(data[i], info))
            return true;
    }

    return false;
}

void assembleFreqOutput()
{

    FILE *f1;

    if ((f1 = fopen(".autoCmd", "r")) == NULL)
    {
        puts("file not found");
    }

    struct cmdFreq freqls[1000];
    int index = 0;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int counter = 0;
   

    while ((read = getline(&line, &len, f1)) != -1)
    {
        char **chunks = (char **)malloc(sizeof(char) * 100);
        char **simplecmd = (char **)malloc(sizeof(char) * 100);

        chunks = str_tokenize(line, ' ');
        simplecmd = str_tokenize(chunks[1], ' ');

        if (atoi(chunks[0]) > 0)
        {
            freqls[index].cmd = simplecmd[0];
            freqls[index++].freq = atoi(chunks[0]);
        }
    }

    fclose(f1);

    FILE *fwr;

    if ((fwr = fopen(".cmdFrequency", "w+")) == NULL)
    {
        puts("File not found");
    }


    for (int i = 0; i < index; i++)
    {

        fprintf(fwr, "%d %s\n", freqls[i].freq, freqls[i].cmd);
        //printf("%d %s\n", freqls[i].freq, freqls[i].cmd);
    }

    fclose(fwr);
}

bool generateAutoCommand(char * cmd){

    FILE *fp;

    if((fp = fopen(".cmdFrequency", "r+")) == NULL){
        puts("FILE not found");
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int counter = 0;
   

    while ((read = getline(&line, &len, fp)) != -1)
    {
        char **chunks = (char **)malloc(sizeof(char) * 100);
        chunks = str_tokenize(line, ' ');

        if(strcmp( strcpy(cmd), strip(chunks[1]) )) return true;
    }

    fclose(fp);

    return false;
}


