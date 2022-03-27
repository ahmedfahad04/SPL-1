#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

struct student
{
    char *name;
    int roll;
    struct address
    {
        char *street;
        int holdingNumber;
    } ad;
};

struct commandTable{
    int size = 0;
    
    struct simpleCommand{

        char *args;

    } command;
};

int main()
{

    struct student bsse12[10];

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {

        char x[1000];
        cout << "NAME: ";
        scanf("%s", x);
        bsse12[i].name = x;
        fflush(stdin);

        char r[1000];
        cout << "\nStreet: ";
        scanf("%s", r);
        bsse12[i].ad.street = r;
        fflush(stdin);

        int hold;
        cout << "\nHolding number: ";
        cin >> hold;

        bsse12[i].ad.holdingNumber = hold;
    }

    for (int i = 0; i < n; i++)
    {

        cout << bsse12[i].name <<  endl;
        cout << bsse12[i].ad.street << " " << bsse12[i].ad.holdingNumber << endl;
    }
}