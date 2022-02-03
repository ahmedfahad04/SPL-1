#include <bits/stdc++.h>
using namespace std;

#define UP_ARROW_KEY 72
#define DOWN_ARROW_KEY 80

int main()
{
    int c;
    while(1){
        c = 0;

        c = getc(stdin);

        if(c = UP_ARROW_KEY) cout << "UP\n";
        else if (c == DOWN_ARROW_KEY) cout << "DOWN\n"; 
        else break;
    }
}
