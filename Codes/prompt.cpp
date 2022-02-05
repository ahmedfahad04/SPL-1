#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
using namespace std;

#define BUFFER_SIZE 1024

void prompt(){

    char *path = current_directory();

    // color coded text (user prompt)
    // printf("mecsh@Dell %s$", path);
    printf("\u001b[1m\u001b[35;1mecsh@mmyShell: %s$\u001b[35;1m\u001b[1m ", path);
}

char *take_user_input()
{
    char *buffer, *splitted_words, *path;
    char ch;
    int location = 0, buffer_size = BUFFER_SIZE;

    //dynamically allocate memory to store the user prompt
    buffer = (char *)malloc(sizeof(char) * buffer_size);
    splitted_words = (char *)malloc(sizeof(char) * buffer_size);

    prompt();
    printf("\u001b[32m");

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

char **tokenizations(char *ch)
{

    char *newstr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    char **raw_words = (char **)malloc(sizeof(char) * BUFFER_SIZE);
    char **words = (char **)malloc(sizeof(char) * BUFFER_SIZE);

    int cnt = 0, k = 0, j = 0;

    // split the string into words based on spaces
    for (int i = 0;; i++)
    {
        if (((ch[i] == ' ' && i > 0) || (ch[i] == '\0') || (ch[i] == '\n')) && (ch[i - 1] != ' '))
        {
            cnt++;
            newstr[j] = '\0';
            raw_words[k++] = newstr;

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

    // removing white spaces from each words
    for(int i=0; i<cnt; i++){

        char *demo = (char *)malloc(sizeof(char) * BUFFER_SIZE);
        int id = 0;

        for(int j=0; j<strlen(raw_words[i]); j++){

            if(raw_words[i][j] != ' ') 
                demo[id++] = raw_words[i][j];
        }

        words[i] = demo;
    }

    return words;
}