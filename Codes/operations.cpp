#include <stdio.h>
#include <stdlib.h>

size_t strlen(char *str)
{

    size_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    return len;
}

bool strcmp(char *a, char *b)
{

    if (strlen(a) != strlen(b))
        return false;
    else
    {

        while (*a)
        {

            if (*a != *b)
                return false;
            a++;
            b++;
        }

        return true;
    }
}

char *strcpy(char *from)
{
    char *to = (char *)malloc(sizeof(char) * 1024);

    int i;
    for (i = 0; i < strlen(from); i++)
        to[i] = from[i];

    from[i] = '\0';

    return to;
}

char *strcatt(char *with, char *str)
{
    char ans[2000];
    int i = 0;

    while (*with != '\0')
    {
        ans[i++] = *with++;
    }

    while (*str != '\0')
    {
        ans[i++] = *str++;
    }

    ans[i] = '\0';

    char *res = ans; // always try to declare *res -> this variable where you need it, don't declare at top. It might results in wrong answer.

    return res;
}

char *strreplace(char *data, char *with, char *str){

    char ans[1024], *p1, *res, tmp[1024];;
    int start = -1, end = -1, pos = -1;

    int id = 0, j = 0;
    for(int i=0; i<strlen(data); i++){

        //cout << "D: " << data[i] << ", W: " << with[j] <<", I: " << i <<endl;

        if(data[i] == with[j]){
            if(start == -1) start = i;
            j++;
        }

        else if ( (data[i] != with[j]) && start != -1){
            end = i;
            break;
        }

        if(start == -1){
            ans[++id] = data[i];
        }

    }
    
    p1 = strcatt(ans, str);

    id = 0;
    for(int k=end; k<strlen(data); k++){
        tmp[id++] = data[k];
    }

    p1 = strcatt(p1, tmp);

    return p1;

}