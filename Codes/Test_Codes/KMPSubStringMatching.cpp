#include <bits/stdc++.h>

void PieTable(char *neddle, int neddle_len, int *LPS);

int strsubstr(char *neddle, char *heystack)
{
    int neddle_len = strlen(neddle);
    int heystack_len = strlen(heystack);

    int LPS[neddle_len];

    PieTable(neddle, neddle_len, LPS);
    int i = 0;
    int j = 0;
    while (i < heystack_len)
    {
        if (neddle[j] == heystack[i])
        {
            j++;
            i++;
        }
        if (j == neddle_len)
        {
            return (i - j);
            // j = LPS[j - 1];
        }

        else if (i < heystack_len && neddle[j] != heystack[i])
        {

            if (j != 0)
                j = LPS[j - 1];
            else
                i = i + 1;
        }
    }

    return -1;
}

void PieTable(char *neddle, int neddle_len, int *LPS)
{

    int len = 0;
    LPS[0] = 0;
    int i = 1;
    while (i < neddle_len)
    {
        if (neddle[i] == neddle[len])
        {
            len++;
            LPS[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = LPS[len - 1];
            }
            else
            {
                LPS[i] = 0;
                i++;
            }
        }
    }
}

int main()
{
    char heystack[] = "AABAACAADAABAABA";
    char neddle[] = "AABA";
    int x = strsubstr(neddle, heystack);
    printf("AANS: %d", x);
    return 0;
}