#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

size_t strlen(const char *str)
{

    size_t len = 0;

    if (str[0] == '\0')
        return 0;

    else
    {
        while (str[len] != '\0')
        {
            len++;
        }

        return len;
    }
}

char **str_tokenize(char *ch, char sep)
{

    char *newstr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    char **raw_words = (char **)malloc(sizeof(char) * BUFFER_SIZE);

    int cnt = 0, k = 0, j = 0;

    // split the string into words based on spaces
    for (int i = 0;; i++)
    {
        if (((ch[i] == sep && i > 0) || (ch[i] == '\0') || (ch[i] == '\n')) && (ch[i - 1] != sep))
        {
            cnt++;
            newstr[j] = '\0';
            raw_words[k++] = newstr;

            newstr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
            j = 0;

            if (ch[i] == '\0')
                break;
        }

        else
        {
            newstr[j++] = ch[i];
        }
    }

    raw_words[k] = NULL;

    return raw_words;
}

bool strcmp(const char *a, const char *b)
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

char **userNames()
{
    char **names = (char **)malloc(sizeof(char) * BUFFER_SIZE);
    int id = 0;

    FILE *fp;

    if ((fp = fopen("/etc/passwd", "r")) == NULL)
    {
        printf("Failed to open /etc/passwd\n");
    }

    // we need to use character array instead of pointers.
    // as pointer array of character lost the input after reading the whole file.
    char a[200], b[200], *host;
    int line = 1;

    while (fscanf(fp, "%s", a) != EOF)
    {
        char **res = str_tokenize(a, ':');
        
        if (res[5] != 0 )
            names[id++] = res[5];

        // printf("%s", res[5]);
        // printf("\n==============================\n");
    }

    names[id] = NULL;

    printf("ID: %d\n", id);
    for (int i = 0; names[i]; i++)
        printf("%s\n", names[i]);

    fclose(fp);

    return names;
}

int main()
{
    char **test = userNames();
}