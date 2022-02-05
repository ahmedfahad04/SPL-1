#include <stdlib.h>
#include <stdio.h>

size_t strlen(char *str){

    size_t len = 0;

    while(str[len]!='\0'){
        len++;
    }

    return len;

}

bool strcpy(char *to, char *from){
    
    while (*from){
        *to++ = *from++;
    }

    return 1;
}



int main()
{
    FILE *fp;

    if ((fp = fopen("/etc/hosts", "r")) == NULL)
    {
        printf("Failed to open /etc/hostname\n");
    }

    char *tmp, *tmp2, ch, **words, a[100], b[100];
    char hostname[100];
    int loc = 0, line = 1;

    while (fscanf(fp, "%s %s ", a, b) != EOF)
    {        
        if(line == 2) 
            bool stat = strcpy(hostname, b);
           
        line++;
    }

    printf("MY HOSTNAME: %s", hostname);



    

    fclose(fp);
}