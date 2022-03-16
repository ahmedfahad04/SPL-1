#include <stdio.h>
#include "shell.h"

char * colorManager()
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
    // eventLoopWithColors(BG_COLOR);
}