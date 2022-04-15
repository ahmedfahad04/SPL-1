#include <cstdio>
#include <stdlib.h>

char * cmd[100];

int main(){

    int n;
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        char *name;
        scanf("%s", name);
    }

    for(int i=0; i<n; i++){
        printf("%s..\n", cmd[i]);
    }
   

    

}