#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#define DELETE -1
#define INSERT -2
#define SUBSTITUE -3
#define UNCHANGED -4
using namespace std;

int c[100][100], b[100][100];
int m, n;

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

struct node
{
    int data;
    string word;
    struct node *left;
    struct node *right;
};

struct node *createNode(int value, string info)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->data = value;
    p->word = info;
    p->left = NULL;
    p->right = NULL;

    return p;
}

void addNode(struct node *parent, int value, string info)
{

    if (value <= parent->data)
    { // left node
        if (parent->left == NULL)
        {
            struct node *leftnode = createNode(value, info);
            parent->left = leftnode;
            // parent->word = info;
            printf("LEFT NODE ADDED >> %d---P: %d\n", value, parent->data);
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
            // parent->word = info;
            printf("RIGHT NODE ADDED >> %d---P: %d\n", value, parent->data);
        }
        else
        {
            addNode(parent->right, value, info);
        }
    }

    return;
}

void printTree(struct node *head)
{
    if (head == NULL)
    {
        return;
    }

    else
    {
        printTree(head->left);

        printf("--%s(%d)--\n", head->word, head->data);

        printTree(head->right);
    }
}

int main()
{

    int x = 10;
    int size = 4;
    string rootWord = "cat";
    struct node *root = createNode(x, rootWord);

    while (size--)
    {
        string newWord;
        cout << "Enter Word: " ;
        cin >> newWord;

        m = newWord.size() + 1;
        n = rootWord.size() + 1;

        char xx[m + 1], yy[n + 1];

        xx[0] = ' ';
        yy[0] = ' ';

        for (int i = 1; i < m; i++)
            xx[i] = newWord[i - 1];
        for (int i = 1; i < n; i++)
            yy[i] = rootWord[i - 1];

        ED(xx, yy, m, n);

        int edgeValue = c[m-1][n-1];
        addNode(root, edgeValue, newWord);

    }
    printTree(root);
}