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

    while (*str != '\0')
    {
        ans[++id] = *str++;
    }

    data += end;
    while (*data != '\0')
    {
        ans[++id] = *data++;
    }

    ans[++id] = '\0';

    char *res = ans;

    return res;
}

bool strcontain(const char *data, const char *substr)
{

    int j = 0, len = 0, flag = 0;
    for (int i = 0; i < strlen(data); i++)
    {
        if (data[i] == substr[j])
        {
            j++;
            len++;
        }
        else
        {
            if (len == strlen(substr))
            {
                flag = 1;
                break;
            }
            j = 0;
            len = 0;
        }
    }

    if (len == strlen(substr))
        flag = 1;

    return flag;
}

int strsubstr(char *neddle, char *heystack)
{
    int neddle_len = strlen(neddle);
    int heystack_len = strlen(heystack);

    int LPS[neddle_len];

    PieTable(neddle, neddle_len, LPS);
    int i = 0;
    int j = 0;
    while (i < heystack_len)
    {
        if (neddle[j] == heystack[i])
        {
            j++;
            i++;
        }
        if (j == neddle_len)
        {
            return (i - j);
            // j = LPS[j - 1];
        }

        else if (i < heystack_len && neddle[j] != heystack[i])
        {

            if (j != 0)
                j = LPS[j - 1];
            else
                i = i + 1;
        }
    }

    return -1;
}

void PieTable(char *neddle, int neddle_len, int *LPS)
{

    int len = 0;
    LPS[0] = 0;
    int i = 1;
    while (i < neddle_len)
    {
        if (neddle[i] == neddle[len])
        {
            len++;
            LPS[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = LPS[len - 1];
            }
            else
            {
                LPS[i] = 0;
                i++;
            }
        }
    }
}