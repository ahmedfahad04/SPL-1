#include <stdio.h>
#include <stdlib.h>

size_t strlen(const char *str)
{

    size_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    return len;
}

bool strcmp(const char *a, const char *b)
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

char *strcpy(const char *from)
{
    int len = strlen(from);
    char res[len + 1];

    int i;
    for (i = 0; i < len; i++)
        res[i] = from[i];

    res[i] = '\0';

    char *to = res;
    return to;
}

char *strcatt(const char *with, const char *str)
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

char *strreplace(const char *data, const char *with, const char *str)
{

    char ans[1024];
    int start = -1, end = -1;

    int id = 0, j = 0;
    for (int i = 0; i < strlen(data); i++)
    {

        // cout << "D: " << data[i] << ", W: " << with[j] <<", I: " << i <<endl;

        if (data[i] == with[j])
        {
            if (start == -1)
                start = i;
            j++;
        }

        else if ((data[i] != with[j]) && start != -1)
        {
            end = i;
            break;
        }

        if (start == -1)
        {
            ans[++id] = data[i];
        }
    }

    id--;

    while(*str != '\0'){
        ans[++id] = *str++;
    }

    data += end;
    while(*data != '\0'){
        ans[++id] = *data++;
    }

    ans[++id] = '\0';

    char *res = ans;

    return res;
}