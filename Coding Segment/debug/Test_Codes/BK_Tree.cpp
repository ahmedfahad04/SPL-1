#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define DELETE -1
#define INSERT -2
#define SUBSTITUE -3
#define UNCHANGED -4
#define MAXSIZE 10005
using namespace std;

int c[MAXSIZE][MAXSIZE], b[MAXSIZE][MAXSIZE], tolerance = -1;
int m, n, totalCommandCount = 0;

size_t strlen(const char *str)
{

    size_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    return len;
}

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
        // printf("%s", line);
        wordArr[i++] = line;
        line = (char *)malloc(sizeof(char) * 1024);
    }

    wordArr[i] = NULL;
    totalCommandCount = i;
    pclose(p);

    return wordArr;
}

void ED(char *x, char *y, int row, int col)
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
            if (value <= 3)
                printf("LEFT NODE ADDED >> %d === %s ==== ---P: %d\n", value, info, parent->data);
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
            if (value <= 3)
                printf("RIGHT NODE ADDED >> %d === %s ==== ---P: %d\n", value, info, parent->data);
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

        if ( head->data <= 3 && (strlen(head->word) >= strlen(keyword)) )
            printf("--%s(%d)--\n", head->word, head->data);

        printTree(head->right, keyword);
    }
}

int main()
{

    char *rootWord = (char *)malloc(1024);
    cout << "Enter the root word: ";
    scanf("%s", rootWord);

    struct node *root = createNode(10, rootWord);    // root value

    char **allCMDs = readCMDOutput("ls /usr/bin");

    char **temp = allCMDs; 

    while (*temp)
    {
        m = strlen(*temp) + 1;
        n = strlen(rootWord) + 1;

        // cout << "M: " << m << ", N: " << n << endl;

        ED(*temp, rootWord, m, n);

        int edgeValue = c[m - 1][n - 1];
        if (edgeValue <= 3 or (m == n)) addNode(root, edgeValue, *temp);

        temp++;
    }

    
    printTree(root, rootWord);
}