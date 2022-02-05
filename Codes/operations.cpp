#include <stdio.h>
#include <stdlib.h>

size_t strlen(char *str)
{

    size_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    return len;
}

bool strcmp(char *a, char *b)
{

    if (strlen(a) != strlen(b))
        return false;
    else
    {

        while (*a)
        {

            if (*a != *b)
                return false;
            a++;
            b++;
        }

        return true;
    }
}

char *strcpy(char *from)
{
    char *to = (char *)malloc(sizeof(char) * 1024);

    int i;
    for (i = 0; i < strlen(from); i++)
        to[i] = from[i];

    from[i] = '\0';

    return to;
}

char *strcatt(char *with, char *str)
{
    char ans[2000];
    int i = 0;

    while (*with != '\0')
    {
        ans[i++] = *with++;
    }

    while (*str != '\0')
    {
        ans[i++] = *str++;
    }

    ans[i] = '\0';

    char *res = ans; // always try to declare *res -> this variable where you need it, don't declare at top. It might results in wrong answer.

    return res;
}