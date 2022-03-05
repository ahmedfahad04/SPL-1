#include <bits/stdc++.h>
using namespace std;

int main(){

    FILE *p;
    char * line = NULL;
    ssize_t read = 0;
    size_t length = 0;

    p = popen("ls", "r");

    while((read = getline(&line, &length, p))!=-1){
        cout << line << "";
    }

    pclose(p);

    // 5 min presentation
    // FAQ
    // live demo
    // ki ki korte cai, ki kora baki ase, ki ki korsi, keno korsi, ki ki use korbo
    // supervisor er sign must..
}


