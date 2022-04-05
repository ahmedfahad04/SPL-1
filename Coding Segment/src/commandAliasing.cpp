#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#define BUFFER_SIZE 1024

void setAlias(char *cmd, char *alias)
{
    // error checking....
    // need to check if user given name already exists or not
    FILE *f1;

    f1 = fopen(".slshAlias", "a");
    fprintf(f1, "%s %s\n", cmd, alias);
    fclose(f1);
}

void aliasCommands(char **words)
{
    char **refactor = (char **)malloc(sizeof(char) * 500);

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

    char **newargs = (char **)malloc(sizeof(char) * 1024);
    char **chunks = (char **)malloc(sizeof(char) * 1024);
    int id = 0;

    while (*data)
    {

        if (id == 0)
        {
            FILE *f2;
            f2 = fopen(".slshAlias", "r");

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
            

            if(flag) newargs[id++] = *data;
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
    return newargs;
}

