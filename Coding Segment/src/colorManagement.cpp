#include <stdio.h>
#include "shell.h"

// char *showCode()
// {
//     for (int i = 0; i < 16; i++)
//     {
//         for (int j = 0; j < 16; j++)
//         {

//             int val = ((i * 16 + j) % 256);

//             // font color
//             char *id = numToStr(val);
//             char *f_p1 = strcatt("\u001b[38;5;", id);
//             char *f_code = strcatt(f_p1, "m");

//             // printf("%s%-5d%s", f_code, val, "\u001b[0m");
//             printf(" %-3d - ", val);

//             // background color
//             char *bg_p1 = strcatt("\u001b[48;5;", id);
//             char *bg_code = strcatt(bg_p1, "m");

//             // printf("CODE: %s ", bg_code);
//             printf("%s    %s", bg_code, "\u001b[0m");
//         }

//         printf("\n");
//     }

//     printf("\nEnter color code for background (eg. 211): ");
//     int color_code;
//     scanf("%d", &color_code);

//     // ==> need to be solved.
//     char *userChoice = numToStr(color_code);
//     char *codeP1 = strcatt("\u001b[48;5;", userChoice);
//     char *codeP2 = strcpy(strcatt(codeP1, "m"));
//     char *BG_COLOR = strcatt(codeP2, "\0");
//     return BG_COLOR;
// }

// will add more color if time permits

void userManual()
{
    
    printf("color [--fg/--bg] [user/host] [color code]\n");
    printf("Color Codes:\t");
    printf("%s red %s\t", FONT_RED, RESET);
    printf("%s yel %s\t", FONT_YEL, RESET);
    printf("%s grn %s\t", FONT_GRN, RESET);
    printf("%s blu %s\t", FONT_BLU, RESET);
    printf("%s blk %s\t", FONT_BLK, RESET);
    printf("%s mag %s\t", FONT_MAG, RESET);
    printf("%s cyn %s\t", FONT_CYN, RESET);
    puts("");
    return;
}
char *selectBGColor(char *args)
{
    char *bgcolor;

    if (strcmp(args, "red"))
    {
        bgcolor = BG_RED;
    }
    else if (strcmp(args, "grn"))
    {
        bgcolor = BG_GRN;
    }
    else if (strcmp(args, "blu"))
    {
        bgcolor = BG_BLU;
    }
    else if (strcmp(args, "cyn"))
    {
        bgcolor = BG_CYN;
    }
    else if (strcmp(args, "yel"))
    {
        bgcolor = BG_YEL;
    }
    else if (strcmp(args, "blk"))
    {
        bgcolor = BG_BLK;
    }
    else if (strcmp(args, "mag"))
    {
        bgcolor = BG_MAG;
    }
    else
    {
        printf("Wrong color code.\n");
        userManual();
        return NULL;
    }

    return bgcolor;
}

char *selectFGColor(char *args)
{
    char *fgcolor;

    if (strcmp(args, "red"))
    {
        fgcolor = FONT_RED;
    }
    else if (strcmp(args, "grn"))
    {
        fgcolor = FONT_GRN;
    }
    else if (strcmp(args, "blu"))
    {
        fgcolor = FONT_BLU;
    }
    else if (strcmp(args, "cyn"))
    {
        fgcolor = FONT_CYN;
    }
    else if (strcmp(args, "yel"))
    {
        fgcolor = FONT_YEL;
    }
    else if (strcmp(args, "blk"))
    {
        fgcolor = FONT_BLK;
    }
    else if (strcmp(args, "mag"))
    {
        fgcolor = FONT_MAG;
    }
    else
    {
        printf("Wrong color code.\n");
        userManual();
        return NULL;
    }

    return fgcolor;
}