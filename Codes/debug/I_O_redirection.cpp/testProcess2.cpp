#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
using namespace std;

size_t strlen(const char *str)
{

    size_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    return len;
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

        if ((int)ch == EOF or ch == '\n' or buffer == NULL)
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

char **removeWhiteSpace(char **raw_data)
{

    char **words = (char **)malloc(sizeof(char) * BUFFER_SIZE);
    int i = 0;

    // removing white spaces from each words
    for (; raw_data[i]; i++)
    {
        char *demo = (char *)malloc(sizeof(char) * BUFFER_SIZE);
        int id = 0;

        for (int j = 0; j < strlen(raw_data[i]); j++)
        {

            if (raw_data[i][j] != ' ' or raw_data[i][j] != '\n')
                demo[id++] = raw_data[i][j];
        }

        words[i] = demo;
    }

    // words[i] = NULL;

    return words;
}

char *strip(char *word)
{

    int id = 0;
    char *demo = (char *)malloc(sizeof(char) * 1024);

    for (int i = 0; i < strlen(word); i++)
    {
        // if ( isalpha(word[i]) || isalnum(word[i]) || ispunct(word[i]) ){
        if (isgraph(word[i]))
        {
            demo[id++] = word[i];
        }
    }

    demo[id] = '\0';

    return demo;
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

int main()
{

    // 0 - stdin
    // 1 - stdout
    // 2 - stderr

    int tmpin = dup(0);
    int tmpout = dup(1);

    // input
    printf(">> ");
    char *data = (char *)malloc(sizeof(char) * 1024);
    char **cmd = (char **)malloc(sizeof(char) * 1024);
    data = take_user_input();
    cmd = str_tokenize(data, '|');

    int i = 0;
    pid_t pid[100];
    int fd[100][2];

    while (*cmd)
    {
        char **token = str_tokenize(*cmd, ' ');
        char **singleCMD = removeWhiteSpace(token);

        if (strlen(*singleCMD) != 0)
        {
            char *command = strip(singleCMD[0]);

            int pid = fork();
            if (pid == 0)
            {
                printf("child process..%s\n", command);
                if (execvp(command, singleCMD) == -1)
                {
                    perror("Execution failed\n");
                }
                exit(EXIT_FAILURE);
            }
        }

        cmd++;
    }
}