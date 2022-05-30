#include <bits/stdc++.h>
using namespace std;

void prefixTable(char *neddle, int neddle_len, int *LPS)
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
    int neddle_len = strlen(neddle);
    int heystack_len = strlen(heystack);

    int LPS[neddle_len];

    prefixTable(neddle, neddle_len, LPS);
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


char ** strsplit(char *find, char *text)
{

    int pos = strsubstr(find, text);
    int len = strlen(find);
    int finalPos = pos + len;

    char **chunk = (char **)malloc(sizeof(char) * 1024);
    char *word = (char *)malloc(sizeof(char) * 1024);
    // char *str2 = (char *)malloc(sizeof(char) * 1024);

    chunk[0] = find;

    int id = 0;

    for(int i=finalPos; i<strlen(text); i++){
        word[id++] = text[i];
    }

    word[id] = '\0';
    chunk[1] = word;

    return chunk;
}

char *strip(char *word)
{
    int id = 0;
    char *demo = (char *)malloc(sizeof(char) * 1024);

    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] != ' ')
            demo[id++] = word[i];
    }

    demo[id] = '\0';
    

    return demo;
}

int main(){

    char * a = "brave";
    char * b = "brave-browser   ";
    char ** ans = strsplit(a, b);
    char * newans = strip(b);
    printf("%s...%d\n", newans, strlen(newans));

    while(*ans){

        printf("%s\n", *ans);
        ans++;
    }
}