#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024

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

char *take_user_input()
{
    char *buffer, *splitted_words, *path;
    char ch;
    int location = 0, buffer_size = BUFFER_SIZE;

    // dynamically allocate memory to store the user prompt
    buffer = (char *)malloc(sizeof(char) * buffer_size);
    splitted_words = (char *)malloc(sizeof(char) * buffer_size);

    while (1)
    {
        scanf("%c", &ch);
        if (ch == '\r')
            continue;

        if (location > buffer_size)
        {
            buffer_size += 1024;
            buffer = (char *)realloc(buffer, buffer_size);
            splitted_words = (char *)realloc(buffer, buffer_size);
        }

        if ((int)ch == EOF or ch == '\n' or buffer == NULL or ch == '\r')
        {
            // this portion is for taking multiline input delimited by '\'
            int tmploc = location - 1;

            if (buffer[tmploc] == '\\')
            {
                location--;
                printf("> ");
                continue;
            }

            buffer[location] = '\0';
            break;
        }

        buffer[location] = ch;
        location++;
    }

    // splitted_words = splitstr(buffer);
    // return splitted_words;

    return buffer;
}

size_t strlen(const char *str)
{

    size_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    return len;
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

typedef struct
{
    char *key;
    char *value;
    int id;
    int size = 0;

} hashtable;

hashtable ht[100];

void setValue(char *cmd, char *alias, int id)
{

    FILE *f1;
    int record;

    f1 = fopen("aliasing.txt", "a");
    fprintf(f1, "%s %s\n", cmd, alias, id);
    fclose(f1);
}

int main()
{

    char *data = (char *)malloc(sizeof(char) * 100);
    char **words = (char **)malloc(sizeof(char) * 100);
    char **refactor = (char **)malloc(sizeof(char) * 100);
    data = take_user_input();

    words = str_tokenize(data, ' ');

    int k = 0;

    if (strcmp(words[0], "alias"))
    {
        refactor = str_tokenize(words[1], '=');
        puts(refactor[0]);
        puts(refactor[1]);
        // setValue(refactor[0], refactor[1], ++k);
    }

    FILE *f2;
    f2 = fopen("aliasing.txt", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, f2)) != -1)
    {
        char **chunks = (char **)malloc(sizeof(char) * 500);
        
        chunks = str_tokenize(line, ' ');
        if (strcmp(chunks[0], refactor[0]))
        {
            puts(chunks[1]);
            break;
        }
        // k++;
    }

    fclose(f2);

    // printf("LINE: %d\n", k);

    // int record;
    // FILE *f2;

    // f2 = fopen("aliasing.txt", "r");
    // fseek(f2, 0, SEEK_END);
    // fscanf(f2, "%d", record);
    // fclose(f2);

    // for(int i=0; i<record; i++){

    // }
}