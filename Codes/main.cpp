#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
using namespace std;


int main(){

    char *cmd;

    do{

        cmd = take_user_input();
        printf("%s\n", cmd);
        

    } while(!strcmp(cmd, "exit")); 

}