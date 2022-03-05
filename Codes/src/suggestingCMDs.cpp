#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#define DELETE -1
#define INSERT -2
#define SUBSTITUE -3
#define UNCHANGEditDistance -4
#define MAXSIZE 10005
using namespace std;

int c[MAXSIZE][MAXSIZE], b[MAXSIZE][MAXSIZE], tolerance = -1;
int m, n, totalCommandCount = 0;

char **readCMDOutput(char *cmd)
{
    FILE *p;
    int ch, buffer_size = 100024;
    size_t length = 0;
    ssize_t read;

    char *line = (char *)malloc(sizeof(char) * 1024);
    char **wordArr = (char **)malloc(sizeof(char) * buffer_size);

    p = popen(cmd, "r"); /* Unix */

    if (p == NULL)
    {
        puts("Unable to open process");
    }

    int i = 0;
    while ((read = getline(&line, &length, p)) != -1)
    {
        wordArr[i++] = line;
        line = (char *)malloc(sizeof(char) * 1024);
    }

    wordArr[i] = NULL;
    totalCommandCount = i;
    pclose(p);

    return wordArr;
}

void EditDistance(char *x, char *y, int row, int col)
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

            // cout << "X: " << x[i-1] << ", Y: " << y[i-1] << endl;

            if (x[i - 1] == y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1];
                b[i][j] = UNCHANGEditDistance;
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

struct node
{
    int data;
    char *word;
    struct node *left;
    struct node *right;
};

struct node *createNode(int value, char *info)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));

    p->data = value;
    p->word = info;
    p->left = NULL;
    p->right = NULL;

    return p;
}

void addNode(struct node *parent, int value, char *info)
{

    if (value <= parent->data)
    { // left node
        if (parent->left == NULL)
        {
            struct node *leftnode = createNode(value, info);
            parent->left = leftnode;
        }
        else
        {
            addNode(parent->left, value, info);
        }
    }
    else
    {
        if (parent->right == NULL)
        {
            struct node *rightnode = createNode(value, info);
            parent->right = rightnode;
        }
        else
        {
            addNode(parent->right, value, info);
        }
    }

    return;
}

void printTree(struct node *head, char *keyword)
{
    if (head == NULL)
    {
        return;
    }

    else
    {
        printTree(head->left, keyword);

        if (head->data <= 3 && (strlen(head->word) >= strlen(keyword)))
            printf("    command -> %s", head->word);

        printTree(head->right, keyword);
    }
}

void cmdSuggestion(char *rootWord)
{
    struct node *root = createNode(10, rootWord); // root value

    char **allCMDs = readCMDOutput("ls /usr/bin");

    char **temp = allCMDs;

    while (*temp)
    {
        m = strlen(*temp) + 1;
        n = strlen(rootWord) + 1;

        EditDistance(*temp, rootWord, m, n);

        int EdgeValue = c[m - 1][n - 1];

        if (EdgeValue <= 3 or (m == n))

            addNode(root, EdgeValue, *temp);

        temp++;
    }

    printf("Command \'%s\' not found, did you mean: \n", rootWord);
    printTree(root, rootWord);
    printf("Try: sudo apt install <deb name>\n");
    exit(EXIT_FAILURE);
}

void findExeFileName(char *cmd)
{
    printf("Executable file(s) of \"%s\" are: \n", cmd);

    char *path =
        "ls /usr/bin;";
    // "ls /usr/sbin; ls /sbin; ls /usr/local/sbin; ls /bin;"
    // "ls /usr/games; ls /usr/local/games; ls /snap/bin; ls /snap/bin";

    char **exeFilePath = readCMDOutput(path);

    while (*exeFilePath)
    {

        int flag = strsubstr(cmd, *exeFilePath);

        if (flag >= 0)
        {

            // Here we'll try to color the searched word.....

            char *newword = strip(*exeFilePath);
            //char **words = strsplit(cmd, newword);

            // while(*words){
            //     printf(">> %s\n", *words);
            //     words++;
            // }

            // // for(int i=0; i<strlen(fileName); i++){

            // //     // if(i <= coloredStrLen) printf("\u001b[31%c\u001b[0m", exeFilePath[i]);
            // //     // else printf("%c", fileName[i]);
            // // }

            printf("%s", *exeFilePath);
            break;
        }

        exeFilePath++;
    }
}