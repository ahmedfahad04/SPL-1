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

char * strcpy(const char *from)
{
    int len = strlen(from);
    char res[len + 1];

    int i;
    for (i = 0; i < len; i++)
        res[i] = from[i];

    res[i] = '\0';

    char *to = res;
    return to;
}

int colorManager()
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

            // printf("%s%-5d%s", f_code, val, "\u001b[0m");
            printf(" %-3d - ", val);



            // background color
            char * bg_p1 = strcatt("\u001b[48;5;", id);
            char * bg_code = strcatt(bg_p1, "m");


            printf("%s    %s", bg_code, "\u001b[0m");
        }

        printf("\n");
    }

    printf("\nEnter color code (eg. 211): ");
    int color_code;
    scanf("%d", &color_code);

    return color_code;
}

char *showCode()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {

            int val = ((i * 16 + j) % 256);

            // font color
            char *id = numToStr(val);
            char *f_p1 = strcatt("\u001b[38;5;", id);
            char *f_code = strcatt(f_p1, "m");

            // printf("%s%-5d%s", f_code, val, "\u001b[0m");
            printf(" %-3d - ", val);

            // background color
            char *bg_p1 = strcatt("\u001b[48;5;", id);
            char *bg_code = strcatt(bg_p1, "m");

            // printf("CODE: %s ", bg_code);
            printf("%s    %s", bg_code, "\u001b[0m");
        }

        printf("\n");
    }

    printf("\nEnter color code for background (eg. 211): ");
    int color_code;
    scanf("%d", &color_code);

    // ==> need to be solved.
    char *userChoice = numToStr(color_code);
    char *codeP1 = strcatt("\u001b[48;5;", userChoice);
    char *BG_COLOR;

    BG_COLOR = strcpy(strcatt(codeP1, "m"));
    return BG_COLOR;
}

int main(){
	// int code = colorManager();

    // char * userChoice = numToStr(code);
    // char * codeP1 = strcatt("\u001b[48;5;", userChoice);
    // char * BG_COLOR = strcpy(strcatt(codeP1, "m"));

    // printf("YOUR CODE: %s%d\n\n\n",  BG_COLOR, code);

    char * colorCode = "\u001b[48;5;230m";
    char * tmp = showCode();
    if(strcmp(tmp, colorCode)) printf("%s", tmp);
    else printf("%s", colorCode);


}
