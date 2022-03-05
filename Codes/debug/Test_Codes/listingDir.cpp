#include <stdio.h>
#include <dirent.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#define DELETE -1
#define INSERT -2
#define SUBSTITUE -3
#define UNCHANGED -4
#define BUFFER_SIZE 1024
#define MAXSIZE 1000055
using namespace std;

int c[100][100], b[100][100];
int m, n, mindist = INT_MAX, k = 0;
string closest_words[100];

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

char **environmentVariablePath()
{

    char *s = secure_getenv("PATH");
    printf(">> %s", s);

    

    char **paths = str_tokenize(s, ':');
    // while (*paths)
    // {
    //     //printf(">> %s\n", *paths);
    //     paths++;
    // }

    return paths;
}

char ** readCMDPath()
{

    DIR *folder;
    struct dirent *files;
    

    char **envPath = environmentVariablePath();
    char ** path = (char **) malloc (sizeof(char) * MAXSIZE);  
    int i = 0;
    int cnt = 0;
    while (*envPath)
    {
       
        //cout << "==============> " << *envPath << endl;
        folder = opendir(*envPath);

        if (folder == NULL)
        {
            perror("Unable to read the directory");
        }

        else
        {
            while (files = readdir(folder))
            {
                cnt++;
                printf("> %s\n", files->d_name);
                path[i++] = files->d_name;
            }

            //printf("Total Files: %d\n", cnt);
        }

        closedir(folder);

        envPath++;
    }

    return path;
}

int main()
{

   char ** p = readCMDPath();
   int k =0;
   while(*p){
       p++;       
   }
}