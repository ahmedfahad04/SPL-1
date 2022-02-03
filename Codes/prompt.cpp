#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#define BUFFER_SIZE 1024
using namespace std;


char *take_user_input(){
    
    char *buffer, *filtered_buffer;
    char ch;
    int location = 0, buffer_size = BUFFER_SIZE;

    //dynamically allocate memory to store the user prompt
    buffer = (char *)malloc(sizeof(char) * buffer_size);
    filtered_buffer = (char *)malloc(sizeof(char) * buffer_size);

    printf("myShell$ ");

    while(1){

        scanf("%c", &ch);

        if((int)ch == EOF or ch == '\n' or buffer == NULL){
            buffer[location] = '\0';
            break;
        }

        else{
            buffer[location] = ch;
        }

        if(location > buffer_size){
            buffer_size += 1024;
            buffer = (char *)realloc(buffer, buffer_size); 
            filtered_buffer = (char *)realloc(buffer, buffer_size); 
        }
        
        location++;
    }

    // filtered_buffer = filter(buffer);
    // return filtered_buffer;
    return buffer;
    
}

char *filter(char *ch){

    char *newstr;
    newstr = (char*)malloc(sizeof(char) * BUFFER_SIZE);

    int flag = 0, id = 0, word = 0;
    char prev = ' ';

    while(1){

        if(*ch == ' ' && prev != ' '){

            flag = 0;
            word++;
            
        }
        else{

            newstr[id] = *ch;
            id++;
            flag = 1;
            prev = *ch;
            printf("CHAR: %c..", *ch);

        }

        ch++;

        if(*ch == '\0') break;

    }

    // newstr[id] = '\0';

    printf("\nAfter, %s, len = %ld, word = %d", newstr, strlen(newstr), word);    

    return ch;

}