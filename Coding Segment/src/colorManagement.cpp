#include <stdio.h>
#include "shell.h"

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