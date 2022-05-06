#include <cstdio>
#include <stdlib.h>
#include <ctype.h>
#include "shell.h"
using namespace std;


char *userFontColor = FONT_RED, *bgColor = "\u001b[230;5;m", *hostFontColor = FONT_CYN;

void promptWithColors(char *code, char *colorType)
{
    char *path = getCurrentDirectory();
    char *myuser = userName();
    char *myhost = hostName();

    // ==> need to work on manual code input

    if (strcmp(colorType, "user"))
    {
        userFontColor = code;
    }
    else if (strcmp(colorType, "host"))
    {
        hostFontColor = code;
    }
    else
    {
        bgColor = code;
    }

    if (bgColor != NULL)
        printf("%s", bgColor);

    printf("\u001b[1m%s\u001b[1m%s@%s:\u001b[1m%s\u001b[1m%s", userFontColor, myuser, myhost, userFontColor, RESET);

    if (bgColor != NULL)
        printf("%s", bgColor);

    printf("\u001b[1m%s\u001b[1m%s$ \u001b[1m%s\u001b[1m%s", hostFontColor, getCurrentDirectory(), hostFontColor, RESET);

    if (bgColor != NULL)
        printf("%s", bgColor);
}

void prompt()
{
    char *path = getCurrentDirectory();
    char *myuser = userName();
    char *myhost = hostName();

    printf("%s%s@%s:%s%s", userFontColor, myuser, myhost, userFontColor, RESET);
    printf("%s\u001b[1m%s%s$ %s\u001b[1m%s", RESET, hostFontColor, getCurrentDirectory(), hostFontColor, RESET);
}

char *take_user_input(char *C_Code, char *colorType, int fsl, FILE *fp)
{
    char *buffer, *splitted_words, *path;
    char ch;
    int location = 0, buffer_size = BUFFER_SIZE;
    // FILE *fp = fopen(".history", "a+");

    // dynamically allocate memory to store the user prompt
    buffer = (char *)malloc(sizeof(char) * buffer_size);
    splitted_words = (char *)malloc(sizeof(char) * buffer_size);

    if (strlen(C_Code) != 0)
    {
        promptWithColors(C_Code, colorType);
    }
    else
        prompt();

    while (1)
    {
        scanf("%c", &ch);
        if (ch == '\r')
            continue;

        if (location > buffer_size)
        {
            buffer_size += 1024;
            buffer = (char *)realloc(buffer, buffer_size);
            splitted_words = (char *)realloc(buffer, buffer_size);
        }

        if ((int)ch == EOF or ch == '\n' or buffer == NULL)
        {
            // this portion is for taking multiline input delimited by '\'
            int tmploc = location - 1;

            if (buffer[tmploc] == '\\')
            {
                location--;
                printf("> ");
                continue;
            }

            buffer[location] = '\0';
            break;
        }

        buffer[location] = ch;
        location++;
    }

    // splitted_words = splitstr(buffer);
    // return splitted_words;
    return buffer;
}

char **removeWhiteSpace(char **raw_data)
{

    char **words = (char **)malloc(sizeof(char) * BUFFER_SIZE);
    int i = 0;

    // removing white spaces from each words
    for (; raw_data[i]; i++)
    {
        char *demo = (char *)malloc(sizeof(char) * BUFFER_SIZE);
        int id = 0;

        for (int j = 0; j < strlen(raw_data[i]); j++)
        {

            if (raw_data[i][j] != ' ')
                demo[id++] = raw_data[i][j];
        }

        words[i] = demo;
    }

    words[i] = NULL;

    return words;
}

char **str_tokenize(char *ch, char sep)
{

    char *newstr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    char **raw_words = (char **)malloc(sizeof(char) * BUFFER_SIZE);

    int cnt = 0, k = 0, j = 0, qFlag = 0, changed = 0;

    // split the string into words based on delimeters
    for (int i = 0;; i++)
    {
        if (ch[i] == '\"' or ch[i] == '\'')
        {
            newstr[j++] = ch[i];
            if (qFlag == 0) // means starting of a quote
            {
                qFlag = 1;
                continue;
            }

            else // means ending of a quote
            {
                qFlag = 0;
                i++;
            }
        }

        if (!qFlag)
        {
            if (((ch[i] == sep && i > 0) || (ch[i] == '\0') || (ch[i] == '\n')) && (ch[i - 1] != sep))
            {
                cnt++;
                newstr[j] = '\0';
                raw_words[k++] = newstr;
                changed = 1;
                // printf("NEW: %s -> %d\n", newstr, qFlag);

                newstr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
                j = 0;

                if (ch[i] == '\0')
                    break;
            }

            else
            {
                newstr[j++] = ch[i];
            }
            // printf("CH: %c ", ch[i]);
        }

        else
        {
            newstr[j++] = ch[i];
        }
    }   


    raw_words[k] = NULL;
    if (changed == 0)
    {
        raw_words[0] = ch;
        raw_words[1] = NULL;
    }

    return raw_words;
}

char *strip(char *word)
{

    int id = 0;
    char *demo = (char *)malloc(sizeof(char) * 1024);

    int stflag = 0, endflag = 0;

    for (int i = 0; i < strlen(word); i++)
    {

        if (word[i] == ' ' and i == 0)
            continue;
        else if (word[i] == ' ' and i == strlen(word) - 1)
            continue;
        else
            demo[id++] = word[i];
    }

    demo[id] = '\0';

    return demo;
}