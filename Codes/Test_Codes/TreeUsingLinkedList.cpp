#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *createNode(int value)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->data = value;
    p->left = NULL;
    p->right = NULL;

    return p;
}

void addNode(struct node *parent, int value)
{

    if (value <= parent->data)
    { // left node
        if (parent->left == NULL)
        {
            struct node *leftnode = createNode(value);
            parent->left = leftnode;
            printf("LEFT NODE ADDED >> %d---P: %d\n", value, parent->data);
        }
        else
        {
            addNode(parent->left, value);
        }
    }
    else
    {
        if (parent->right == NULL)
        {
            struct node *rightnode = createNode(value);
            parent->right = rightnode;
            printf("RIGHT NODE ADDED >> %d---P: %d\n", value, parent->data);
        }
        else
        {
            addNode(parent->right, value);
        }
    }

    return;
}

void printTree(struct node *head, int nodes)
{

    if (head == NULL){
        return;
    }

    else
    {
        printTree(head->left, nodes);

        printf("--%d--\n", head->data);

        printTree(head->right, nodes);
    }
}

int main()
{

    int x = 10;
    int n = 5;
    struct node *root = createNode(x);
    addNode(root, 7);
    addNode(root, 5);
    addNode(root, 15);
    addNode(root, 12);
    addNode(root, 16);
    printTree(root, n);
}