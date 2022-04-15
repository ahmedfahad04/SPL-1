#include <sys/socket.h>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <iostream>
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

bool strcontain(const char *data, const char *substr)
{

    int j = 0, len = 0, flag = 0;
    for (int i = 0; i < strlen(data); i++)
    {
        if (data[i] == substr[j])
        {
            j++;
            len++;
        }
        else
        {
            if (len == strlen(substr))
            {
                flag = 1;
                break;
            }
            j = 0;
            len = 0;
        }
    }

    if (len == strlen(substr))
        flag = 1;

    return flag;
}

struct ShellCommands
{
    char *simpleCommand[50];
    char *infile;
    char *outfile;
    char *background;
};

int count_fds(int k)
{
    int maxfd = getdtablesize();
    int openfds;
    int fd;
    int i;

    openfds = k;

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
        return maxfd;
    close(fd);

    std::cout << "MAXFD: " << maxfd << "\n";

    // for (i = 0; i < maxfd; i++) {
    //         if (dup2(i, fd) != -1) {
    //                 openfds++;
    //                 std::cout << "FD: " << openfds << "\n";
    //                 close(fd);
    //         }
    // }

    return openfds;
}

void execute(int size, struct ShellCommands command)
{
    pid_t pid[100];
    int fd[100][2];
    

    for (int i = 0; i < size; i++)
    {
        char *currCMD = strip(command.simpleCommand[i]);
        char **cmd = str_tokenize(currCMD, ' ');
        int fdout, file;

         // this is input redirection...
        if (command.infile)
        {
            printf("READING>>>\n");
            int f2 = open(command.infile, O_RDONLY, 0777);
            if (f2 == -1)
            {
                puts("Error reading file");
            }

            int fdin = dup2(f2, 0);
            close(f2);
        }

        // this is output redirection....
        if (command.outfile)
        {
            printf("WRITING>>>\n");
            file = open(command.outfile, O_WRONLY | O_CREAT, 0777);
            if (file == -1)
            {
                puts("Error writing file");
            }

            // printf("Previous FD: %d\n", file);

            fdout = dup2(file, 1); // permanently converted the stdout...

            close(file);
        }


       
        if (i == 0)
        {
            // puts("FIRST");

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

                if (i != size - 1) // if we enter only a single command
                {
                    // child process; write end
                    dup2(fd[i][1], STDOUT_FILENO);
                    close(fd[i][1]);
                    close(fd[i][0]);
                }

                if (execvp(cmd[0], cmd) == -1)
                {
                    printf("Execution failed..#B: %d", i);
                }
            }
            waitpid(pid[i], NULL, 0);
        }

        else if (i == size - 1)
        { // last cmd
          // cmd 4
            // puts("LAST");

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

    return;
}

int main()
{

    int save_in, save_out;

    save_in = dup(STDIN_FILENO);
    save_out = dup(STDOUT_FILENO);

    while (1)
    {

        printf(">> ");

        dup2(save_in, STDIN_FILENO);
        dup2(save_out, STDOUT_FILENO);

        char *data = (char *)malloc(sizeof(char) * 1024);
        char **cmd = (char **)malloc(sizeof(char) * 1024);
        char **red = (char **)malloc(sizeof(char) * 1024);
        data = take_user_input();

        struct ShellCommands command;
        int size = 0;

        command.outfile = NULL;
        command.infile = NULL;

        printf("--> %s ===> %d\n", data, strlen(data));

        // pipelined command
        if (strcontain(data, "|"))
        {
            cmd = str_tokenize(data, '|');
        }
        else
            *cmd = data; // only a single command

        while (*cmd)
        {
            puts(*cmd);
            if (strcontain(*cmd, ">") or strcontain(*cmd, "<"))
            {

                // cat > infile < outfile
                // cat > infile  ------------------ Output redirection
                if (strcontain(*cmd, "<"))
                {
                    red = str_tokenize(*cmd, '<');
                    char *p1 = strip(red[0]);
                    char *p2 = strip(red[1]);

                    // case 1 -------- echo hello < infile > outfile
                    if (strcontain(p2, ">"))
                    {
                        red = str_tokenize(p2, '>');
                        command.infile = red[0];
                        command.outfile = red[1];
                    }
                    else
                    {
                        command.infile = p2;
                    }

                    // case2 ---------- echo hello > infile < outfile
                    if (strcontain(p1, ">"))
                    {
                        red = str_tokenize(p1, '>');
                        command.simpleCommand[size++] = red[0];
                        command.outfile = red[1];
                    }
                    else
                    {
                        command.simpleCommand[size++] = p1;
                    }
                }

                else if (strcontain(*cmd, ">"))
                {
                    red = str_tokenize(*cmd, '>');
                    char *p1 = strip(red[0]);
                    char *p2 = strip(red[1]);

                    // case 1---------- echo hello > infile < outfile
                    if (strcontain(p2, "<"))
                    {
                        red = str_tokenize(p2, '<');
                        command.outfile = red[0];
                        command.infile = red[1];
                    }
                    else
                    {
                        command.outfile = p2;
                    }

                    // case 2 -------- echo hello < infile > outfile
                    if (strcontain(p1, ">"))
                    {
                        red = str_tokenize(p1, '>');
                        command.simpleCommand[size++] = red[0];
                        command.outfile = red[1];
                    }
                    else
                    {
                        command.simpleCommand[size++] = p1;
                    }
                }

                else
                {
                    command.infile = NULL;
                    command.outfile = NULL;
                }
            }
            else
            {
                command.simpleCommand[size++] = *cmd;
            }
            cmd++;
        }

        // parsing ends.....

        printf("STDOUT: %s\n", command.infile);
        printf("STDIN: %s\n", command.outfile);
        printf("SIZE: %d\n", size);

        // std::thread t1(execute, size, command);
        // t1.join();
        execute(size, command);
    }
}