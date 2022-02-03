#include <stdio.h>
#include <stdlib.h>

size_t strlen(char *str){

    size_t len = 0;

    while(str[len]!='\0'){
        len++;
    }

    return len;

}

bool strcmp(char *a, char *b){

    if(strlen(a) != strlen(b)) return false;
    else{

        while(*a){
            
            if(*a != *b) return false;
            a++;
            b++;
        }

        return true;
    }
}

