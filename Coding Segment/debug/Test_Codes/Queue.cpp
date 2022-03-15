#include <bits/stdc++.h>
using namespace std;

int main(){

    queue<int> q;
    q.push(12);
    q.push(25);
    q.push(14);

    while(!q.empty()){
        int x = q.front();
        cout << x << endl;
        q.pop();
    }


}