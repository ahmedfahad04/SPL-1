#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#define BUFFER_SIZE 1024

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

size_t strlen(const char *str)
{

    size_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    return len;
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

    words[i] = NULL;

    return words;
}

char *strip(char *word)
{

    int id = 0;
    char *demo = (char *)malloc(sizeof(char) * 1024);

    int stflag = 0, endflag = 0;

    for (int i = 0; i < strlen(word); i++)
    {

        if (word[i] == ' ' and i == 0)
            continue;
        else if (word[i] == ' ' and i == strlen(word) - 1)
            continue;
        else
            demo[id++] = word[i];
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

int strlen2(char **str)
{
    int len = 0;

    while (*str)
    {
        len++;
        str++;
    }

    return len;
}

char *strcpy(const char *from)
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

char **strcpy2(char **str)
{
    char **words = (char **)malloc(sizeof(char) * BUFFER_SIZE);
    int i = 0;

    // removing white spaces from each words
    for (; str[i]; i++)
    {
        char *demo = (char *)malloc(sizeof(char) * BUFFER_SIZE);
        int id = 0;

        for (int j = 0; j < strlen(str[i]); j++)
        {
            demo[id++] = str[i][j];
        }

        words[i] = demo;
    }

    words[i] = NULL;

    return words;
}

int main()
{

    printf(">> ");
    char *data = (char *)malloc(sizeof(char) * 1024);
    char **cmd = (char **)malloc(sizeof(char) * 1024);
    data = take_user_input();
    cmd = str_tokenize(data, '|');

    char *simpleCMD[10];

    // for (int i = 0; i < 10; i++)
    // {
    //     simpleCMD[i] = (char *)malloc(sizeof(char) * 1024);
    // }
    int size = 0;

    while (*cmd)
    {
        simpleCMD[size++] = *cmd;
        cmd++;
    }

    pid_t pid[100];
    int fd[100][2];

    for (int i = 0; i < size; i++)
    {
        char *currCMD = strip(simpleCMD[i]);
        char **cmd = str_tokenize(currCMD, ' ');

        if (i == 0)
        { // first cmd
            puts("FIRST");
            // pipe 1
            if (pipe(fd[i]) == -1)
            {
                printf("Error creating pipe;");
            }

            // cmd 1
            int x = fork();
            pid[i] = x;
            if (pid[i] == 0)
            {
                // child process; write end
                dup2(fd[i][1], STDOUT_FILENO);
                close(fd[i][1]);
                close(fd[i][0]);

                if (execvp(cmd[0], cmd) == -1)
                {
                    printf("Execution failed..#B: %d", i);
                }
                // execlp("ls", "ls", NULL);
            }
            waitpid(pid[i], NULL, 0);
        }

        else if (i == size - 1)
        { // last cmd
          // cmd 4
            puts("LAST");
            int x = fork();
            pid[i] = x;
            if (pid[i] == 0)
            {
                // child process; read end
                dup2(fd[i - 1][0], STDIN_FILENO);
                close(fd[i - 1][1]);
                close(fd[i - 1][0]);

                if (execvp(cmd[0], cmd) == -1)
                {
                    printf("Execution failed..#A: %d", i);
                }
            }

            close(fd[i - 1][1]);
            close(fd[i - 1][0]);
            waitpid(pid[i], NULL, 0);
        }

        else
        {
            // puts("OTHERS");
            //  pipe 2
            if (pipe(fd[i]) == -1)
            {
                printf("Error creating pipe;");
            }

            // cmd 2
            int x = fork();
            pid[i] = x;
            if (pid[i] == 0)
            {
                // child process; read end
                dup2(fd[i - 1][0], STDIN_FILENO);
                close(fd[i - 1][1]);
                close(fd[i - 1][0]);

                if (i != size - 1)
                {
                    // // write end
                    dup2(fd[i][1], STDOUT_FILENO);
                    close(fd[i][1]);
                    close(fd[i][0]);
                }

                if (execvp(cmd[0], cmd) == -1)
                {
                    printf("Execution failed..#C: %d", i);
                }
            }

            // erpor ar fd er kaj nai tai etake ekhanei off korte hobe
            close(fd[i - 1][1]);
            close(fd[i - 1][0]);
            waitpid(pid[i], NULL, 0);
        }
    }
}