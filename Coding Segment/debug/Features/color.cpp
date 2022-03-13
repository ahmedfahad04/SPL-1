#include <bits/stdc++.h>
using namespace std;

char *strcatt(const char *with, const char *str)
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


char * numToStr(int num){
	char * result = (char*) malloc(sizeof(char) * 1024);
	
	
	int i=0;
	while(num>0){
		int x = num%10;
		num /= 10;
		result[i++] = x + '0';

	}
	
	result[i] = '\0';
	
	char * str = (char*) malloc(sizeof(char) * 1024);
	
	int j = 0;
	for(; j<i; j++){
		str[j] = result[i-j-1];
		//printf("%c..\n", result[j]);
	}
	
	str[j] = '\0';	
	
	return str;
	
}

void colorManager()
{

    printf("INSIDE COLOR MANAGER\n");

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {

            int val = ((i*16 + j)%256);
            char *id = numToStr(val);
            char * p1 = strcatt("\u001b[38;5;", id);
            char * code = strcatt(p1, "m");

            // partially done..
            // printf("\u001b[38;5;%c %d ", val, i*16+j);
            printf("user%s(%d).. host\n", code, val);
        }

        printf("\n");
    }
}

int main(){
	colorManager();
}
