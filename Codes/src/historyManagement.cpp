#include <cstdio>
#include <dirent.h>
#include <stdlib.h>
#include <math.h>
#include "shell.h"

char *myTilde = strcatt("/home/", userName());
char *historyFileName = strcatt(myTilde, "/.slsh_history");

int historySerialLocator()
{
    if (access(historyFileName, F_OK) != 0)
    {
        FILE *fp;
        if ((fp = fopen(historyFileName, "w")) == NULL)
        {
            puts("Failed to create History files");
        }
        fclose(fp);
    }
    else
    {

        FILE *fp;
        fp = fopen(historyFileName, "r+");

        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        int serial = 0;

        int line_counter = 0;
        while ((read = getline(&line, &len, fp)) != -1)
        {
            line_counter++;
        }

        fclose(fp);
        return line_counter;
    }
}

void writeHistory(int size, struct history ht[])
{

    FILE *fhist = fopen(historyFileName, "a+");

    for (int i = 0; i < size; i++)
    {
        if (ht[i].cmd[0] == '!')
            continue;
        else
            fprintf(fhist, "%s\n", ht[i].cmd);
    }

    fclose(fhist);
}

char *readHistory(int order)
{

    FILE *fp = fopen(historyFileName, "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int serial = 0;

    if (order == -1)
    {   
        int cnt = 1;
        while ((read = getline(&line, &len, fp)) != -1)
        {
            printf("%d: %s",cnt, line);
            cnt++;
        }
    }
    else
    {
        char *sl = numToStr(order);
        int i = 0;

        int counter = 1;
        while ((read = getline(&line, &len, fp)) != -1)
        {
            if(counter == order)
            {
                return strip(line);
            }
            counter++;
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

void clearHistory(){

    if(remove(historyFileName) == 0){
        puts("History cleared");
    } else {
        puts("History failed to be removed!");
    }

}