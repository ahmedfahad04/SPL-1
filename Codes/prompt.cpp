#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

using namespace std;

#define BUFFER_SIZE 1024

char *take_user_input()
{

    char *buffer, *splitted_words;
    char ch;
    int location = 0, buffer_size = BUFFER_SIZE;

    //dynamically allocate memory to store the user prompt
    buffer = (char *)malloc(sizeof(char) * buffer_size);
    splitted_words = (char *)malloc(sizeof(char) * buffer_size);

    printf("myShell$ ");

    while (1)
    {

        scanf("%c", &ch);

        if ((int)ch == EOF or ch == '\n' or buffer == NULL)
        {
            buffer[location] = '\0';
            break;
        }

        else
        {
            buffer[location] = ch;
        }

        if (location > buffer_size)
        {
            buffer_size += 1024;
            buffer = (char *)realloc(buffer, buffer_size);
            splitted_words = (char *)realloc(buffer, buffer_size);
        }

        location++;
    }

    //splitted_words = splitstr(buffer);
    //return splitted_words;
    return buffer;
}

char **splitstr(char *ch)
{

    char *newstr;
    newstr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    char **words = (char **)malloc(sizeof(char) * BUFFER_SIZE);

    int cnt = 0, k = 0, j = 0;

    for (int i = 0;; i++)
    {
        if (((ch[i] == ' ' && i > 0) || (ch[i] == '\0')) && (ch[i - 1] != ' '))
        {
            cnt++;
            newstr[j] = '\0';
            words[k++] = newstr;

            newstr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
            j = 0;

            if (ch[i] == '\0')
                break;
        }

        else
        {
            newstr[j++] = ch[i];
        }
    }


    return words;
}