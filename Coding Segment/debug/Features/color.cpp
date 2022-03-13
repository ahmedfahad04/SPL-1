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
 
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {

            int val = ((i*16 + j)%256);
            
            // font color
            char * id = numToStr(val);
            char * f_p1 = strcatt("\u001b[38;5;", id);
            char * f_code = strcatt(f_p1, "m");

            printf("%s%-5d%s", f_code, val, "\u001b[0m");


            // background color
            char * bg_p1 = strcatt("\u001b[48;5;", id);
            char * bg_code = strcatt(bg_p1, "m");


            printf("%s%-5d%s", bg_code, val, "\u001b[0m");
        }

        printf("\n");
    }
}

int main(){
	colorManager();
}
