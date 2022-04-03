#include <bits/stdc++.h>
#include <dirent.h>
#define BUFFER_SIZE 1024
using namespace std;

bool wildcardmatching(char *str, char *pat, int slen, int plen)
{

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

char **str_tokenize(char *ch, char sep)
{

    char *newstr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    char **raw_words = (char **)malloc(sizeof(char) * BUFFER_SIZE);

    int cnt = 0, k = 0, j = 0;

    // split the string into words based on spaces
    for (int i = 0;; i++)
    {
        if (((ch[i] == sep && i > 0) || (ch[i] == '\0') || (ch[i] == '\n')) && (ch[i - 1] != sep))
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

    raw_words[k] = NULL;

    return raw_words;
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
                    puts(dname);
                    args = strcatt(args, dname);
                }
            }

            closedir(folder);

            newargs[id++] = args;
        }
        else
        {
            newargs[id++] = *data;
        }

        data++;
    }

    return newargs;
}

int main()
{
    char ** tokens = str_tokenize("wc *.cpp -l", ' ');
    char ** newtokens = checkForWildCards(tokens);

    while(*newtokens){
        puts(*newtokens);
        newtokens++;
    }
}