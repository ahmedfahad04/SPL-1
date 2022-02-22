#include <stdio.h>
#include <dirent.h>
#include <bits/stdc++.h>
#define DELETE -1
#define INSERT -2
#define SUBSTITUE -3
#define UNCHANGED -4
using namespace std;

int c[100][100], b[100][100];
int m, n, mindist = INT_MAX, k = 0;
string closest_words[100];

void ED(char x[], char y[], int row, int col)
{
    // initialize
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {

            c[i][j] = 0;
            b[i][j] = 0;
        }
    }

    for (int i = 0; i < row; i++)
    {
        c[0][i] = i;
        b[0][i] = -2;
    }
    for (int i = 0; i < row; i++)
    {
        c[i][0] = i;
        b[i][0] = -1;
    }

    // calculation
    for (int i = 1; i < row; i++)
    {

        for (int j = 1; j < col; j++)
        {

            int subs = c[i - 1][j - 1];
            int del = c[i - 1][j];
            int insert = c[i][j - 1];

            if (x[i] == y[j])
            {
                c[i][j] = c[i - 1][j - 1];
                b[i][j] = UNCHANGED;
            }

            else
            {

                int m1 = min(subs, del);
                int minimum = min(m1, insert);

                // cout << x[i] << " " << y[j] << endl;
                if (minimum == subs)
                {

                    // min = substitute
                    c[i][j] = c[i - 1][j - 1] + 1;
                    b[i][j] = SUBSTITUE;
                    // cout << "SUBSTITUTE\n";
                }

                else if (minimum == c[i][j - 1])
                {
                    // min = insert
                    c[i][j] = c[i][j - 1] + 1;
                    b[i][j] = INSERT;
                    // cout << "INSERT\n";
                }

                else
                {

                    // min = del
                    c[i][j] = c[i - 1][j] + 1;
                    b[i][j] = DELETE;
                    // cout << "DEL\n";
                }
            }
        }
    }
}

void execute(string a, string d)
{

    m = a.size() + 1;
    n = d.size() + 1;

    char xx[m + 1], yy[n + 1];

    xx[0] = ' ';
    yy[0] = ' ';

    for (int i = 1; i < m; i++)
        xx[i] = a[i - 1];
    for (int i = 1; i < n; i++)
        yy[i] = d[i - 1];

    // function call
    ED(xx, yy, m, n);

    if(a == d){
        cout << "String matched\n";
        return;
    }

}

int main()
{

    DIR *folder;
    struct dirent *files;

    char ch[100];
    int cnt = 0;
    string s = "clear";
    printf("Enter directory path: ");
    scanf("%s", ch);

    folder = opendir(ch);

    if (folder == NULL)
    {
        perror("Unable to read the directory");
    }

    else
    {

        while (files = readdir(folder))
        {
            cnt++;

            execute(s, files->d_name);
            // printf("> %s\n", files->d_name);
        }

        printf("Total Files: %d\n", cnt);
    }

    closedir(folder);
}