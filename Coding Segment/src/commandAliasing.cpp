#include <cstdio>
#include <stdlib.h>
#include "shell.h"
#define BUFFER_SIZE 1024

// char *myTilde2 = strcatt("/home/", userName());
// char *aliasfp = strcatt(myTilde2, "/.slshAlias");

// ==> will work on that
char *aliasfp = "/home/ahmedfahad/.slsh_alias";

void setAlias(char *cmd, char *alias)
{
    // error checking....
    // ==> also group command aliasing
    // need to check if user given name already exists or not
    // first create the file if it's not been created
    if (access(aliasfp, F_OK) != 0)
    {
        puts("C");
        FILE *fp3;
        if ((fp3 = fopen(aliasfp, "w+")) == NULL)
        {
            puts("Failed to create aliasfp files");
        }
        fclose(fp3);
    }

    FILE *f1;

    if ((f1 = fopen(aliasfp, "a+")) == NULL)
    {
        puts("Failed to open aliasfp file");
    }

    fprintf(f1, "%s %s\n", cmd, alias);
    fclose(f1);
}

void aliasCommands(char **words)
{
    char **refactor = (char **)malloc(sizeof(char) * 500);

    if (strlen2(words) == 1)
    {

        char s;
  

        FILE *fp3;
        if ((fp3 = fopen(aliasfp, "r")) == NULL)
        {
            puts("Failed to create aliasfp files");
        }

        while ((s = fgetc(fp3)) != EOF)
        {
            printf("%c", s);
        }
        fclose(fp3);

        return;
    }

    if (strcmp(words[0], "alias"))
    {
        refactor = str_tokenize(words[1], '=');
        puts(refactor[0]); // ls
        puts(refactor[1]); // list
        setAlias(refactor[0], refactor[1]);
    }
}

char **checkForAliasing(char **data)
{

    if (access(aliasfp, F_OK) != 0)
    {
        FILE *fp3;
        if ((fp3 = fopen(aliasfp, "w+")) == NULL)
        {
            puts("Failed to create aliasfp files");
        }
        fclose(fp3);
    }

    char *newargs[500];
    char **chunks = (char **)malloc(sizeof(char) * 500);
    int id = 0;

    while (*data)
    {

        if (id == 0)
        {
            FILE *f2;
            f2 = fopen(aliasfp, "r");

            char *line = NULL;
            size_t len = 0;
            ssize_t read;
            int flag = 1;
            // printf("PReV, iDATA: %s----flag: %d\n", *data, flag);

            while ((read = getline(&line, &len, f2)) != -1)
            {
                chunks = str_tokenize(line, ' ');

                if (strcmp(chunks[1], *data))
                {
                    newargs[id++] = strip(chunks[0]);
                    flag = 0;
                }
                // puts(chunks[0]);
                // puts(chunks[1]);
                // printf("DATA: %s----flag: %d\n", *data, flag);
            }

            // free(chunks);

            if (flag)
                newargs[id++] = *data;
            fclose(f2);
        }

        else
        {
            newargs[id++] = *data;
        }

        // printf("--DATA: %s\n", newargs[id-1]);

        data++;
    }

    // free(newargs);
    newargs[id] = NULL;
    char **ans = newargs;
    return ans;
}
