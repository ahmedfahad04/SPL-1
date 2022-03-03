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

// void ED(char x[], char y[], int row, int col)
// {
//     // initialize
//     for (int i = 0; i < row; i++)
//     {
//         for (int j = 0; j < col; j++)
//         {

//             c[i][j] = 0;
//             b[i][j] = 0;
//         }
//     }

//     for (int i = 0; i < row; i++)
//     {
//         c[0][i] = i;
//         b[0][i] = -2;
//     }
//     for (int i = 0; i < row; i++)
//     {
//         c[i][0] = i;
//         b[i][0] = -1;
//     }

//     // calculation
//     for (int i = 1; i < row; i++)
//     {

//         for (int j = 1; j < col; j++)
//         {

//             int subs = c[i - 1][j - 1];
//             int del = c[i - 1][j];
//             int insert = c[i][j - 1];

//             if (x[i] == y[j])
//             {
//                 c[i][j] = c[i - 1][j - 1];
//                 b[i][j] = UNCHANGED;
//             }

//             else
//             {

//                 int m1 = min(subs, del);
//                 int minimum = min(m1, insert);

//                 // cout << x[i] << " " << y[j] << endl;
//                 if (minimum == subs)
//                 {

//                     // min = substitute
//                     c[i][j] = c[i - 1][j - 1] + 1;
//                     b[i][j] = SUBSTITUE;
//                     // cout << "SUBSTITUTE\n";
//                 }

//                 else if (minimum == c[i][j - 1])
//                 {
//                     // min = insert
//                     c[i][j] = c[i][j - 1] + 1;
//                     b[i][j] = INSERT;
//                     // cout << "INSERT\n";
//                 }

//                 else
//                 {

//                     // min = del
//                     c[i][j] = c[i - 1][j] + 1;
//                     b[i][j] = DELETE;
//                     // cout << "DEL\n";
//                 }
//             }
//         }
//     }
// }

// void execute(string a, string d)
// {

//     m = a.size() + 1;
//     n = d.size() + 1;

//     char xx[m + 1], yy[n + 1];

//     xx[0] = ' ';
//     yy[0] = ' ';

//     for (int i = 1; i < m; i++)
//         xx[i] = a[i - 1];
//     for (int i = 1; i < n; i++)
//         yy[i] = d[i - 1];

//     // function call
//     ED(xx, yy, m, n);

//     if(a == d){
//         cout << "String matched\n";
//         return;
//     }

// }

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