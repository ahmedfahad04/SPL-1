#include <stdio.h>
#include <stdlib.h>

int cnt = 0;

char **readCMDOutput(char *cmd)
{
    FILE *p;
    int ch, buffer_size = 100024;
    size_t length = 0;
    ssize_t read;

    char *line = (char *) malloc (sizeof(char)*1024);
    char **wordArr = (char **)malloc(sizeof(char) * buffer_size);

    p = popen(cmd, "r"); /* Unix */

    if (p == NULL)
    {
        puts("Unable to open process");
    }

    int i = 0;
    while ((read = getline(&line, &length, p)) != -1)
    {
        //printf("%s", line);
        wordArr[i++] = line;
        line = (char *) malloc (sizeof(char)*1024);
    }

    wordArr[i] = NULL;
    cnt = i;
    pclose(p);

    return wordArr;
}

int main()
{
    // char command[1024];
    // printf("Enter your commmand: ");
    // scanf("%s", command);

    char **ans = readCMDOutput("ls /usr/include");

    char **temp = ans; // temp is a pointer to a *pointer*, not a pointer to a *char*

    while (*temp)
    {
        printf("%s", *temp);
        temp++;
    }

    printf("Word Size: %d", cnt);
}