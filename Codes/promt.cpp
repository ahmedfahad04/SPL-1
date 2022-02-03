#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
using namespace std;


char *take_user_input(){
    
    char *buffer;
    char ch;
    int location = 0, buffer_size = 1024;

    //dynamically allocate memory to store the user prompt
    buffer = (char *)malloc(sizeof(char) * buffer_size);

    printf("myShell$ ");

    while(1){

        scanf("%c", &ch);

        if((int)ch == EOF or ch == '\n'){
            buffer[location] = '\0';
            return buffer;
        }

        else{
            buffer[location] = ch;
        }

        if(location > buffer_size){
            buffer_size += 1024;
            buffer = (char *)realloc(buffer, buffer_size); 
        }
        
        location++;
    }
    
}
