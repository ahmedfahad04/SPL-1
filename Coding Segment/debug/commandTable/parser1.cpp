#include <bits/stdc++.h>
#define BUFFER_SIZE 1024
using namespace std;

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

struct ShellCommands
{
    char *simpleCommand[50];
    char *infile;
    char *outfile;
    char *background;
};

int main()
{

    printf(">> ");
    char *data = (char *)malloc(sizeof(char) * 1024);
    char **cmd = (char **)malloc(sizeof(char) * 1024);
    char **red = (char **)malloc(sizeof(char) * 1024);

    data = take_user_input();
    struct ShellCommands command;
    int size = 0;
    command.outfile = NULL;
    command.infile = NULL;

    // pipelined command
    if (strcontain(data, "|"))
    {
        cmd = str_tokenize(data, '|');
    }
    else
        *cmd = data; // only a single command

        

    while (*cmd)
    {
        if (strcontain(*cmd, ">") or strcontain(*cmd, "<"))
        {

            // cat > infile < outfile
            // cat > infile  ------------------ Output redirection
            if (strcontain(*cmd, "<"))
            {
                red = str_tokenize(*cmd, '<');
                char *p1 = red[0];
                char *p2 = red[1];

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
                char *p1 = red[0];
                char *p2 = red[1];

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

    // output
    for (int i = 0; i < size; i++)
    {
        puts(command.simpleCommand[i]);
    }

    printf("STDOUT: %s\n", command.outfile);
    printf("STDIN: %s\n", command.infile);
    printf("SIZE: %d\n", size);
}