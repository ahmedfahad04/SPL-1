#include <cstdio>
#include <dirent.h>
#include <stdlib.h>
#include "shell.h"

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
    {
        if (from[i] == '\n')
        {
            res[i] = '\0';
            break;
        }
        else
            res[i] = from[i];
    }

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

int strlen2(char **str)
{
    int len = 0;

    while (*str)
    {
        len++;
        str++;
    }

    return len;
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

int strsubstr(char *neddle, char *heystack)
{
    // Implementation of KMP String Searching Algorithm...
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

char **strsplit(char *find, char *text)
{

    int pos = strsubstr(find, text);
    int len = strlen(find);
    int finalPos = pos + len;

    char **chunk = (char **)malloc(sizeof(char) * 1024);
    char *word = (char *)malloc(sizeof(char) * 1024);
    // char *str2 = (char *)malloc(sizeof(char) * 1024);

    chunk[0] = find;

    int id = 0;

    for (int i = finalPos; i < strlen(text); i++)
    {
        word[id++] = text[i];
    }

    word[id] = '\0';
    chunk[1] = word;

    return chunk;
}

char *numToStr(int num)
{
    char *result = (char *)malloc(sizeof(char) * 1024);

    int i = 0;
    while (num > 0)
    {
        int x = num % 10;
        num /= 10;
        result[i++] = x + '0';
    }

    result[i] = '\0';

    char *str = (char *)malloc(sizeof(char) * 1024);

    int j = 0;
    for (; j < i; j++)
    {
        str[j] = result[i - j - 1];
        // printf("%c..\n", result[j]);
    }

    str[j] = '\0';

    return str;
}

bool wildcardmatching(char *str, char *pat, int slen, int plen)
{
    // ==> need to check null character before . operator
    if (plen == 0)
    {
        if (plen == 0)
            return 0;
        else
            return 1;
    }

    bool table[slen + 1][plen + 1];

    for (int i = 0; i <= slen; i++)
    {
        for (int j = 0; j <= plen; j++)
        {
            table[i][j] = false;
        }
    }

    // initially empty stirng mathches with empty pattern
    table[0][0] = true;

    // only * can match with empty sequence
    for (int j = 1; j <= plen; j++)
    {
        if (pat[j - 1] == '*')
        {
            table[0][j] = table[0][j - 1];
        }
    }

    for (int i = 1; i <= slen; i++)
    {
        for (int j = 1; j <= plen; j++)
        {

            if (pat[j - 1] == '*')
            {
                table[i][j] = table[i - 1][j] || table[i][j - 1];
            }

            else if (pat[j - 1] == '?' || (str[i - 1] == pat[j - 1]))
            {
                table[i][j] = table[i - 1][j - 1];
            }

            else
                table[i][j] = false;
        }
    }

    return table[slen][plen];
}

char **checkForWildCards(char **data)
{
    char **newargs = (char **)malloc(sizeof(char) * 1024);
    int id = 0;

    while (*data)
    {
        if (strcontain(*data, "*"))
        {
            char *args = (char *)malloc(sizeof(char) * 1024);

            DIR *folder;
            struct dirent *entry;
            int files = 0;

            folder = opendir(".");

            if (folder == NULL)
            {
                perror("Unable to read directory");
            }

            while ((entry = readdir(folder)))
            {
                char *dname = entry->d_name;


                if (wildcardmatching(dname, *data, strlen(dname), strlen(*data)))
                {
                    // puts(dname);
                    args = strcatt(args, dname);
                    args = strcatt(args, " ");
                }
            }

            closedir(folder);

            char **dirs = str_tokenize(args, ' ');
            while (*dirs)
            {
                if (strlen(*dirs) != 0)
                    newargs[id++] = *dirs;
                dirs++;
            }
        }
        else
        {
            newargs[id++] = *data;
        }

        data++;
    }

    return newargs;
}

void showValue(char *val)
{

    prompt();
    printf("%s", val);
}

struct ShellCommands parse(char *data)
{


    char **cmd = (char **)malloc(sizeof(char) * 1024);
    char **red = (char **)malloc(sizeof(char) * 1024);

    struct ShellCommands command;
    int size = 0;

    command.outfile = NULL;
    command.infile = NULL;


    // pipelined command
    if (strcontain(data, "|"))
    {
        cmd = str_tokenize(data, '|');
    }
    else
        *cmd = data; // only a single command



    while (*cmd)
    {
        if (strcontain(*cmd, ">") or strcontain(*cmd, "<"))
        {

            // cat > infile < outfile
            // cat > infile  ------------------ Output redirection
            if (strcontain(*cmd, "<"))
            {
                red = str_tokenize(*cmd, '<');
                char *p1 = strip(red[0]);
                char *p2 = strip(red[1]);

                // case 1 -------- echo hello < infile > outfile
                if (strcontain(p2, ">"))
                {
                    red = str_tokenize(p2, '>');
                    command.infile = red[0];
                    command.outfile = red[1];
                }
                else
                {
                    command.infile = p2;
                }

                // case2 ---------- echo hello > infile < outfile
                if (strcontain(p1, ">"))
                {
                    red = str_tokenize(p1, '>');
                    command.simpleCommand[size++] = red[0];
                    command.outfile = red[1];
                }
                else
                {
                    command.simpleCommand[size++] = p1;
                }
            }

            else if (strcontain(*cmd, ">"))
            {
                red = str_tokenize(*cmd, '>');
                char *p1 = strip(red[0]);
                char *p2 = strip(red[1]);

                // case 1---------- echo hello > infile < outfile
                if (strcontain(p2, "<"))
                {
                    red = str_tokenize(p2, '<');
                    command.outfile = red[0];
                    command.infile = red[1];
                }
                else
                {
                    command.outfile = p2;
                }

                // case 2 -------- echo hello < infile > outfile
                if (strcontain(p1, ">"))
                {
                    red = str_tokenize(p1, '>');
                    command.simpleCommand[size++] = red[0];
                    command.outfile = red[1];
                }
                else
                {
                    command.simpleCommand[size++] = p1;
                }
            }

            else
            {
                command.infile = NULL;
                command.outfile = NULL;
            }
        }
        else
        {
            command.simpleCommand[size++] = *cmd;
        }
        cmd++;
    }

    // parsing ends.....

    // printf("STDOUT: %s\n", command.infile);
    // printf("STDIN: %s\n", command.outfile);
    // printf("SIZE: %d\n", size);

    command.size = size;

    return command;
}