#include <stdio.h>
#include <stdlib.h>

size_t strlen(char *str){

    size_t len = 0;

    while(str[len]!='\0'){
        len++;
    }

    return len;

}

int main(){
    
    char *ch, *newstr;
    int len = strlen(ch);
    ch = (char *)malloc(sizeof(char)*1024);
    newstr = (char *)malloc(sizeof(char)*1024);

    
    printf("Before, %s, len = %d", ch, len);

    int flag = 0, id = 0, word = 0;
    char prev = ' ';

    while(*ch){

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
    }

    newstr[id] = '\0';

    printf("\nAfter, %s, len = %ld, word = %d", newstr, strlen(newstr), word);


}