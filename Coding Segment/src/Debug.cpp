#include <cstdio>
#include <stdlib.h>
#include <cstdio>
#include <dirent.h>
#include <stdlib.h>
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
#include <math.h>
#include <signal.h>

#define BUFFER_SIZE 1024

// ANSI COLOR CODES
#define FONT_BLK "\u001b[30m"
#define FONT_RED "\u001b[31m"
#define FONT_GRN "\u001b[32m"
#define FONT_YEL "\u001b[33m"
#define FONT_BLU "\u001b[34m"
#define FONT_MAG "\u001b[35m"
#define FONT_CYN "\u001b[36m"
#define FONT_WHT "\u001b[37m"
#define RESET "\u001b[0m"

#define FONT_DARK_BLK "\u001b[30m;1m"
#define FONT_DARK_RED "\u001b[31m;1m"
#define FONT_DARK_GRN "\u001b[32m;1m"
#define FONT_DARK_YEL "\u001b[33m;1m"
#define FONT_DARK_BLU "\u001b[34m;1m"
#define FONT_DARK_MAG "\u001b[35m;1m"
#define FONT_DARK_CYN "\u001b[36m;1m"
#define FONT_DARK_WHT "\u001b[37m;1m"

#define BG_BLK "\u001b[40m"
#define BG_RED "\u001b[41m"
#define BG_GRN "\u001b[42m"
#define BG_YEL "\u001b[43m"
#define BG_BLU "\u001b[44m"
#define BG_MAG "\u001b[45m"
#define BG_CYN "\u001b[46m"
#define BG_WHT "\u001b[47m"

#define BG_DARK_BLK "\u001b[40m;1m"
#define BG_DARK_RED "\u001b[41m;1m"
#define BG_DARK_GRN "\u001b[42m;1m"
#define BG_DARK_YEL "\u001b[43m;1m"
#define BG_DARK_BLU "\u001b[44m;1m"
#define BG_DARK_MAG "\u001b[45m;1m"
#define BG_DARK_CYN "\u001b[46m;1m"
#define BG_DARK_WHT "\u001b[47m;1m"

// BK TREE NODE
struct node
{
    int data;
    char *word;
    struct node *left;
    struct node *right;
};

// COMMAND STRUCT
struct ShellCommands
{
    char *simpleCommand[50];
    char *infile;
    char *outfile;
    char *background;
    char size = 0;
};
void executenew(int size, struct ShellCommands command);

// COMMAND AUTOCOMPLETION
struct cmdFreq
{
    char *cmd;
    int freq;
    int prev;
};
void frequencyCalculator(char *command, FILE *save);
void assembleFreqOutput();
int generateAutoCommand(char *cmd);
void updateCmdFrequency();
int count(char *data[], char *info, int size);
void mergeAndExecute(char *command, char **data);
void commandSuggestion(int flag, char **args);
char *AutoCommandCompletion(int flag, char *args);

// HISTORY
struct history
{
    char *cmd;
    int order;
};
int historySerialLocator();
void writeHistory(int size, struct history ht[]);
char *readHistory(int serial = -1);
char *showParticularHistory(char *cmd);

// MAIN LOOP
void eventLoop(char *code = "", char *type = "");
void eventLoopWithColors(char *ch = "", char *type = "");

// COMMAND PROMPT
void prompt();
void promptWithColors(char *code, char *colorType);
char *takeUserInput(char *code = "", char *colorType = "", int fsl = 0, FILE *fp = NULL);
char **strtokenize(char *ch, char sep);
void sig_handler(int signum);

// BASIC STRING OPERATIONS
size_t strlen(const char *str);
bool strcmp(const char *a, const char *b);
int strlen2(char **str);
char *strcpy(const char *b);
char *strchr(const char *a, const char ch);
char *strcatt(const char *with, const char *str);
char *strreplace(const char *info, const char *with, const char *str);
bool strcontain(char *data, char *substr);
char **removeWhiteSpace(char **raw_data);
void PieTable(char *neddle, int neddle_len, int *LPS);
int strsubstr(char *neddle, char *heystack);
char **strsplit(char *find, char *text);
char *strip(char *word);
char *showCode();
char *selectBGColor(char *args);
char *selectFGColor(char *args);
char *numToStr(int num);
void userManual();
bool wildcardmatching(char *str, char *pat, int slen, int plen);

// COMMAND EXECUTION
void cmd_execute(char **args);
void change_directory(char *path);
char *current_directory();
char *hostName();
char *userName();
void execute(char **args);
bool isBuiltInCmd(char *cmd);
char *getCurrentDirectory();
void BKTreeGeneration(char *cmd);
void findExeFileName(char *cmd);
void saveInfo();
void executePipelinedCommands(int size, char *simpleCMD[], struct ShellCommands command);
char **checkForWildCards(char **data);
void setAlias(char *cmd, char *alias);
void aliasCommands(char **words);
char **checkForAliasing(char **cmd);
char *getAlias(char *data);
struct ShellCommands parser(char *data);

// ------------------------------ IMPLEMENTATION -----------------------------------

size_t strlen(const char *str)
{
    // calculate the length of a string

    size_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    return len;
}

// char ** merge(char ** words, int start, int end){

// }

bool strcmp(const char *a, const char *b)
{
    // compare two strings named a and b

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

char *strcpy(const char *from)
{
    // make a copy of 'from' string

    int len = strlen(from);
    char copiedData[len + 1];

    int i;
    for (i = 0; i < len; i++)
    {
        if (from[i] == '\n')
        {
            copiedData[i] = '\0';
            break;
        }
        else
            copiedData[i] = from[i];
    }

    copiedData[i] = '\0';

    char *to = copiedData;
    return to;
}

char *strcatt(const char *with, const char *str)
{
    // concatenate string 'str' with string named 'with'

    char temp[500];
    int i = 0;

    while (*with != '\0')
    {
        temp[i++] = *with++;
    }

    while (*str != '\0')
    {
        temp[i++] = *str++;
    }

    temp[i] = '\0';

    char *res = temp; // always try to declare *copiedData -> this variable where you need it, don't declare at top. It might temps in wrong tempwer.

    return res;
}

int strlen2(char **str)
{
    // calculate length of a 2D string

    int len = 0;

    while (*str)
    {
        len++;
        str++;
    }

    return len;
}

char *strreplace(const char *data, const char *with, const char *str)
{

    char ans[1024];
    int start = -1, end = -1;

    int id = 0, j = 0;
    for (int i = 0; i < strlen(data); i++)
    {

        // cout << "D: " << data[i] << ", W: " << with[j] <<", I: " << i <<endl;

        if (data[i] == with[j])
        {
            if (start == -1)
                start = i;
            j++;
        }

        else if ((data[i] != with[j]) && start != -1)
        {
            end = i;
            break;
        }

        if (start == -1)
        {
            ans[++id] = data[i];
        }
    }

    id--;

    while (*str != '\0')
    {
        ans[++id] = *str++;
    }

    data += end;
    while (*data != '\0')
    {
        ans[++id] = *data++;
    }

    ans[++id] = '\0';

    char *res = ans;

    return res;
}

bool strcontain(char *data, char *substr)
{

    // check if the substring named 'substr' is present in data

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

void PieTable(char *neddle, int neddle_len, int *LPS)
{

    // this is helping function to implement KMP String matching algorithm
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

int strsubstr(char *neddle, char *heystack)
{
    // Implementation of KMP String Searching Algorithm...
    // here needle means the string to be searched and heystack means the streams of character where we'll search

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

char **strsplit(char *find, char *text)
{

    // split the string 'text' based on the string 'find'

    int pos = strsubstr(find, text);
    int len = strlen(find);
    int finalPos = pos + len;

    char **chunk = (char **)malloc(sizeof(char) * 1024);
    char *word = (char *)malloc(sizeof(char) * 1024);

    chunk[0] = find;

    int id = 0;

    for (int i = finalPos; i < strlen(text); i++)
    {
        word[id++] = text[i];
    }

    word[id] = '\0';
    chunk[1] = word;

    return chunk;
}

char *numToStr(int num)
{
    // number to String converter

    char *temp = (char *)malloc(sizeof(char) * 1024);

    int i = 0;
    while (num > 0)
    {
        int x = num % 10;
        num /= 10;
        temp[i++] = x + '0';
    }

    temp[i] = '\0';

    char *str = (char *)malloc(sizeof(char) * 1024);

    int j = 0;
    for (; j < i; j++)
    {
        str[j] = temp[i - j - 1];
        // printf("%c..\n", temp[j]);
    }

    str[j] = '\0';

    return str;
}

bool wildcardmatching(char *str, char *pattern, int textLen, int patternLen)
{

    // Find wild card matching for given string 'str' based on the pattern 'pattern'
    // here textLen

    // ==> need to check null character before . operator
    if (patternLen == 0)
    {
        if (patternLen == 0)
            return 0;
        else
            return 1;
    }

    bool table[textLen + 1][patternLen + 1];

    for (int i = 0; i <= textLen; i++)
    {
        for (int j = 0; j <= patternLen; j++)
        {
            table[i][j] = false;
        }
    }

    // initially empty stirng mathches with empty patterntern
    table[0][0] = true;

    // only * can match with empty sequence
    for (int j = 1; j <= patternLen; j++)
    {
        if (pattern[j - 1] == '*')
        {
            table[0][j] = table[0][j - 1];
        }
    }

    for (int i = 1; i <= textLen; i++)
    {
        for (int j = 1; j <= patternLen; j++)
        {

            if (pattern[j - 1] == '*')
            {
                table[i][j] = table[i - 1][j] || table[i][j - 1];
            }

            else if (pattern[j - 1] == '?' || (str[i - 1] == pattern[j - 1]))
            {
                table[i][j] = table[i - 1][j - 1];
            }

            else
                table[i][j] = false;
        }
    }

    return table[textLen][patternLen];
}

char **checkForWildCards(char **data)
{

    // check if wildcard is available in given stream of character or not

    char **newargs = (char **)malloc(sizeof(char) * 1024);
    int id = 0;

    while (*data)
    {
        if (strcontain(*data, "*"))
        {
            char *args = (char *)malloc(sizeof(char) * 1024);

            DIR *folder;
            struct dirent *entry;
            int files = 0;

            // current directory
            folder = opendir(".");

            if (folder == NULL)
            {
                perror("Unable to read directory");
            }

            while ((entry = readdir(folder)))
            {
                char *dname = entry->d_name;

                if (wildcardmatching(dname, *data, strlen(dname), strlen(*data)))
                {
                    // puts(dname);
                    args = strcatt(args, dname);
                    args = strcatt(args, " ");
                }
            }

            closedir(folder);

            char **dirs = strtokenize(args, ' ');

            while (*dirs)
            {
                if (strlen(*dirs) != 0)
                    newargs[id++] = *dirs;
                dirs++;
            }
        }
        else
        {
            newargs[id++] = *data;
        }

        data++;
    }

    // while(*newargs){
    //     printf("WILD: %s\n", *newargs);
    //     newargs++;
    // }

    return newargs;
}

struct ShellCommands parser(char *data)
{

    char **cmd = (char **)malloc(sizeof(char) * 1024);
    char **temp = (char **)malloc(sizeof(char) * 1024);

    struct ShellCommands command;
    int size = 0;

    command.outfile = NULL;
    command.infile = NULL;

    // pipelined command
    if (strcontain(data, "|"))
    {
        cmd = strtokenize(data, '|');
    }
    else
        *cmd = data; // only a single command

    while (*cmd)
    {
        if (strcontain(*cmd, ">") or strcontain(*cmd, "<"))
        {

            // cat > infile < outfile
            // cat > infile  ------------------ Output tempirection
            if (strcontain(*cmd, "<"))
            {
                temp = strtokenize(*cmd, '<');
                char *p1 = strip(temp[0]);
                char *p2 = strip(temp[1]);

                // case 1 -------- echo hello < infile > outfile
                if (strcontain(p2, ">"))
                {
                    temp = strtokenize(p2, '>');
                    command.infile = temp[0];
                    command.outfile = temp[1];
                }
                else
                {
                    command.infile = p2;
                }

                // case2 ---------- echo hello > infile < outfile
                if (strcontain(p1, ">"))
                {
                    temp = strtokenize(p1, '>');
                    command.simpleCommand[size++] = temp[0];
                    command.outfile = temp[1];
                }
                else
                {
                    command.simpleCommand[size++] = p1;
                }
            }

            else if (strcontain(*cmd, ">"))
            {
                temp = strtokenize(*cmd, '>');
                char *p1 = strip(temp[0]);
                char *p2 = strip(temp[1]);

                // case 1---------- echo hello > infile < outfile
                if (strcontain(p2, "<"))
                {
                    temp = strtokenize(p2, '<');
                    command.outfile = temp[0];
                    command.infile = temp[1];
                }
                else
                {
                    command.outfile = p2;
                }

                // case 2 -------- echo hello < infile > outfile
                if (strcontain(p1, ">"))
                {
                    temp = strtokenize(p1, '>');
                    command.simpleCommand[size++] = temp[0];
                    command.outfile = temp[1];
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

    // printf("STDOUT: %s\n", command.infile);
    // printf("STDIN: %s\n", command.outfile);
    // printf("SIZE: %d\n", size);

    command.size = size;

    return command;
}

// -------------------------------- COMMAND EXECUTION --------------------------------------

int flag = 0;

void cmd_execute(char **args)
{
    // temporarily I'll send the pure text
    // in future I'll send the tokenize text for execution
    // cmd_execute(commandLine);

    char *cmd = args[0];

    if (strcmp(cmd, "cd"))
    {
        change_directory(args[1]);
    }

    if (strcmp(cmd, "apropos"))
    {

        findExeFileName(args[1]);
    }

    if (strcmp(cmd, "color"))
    {
        // ==> need to create a help menu to show how to take input
        // color --bg red
        if (args[1] == NULL)
        {
            userManual();
            return;
        }
        else if (strcmp(args[1], "--bg"))
        {
            if (args[2] == NULL)
            {
                printf("Color Code missing...\n");
                userManual();
                return;
            }
            char *bgCode = selectBGColor(args[2]);
            eventLoopWithColors(bgCode);
        }

        // color --fg user cyn
        else if (strcmp(args[1], "--fg"))
        {
            if (args[3] == NULL || args[2] == NULL)
            {
                printf("Color Code missing...\n");
                userManual();
                return;
            }

            if (!strcmp(args[2], "user") && !strcmp(args[2], "host"))
            {
                printf("Wrong type declaration...\n");
                userManual();
                return;
            }

            char *fgCode = selectFGColor(args[3]);
            eventLoopWithColors(fgCode, args[2]);
        }

        else if (strcmp(args[1], "--help"))
        {
            // printf("Wrong command...\n");
            userManual();
        }
    }
}

void change_directory(char *path)
{
    char *tilde = "~";
    bool tildeStatus = strcmp(tilde, path);
    char *newPath;

    if (tildeStatus)
    {
        newPath = strcatt("/home/", userName());
        // printf("NEW: %s\n", newPath);

        if (chdir(newPath) != 0)
            printf("slsh: cd: %s: No such file or directory\n", newPath);
    }

    else if (strcontain(path, tilde))
    {

        newPath = strcatt("/home/", userName());
        char **splittedWords = strsplit(tilde, path);
        char *finalPath = strcatt(newPath, splittedWords[1]);

        if (chdir(finalPath) != 0)
            printf("slsh: cd: %s: No such file or directory\n", newPath);
    }

    else
    {
        if (chdir(path) != 0)
            printf("slsh: cd: %s: No such file or directory\n", path);
    }
}

char *current_directory()
{
    char cwd[1024], *addr;

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        // copy the value of cwd into char pointer addr
        addr = cwd;
    }
    else
    {
        perror("getcwd() error");
        // return 1;
    }

    return addr;
}

char *hostName()
{
    char *host = (char *)malloc(sizeof(char) * BUFFER_SIZE);

    FILE *fp;

    if ((fp = fopen("/etc/hostname", "r")) == NULL)
    {
        printf("Failed to open /etc/hostname\n");
    }

    // we need to use character array instead of pointers.
    // as pointer array of character lost the input after reading the whole file.
    char a[2000];

    while (fscanf(fp, "%s", a) != EOF)
    {
        host = a;
    }

    fclose(fp);

    return host;
}

char *userName()
{
    // we need to use character array instead of pointers.
    // as pointer array of character lost the input after reading the whole file.
    // char *currdir = current_directory();
    static char *user = (char *)malloc(sizeof(char) * BUFFER_SIZE);

    // this condition is a must
    // otherwise wrong memory is allocated and eventually it pushes to remove other variables value
    if (strlen(user) != 0)
    {
        return user;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    FILE *fp;

    if ((fp = fopen("/etc/passwd", "r")) == NULL)
    {
        printf("Failed to open /etc/passwd\n");
    }

    // I need to use getline becuase it can handle line with spaces easily
    // other file function is malfunctioning in many cases
    // read - holds the length of the line
    while ((read = getline(&line, &length, fp)) != -1)
    {
        char **chunk = strtokenize(line, ':');

        if (chunk[5] != 0)
        {
            // this following two condition is a must.
            // it's because if I don't add the first condition
            // it matches '/' with currentdir and that produce faulty results
            if (strcontain(chunk[5], "/home/") && strcontain(current_directory(), chunk[5]))
            {
                user = chunk[0];
            }
        }
    }

    fclose(fp);

    return user;
}

bool isBuiltInCmd(char *cmd)
{

    bool status = 0;

    if (strcmp(cmd, "cd"))
    {
        status = 1;
    }

    else
    {
        status = 0;
    }

    return status;
}

void execute(char **args)
{

    // ==X this is the breakpoint for not working CD option
    char *command = args[0];

    if (strcmp(command, "cd"))
    {
        cmd_execute(args);
    }

    else if (strcmp(command, "apropos"))
    {

        if (strlen2(args) == 1)
        {
            printf("Provide argument after apropos..\napropos [options..]\n");
            return;
        }

        cmd_execute(args);
    }

    else if (strcmp(command, "color"))
    {
        cmd_execute(args);
    }

    else if (strcmp(command, "alias"))
    {
        aliasCommands(args);
    }

    else if (strcmp(command, "history"))
    {
        readHistory();
    }

    else if (strcmp(command, "autocomplete"))
    {
        if (strcmp(args[1], "on"))
            flag = 1;
        else
            flag = 0;
    }

    // ==> will start from here
    // store process id
    // check if the process if child or parent
    // if it's the child process run execv()
    // if it's parent process then wait for the child process to be terminated
    else
    {

        pid_t status, process_id;

        process_id = fork();

        // child process
        if (process_id == 0)
        {
            if (execvp(args[0], args) == -1)
            {
                // printf("NEWF: %d\n", flag);
                if (flag)
                    char *CMD = AutoCommandCompletion(flag, args[0]);
                else
                    commandSuggestion(flag, args);

                // puts(CMD);

                // mergeAndExecute(CMD, args);
                // perror("Execution failed\n");
            }
            exit(0);
        }
        else if (process_id < 1)
        {
            puts("Parent process");
            perror("Process Forking Failed\n");
        }

        else
        {
            status = waitpid(process_id, NULL, 0);
            // printf("It's a parent proecss\n");
        }
    }
}

void executePipelinedCommands(int size, char *simpleCMD[], struct ShellCommands command)
{

    pid_t pid[100];
    int fd[100][2];

    size = command.size;

    for (int i = 0; i < size; i++)
    {
        char *currCMD = strip(command.simpleCommand[i]);
        char **cmd = strtokenize(currCMD, ' ');
        cmd = checkForWildCards(cmd); // checking if any wildcard pattern is available or not
        cmd = checkForAliasing(cmd);

        // ==X this is the breakpoint
        // cmd = checkForAliasing(cmd);  // checking if any alias is available or not
        int fdout, file;

        // this is input redirection...
        if (command.infile)
        {
            printf("READING>>>\n");
            int f2 = open(strip(command.infile), O_RDONLY, 0777);
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
            file = open(strip(command.outfile), O_WRONLY | O_CREAT, 0777);
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

char *getCurrentDirectory()
{

    // ==> DON'T KNOW WHY THIS IS HAPPENING
    char *dirPath, *currentDir, *extension;

    currentDir = current_directory();
    extension = strcatt("/home/", userName());

    if (strcontain(currentDir, extension))
    {
        dirPath = strreplace(currentDir, extension, "~");
    }
    else
    {
        dirPath = currentDir;
    }

    // adding new line looks cool

    return dirPath;
}

// -------------------------- TOKENIZER -------------------------

char *userFontColor = FONT_RED, *bgColor = "\u001b[230;5;m", *hostFontColor = FONT_CYN;

void promptWithColors(char *colorCode, char *colorType)
{
    char *path = getCurrentDirectory();
    char *myuser = userName();
    char *myhost = hostName();

    // ==> need to work on manual colorCode input

    if (strcmp(colorType, "user"))
    {
        userFontColor = colorCode;
    }
    else if (strcmp(colorType, "host"))
    {
        hostFontColor = colorCode;
    }
    else
    {
        bgColor = colorCode;
    }

    if (bgColor != NULL)
        printf("%s", bgColor);

    printf("\u001b[1m%s\u001b[1m%s@%s:\u001b[1m%s\u001b[1m%s", userFontColor, myuser, myhost, userFontColor, RESET);

    if (bgColor != NULL)
        printf("%s", bgColor);

    printf("\u001b[1m%s\u001b[1m%s$ \u001b[1m%s\u001b[1m%s", hostFontColor, getCurrentDirectory(), hostFontColor, RESET);

    if (bgColor != NULL)
        printf("%s", bgColor);
}

void prompt()
{
    char *path = getCurrentDirectory();
    char *myuser = userName();
    char *myhost = hostName();

    printf("%s%s@%s:%s%s", userFontColor, myuser, myhost, userFontColor, RESET);
    printf("%s\u001b[1m%s%s$ %s\u001b[1m%s", RESET, hostFontColor, getCurrentDirectory(), hostFontColor, RESET);
}

char *takeUserInput(char *colorcolorCode, char *colorType, int fsl, FILE *fp)
{
    char *buffer, *path;
    char ch;
    int location = 0, buffer_size = BUFFER_SIZE;

    // dynamically allocate memory to store the user prompt
    buffer = (char *)malloc(sizeof(char) * buffer_size);

    // check if new color colorCode is applied or not
    if (strlen(colorcolorCode) != 0)
    {
        promptWithColors(colorcolorCode, colorType);
    }
    else
        prompt();

    int quoteStart = 0;
    char *temp;

    while (1)
    {
        scanf("%c", &ch);
        if (ch == '\r')
            continue;

        if (location > buffer_size)
        {
            buffer_size += 1024;
            buffer = (char *)realloc(buffer, buffer_size);
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

            if (raw_data[i][j] != ' ')
                demo[id++] = raw_data[i][j];
        }

        words[i] = demo;
    }

    words[i] = NULL;

    return words;
}

char **strtokenize(char *ch, char sep)
{

    char *newstr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    char **raw_words = (char **)malloc(sizeof(char) * BUFFER_SIZE);

    int cnt = 0, k = 0, j = 0, qFlag = 0, changed = 0;

    // split the string into words based on spaces
    for (int i = 0;; i++)
    {
        if (ch[i] == '\"' or ch[i] == '\'')
        {
            newstr[j++] = ch[i];
            if (qFlag == 0) // means starting of a quote
            {
                qFlag = 1;
                continue;
            }

            else // means ending of a quote
            {
                qFlag = 0;
                i++;
            }
        }

        if (!qFlag)
        {
            if (((ch[i] == sep && i > 0) || (ch[i] == '\0') || (ch[i] == '\n')) && (ch[i - 1] != sep))
            {
                cnt++;
                newstr[j] = '\0';
                raw_words[k++] = newstr;
                changed = 1;
                //  printf("NEW: %s -> %d\n", newstr, qFlag);

                newstr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
                j = 0;

                if (ch[i] == '\0')
                    break;
            }

            else
            {
                newstr[j++] = ch[i];
            }
            // printf("CH: %c ", ch[i]);
        }

        else
        {
            newstr[j++] = ch[i];
        }
    }

    // raw_words[k] = NULL;
    if (changed == 0)
    {
        raw_words[0] = ch;
        raw_words[1] = NULL;
    }

    return raw_words;
}

char *strip(char *word)
{

    int id = 0;
    char *temp = (char *)malloc(sizeof(char) * 1024);

    for (int i = 0; i < strlen(word); i++)
    {

        if (word[i] == ' ' and i == 0)
            continue;
        else if (word[i] == ' ' and i == strlen(word) - 1)
            continue;
        else
            temp[id++] = word[i];
    }

    temp[id] = '\0';

    return temp;
}

// ---------------------------- COLOR MANAGEMENT -------------------------

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
// ---------------- HISTORY ----------------------------------

int historySerialLocator()
{
    char *historyFileName = strcatt(strcatt("/home/", userName()), "/.slsh_history");

    if (access(historyFileName, F_OK) != 0)
    {
        FILE *fp;
        if ((fp = fopen(historyFileName, "w")) == NULL)
        {
            puts("Failed to create History files");
        }
        fclose(fp);
    }
    else
    {

        FILE *fp;
        fp = fopen(historyFileName, "r+");

        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        int serial = 0;

        while ((read = getline(&line, &len, fp)) != -1)
        {
            char **chunks = (char **)malloc(sizeof(char) * 500);

            chunks = strtokenize(line, ': ');
            if (strlen(chunks[1]) == 0)
                continue;
            else
            {
                serial = atoi(chunks[0]);
                // printf("SL: %d\n", serial);
            }
        }

        // printf("CUR: %d\n", serial);
        fclose(fp);
        return serial;
    }
}

void writeHistory(int size, struct history ht[])
{
    char *historyFileName = strcatt(strcatt("/home/", userName()), "/.slsh_history");

    // printf("HIST: %s\n", historyFileName);
    FILE *fhist = fopen(historyFileName, "a+");

    for (int i = 0; i < size; i++)
    {
        if (ht[i].cmd[0] == '!')
            continue;
        else
            fprintf(fhist, "%d: %s\n", ht[i].order, ht[i].cmd);
    }

    fclose(fhist);
}

char *readHistory(int order)
{

    char *historyFileName = strcatt(strcatt("/home/", userName()), "/.slsh_history");

    FILE *fp = fopen(historyFileName, "r"); ///~/Desktop/SPL-1.2/Coding Segment/src/.history

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int serial = 0;

    if (order == -1)
    {
        while ((read = getline(&line, &len, fp)) != -1)
        {
            printf("%s", line);
        }
    }
    else
    {
        char *sl = numToStr(order);
        int i = 0;
        while ((read = getline(&line, &len, fp)) != -1)
        {

            char **chunks = (char **)malloc(sizeof(char) * 100);
            chunks = strtokenize(line, ':');

            if (strcmp(sl, chunks[0]))
            {

                return chunks[1];
            }
        }
    }

    return NULL;
}

char *showParticularHistory(char *input)
{

    int num = 0;
    int len = strlen(input) - 1;

    for (int i = 1; i < strlen(input); i++)
    {
        num += (input[i] - '0') * pow(10, len - i);
    }

    char *ans = readHistory(num);
    return ans;
}

// ------------------------------ COMMAND ALIASING --------------------------

void setAlias(char *cmd, char *alias)
{
    // error checking....
    // ==> also group command aliasing
    // need to check if user given name already exists or not
    // first create the file if it's not been created
    char *aliasfp = strcatt(strcatt("/home/", userName()), "/.slsh_alias");

    // printf("ALIAS: %s\n", aliasfp);
    if (access(aliasfp, F_OK) != 0)
    {
        puts("C");
        FILE *fp3;
        if ((fp3 = fopen(aliasfp, "w+")) == NULL)
        {
            puts("Failed to create aliasfp files");
        }
        fclose(fp3);
    }

    FILE *f1;

    if ((f1 = fopen(aliasfp, "a+")) == NULL)
    {
        puts("Failed to open aliasfp file");
    }

    fprintf(f1, "%s %s\n", cmd, alias);
    fclose(f1);
}

void aliasCommands(char **words)
{

    char *aliasfp = strcatt(strcatt("/home/", userName()), "/.slsh_alias");
    char **refactor = (char **)malloc(sizeof(char) * 500);

    if (strlen2(words) == 1)
    {
        char s;

        FILE *fp3;
        if ((fp3 = fopen(aliasfp, "r")) == NULL)
        {
            puts("Failed to create aliasfp files");
        }

        while ((s = fgetc(fp3)) != EOF)
        {
            printf("%c", s);
        }
        fclose(fp3);

        return;
    }

    if (strcmp(words[0], "alias"))
    {
        refactor = strtokenize(words[1], '=');
        // puts(refactor[0]); // ls
        // puts(refactor[1]); // list
        setAlias(refactor[0], refactor[1]);
    }
}

char *removeQuotes(char *str)
{
    char *editedStr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    int i, k = 0;

    for (i = 0; str[i]; i++)
    {
        if (str[i] == '\'' or str[i] == '\"')
            continue;
        else
            editedStr[k++] = str[i];
    }

    editedStr[k] = '\0';
    return editedStr;
}

char **checkForAliasing(char **data)
{

    char *aliasfp = strcatt(strcatt("/home/", userName()), "/.slsh_alias");

    if (access(aliasfp, F_OK) != 0)
    {
        FILE *fp3;
        if ((fp3 = fopen(aliasfp, "w+")) == NULL)
        {
            puts("Failed to create aliasfp files");
        }
        fclose(fp3);
    }

    char *newargs[500];
    char **chunks = (char **)malloc(sizeof(char) * 500);
    int id = 0;

    while (*data)
    {

        if (id == 0)
        {
            FILE *f2;
            f2 = fopen(aliasfp, "r");

            char *line = NULL;
            size_t len = 0;
            ssize_t read;
            int flag = 1;

            while ((read = getline(&line, &len, f2)) != -1)
            {
                chunks = strtokenize(line, ' ');

                int wordLen = strlen2(chunks);

                if (strcmp(chunks[wordLen - 2], *data))
                {
                    // printf("ANS: %s\n", chunks[wordLen-2]);
                    // printf(">> %s\n", removeQuotes(chunks[0]));

                    for (int i = 0; i < wordLen - 2; i++)
                    {
                        newargs[id++] = chunks[i];
                        // printf("NEW STR: %s\n", chunks[i]);
                    }

                    flag = 0;
                }
                // puts(chunks[0]);
                // puts(chunks[1]);
                // printf("DATA: %s----flag: %d\n", *data, flag);
            }

            // free(chunks);

            if (flag)
                newargs[id++] = removeQuotes(*data);
            fclose(f2);
        }

        else
        {
            newargs[id++] = removeQuotes(*data);
        }

        // printf("--DATA: %s\n", newargs[id-1]);

        data++;
    }

    // free(newargs);
    newargs[id] = NULL;
    // printf("NEW CMD: %s\n", strtokenize(*newargs, ' '));    // will start from here
    char **ans = newargs;
    return ans;
}

// --------------------- COMMAND AUTOCOMPLETION --------------------

void updateCmdFrequency()
{

    FILE *currFrq, *temp;
    struct cmdFreq unMatchedCMD[1000];
    char *distinctCMD[1000];
    int distinctCounter[1000] = {0};
    int id = 0;

    if ((currFrq = fopen(".tempfqr", "r")) == NULL)
    {
        puts("Failed to Open tmpFreqency file");
    }

    if ((temp = fopen(".cmdFrequency", "w")) == NULL)
    {
        puts("Failed to Open Cmd Freqency file");
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read1;
    int newCounter = 0;
    int dsize = 0;
    char **chunks;

    // let's fetch the distinct command
    while ((read1 = getline(&line, &len, currFrq)) != -1)
    {
        chunks = (char **)malloc(sizeof(char) * 100);
        chunks = strtokenize(line, ' ');

        int isExist = count(distinctCMD, chunks[1], dsize);

        if (isExist == -1)
        {
            distinctCMD[dsize] = chunks[1];
            distinctCounter[dsize++] = atoi(chunks[0]);
        }
        else
        {
            distinctCounter[isExist] += atoi(chunks[0]);
        }
    }

    // test run
    for (int i = 0; i < dsize; i++)
    {

        // printf("Distinct CMD: %s, CNT: %d\n", distinctCMD[i], distinctCounter[i]);

        len = 0;
        *line = NULL;
        ssize_t read;

        // first read the cmd feq file to get the current freq of specific command "CMD"
        while ((read = getline(&line, &len, currFrq)) != -1)
        {
            chunks = (char **)malloc(sizeof(char) * 100);
            chunks = strtokenize(line, ' ');

            // puts(chunks[1]);
            // puts(chunks[0]);

            if (strcmp(chunks[1], strcpy(distinctCMD[i])))
            {
                int cnt = atoi(chunks[0]);
                distinctCounter[i] += cnt;
            }
            else // no need
            {
                unMatchedCMD[id].cmd = chunks[1];
                unMatchedCMD[id++].freq = atoi(chunks[0]);
            }
        }

        if (distinctCounter[i])
        {
            fprintf(temp, "%d %s\n", distinctCounter[i], strcpy(distinctCMD[i]));
        }
    }

    // also add the new freq
    // newCounter += newFreq;

    // temp close both file
    fclose(currFrq);
    fclose(temp);

    return;
}

void frequencyCalculator(char *command, FILE *save)
{

    FILE *fp;

    // ==> becareful about file path name

    if ((fp = fopen("/home/ahmedfahad/.bash_history", "r")) == NULL)
    {
        printf("Failed to open history file");
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int counter = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        char **chunks = (char **)malloc(sizeof(char) * 100);
        char *simplecmd = (char *)malloc(sizeof(char) * 100);

        chunks = strtokenize(line, ' ');
        simplecmd = chunks[0];
        // will handle case of ./run -> commands

        // puts(strip(simplecmd[0]));
        // printf(">> %s\n", command);

        if (strcmp(strcpy(command), strip(simplecmd)))
        {
            counter++;
        }
    }

    fclose(fp);

    // need to think do we need this counter condition??
    if (counter > 0)
        fprintf(save, "%d %s\n", counter, strcpy(command));
}

int count(char *data[], char *info, int size)
{

    for (int i = 0; i < size; i++)
    {
        if (strcmp(data[i], info))
            return i;
    }

    return -1;
}

int generateAutoCommand(char *cmd)
{

    FILE *fp;

    if ((fp = fopen(".cmdFrequency", "r+")) == NULL)
    {
        puts("FILE cmd frequency not found");
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int counter = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        char **chunks = (char **)malloc(sizeof(char) * 100);
        chunks = strtokenize(line, ' ');

        if (strcmp(strcpy(cmd), strip(chunks[1])))
        {
            return atoi(chunks[0]);
        }
    }

    fclose(fp);

    return 0;
}

void mergeAndExecute(char *command, char **data)
{

    puts("INSIDE MERGE");
    puts(command);

    char *newargs[500];
    int id = 0;

    while (*data)
    {
        if (id == 0)
        {
            newargs[id++] = command;
        }
        else
        {
            newargs[id++] = *data;
        }

        puts(*data);
        data++;
    }

    // free(newargs);
    newargs[id] = NULL;

    execute(newargs);
}

// ------------------------------- COMMAND SUGGESTION ---------------------------

#define DELETE -1
#define INSERT -2
#define SUBSTITUE -3
#define UNCHANGEditDistance -4
#define MAXSIZE 10005

int c[MAXSIZE][MAXSIZE], b[MAXSIZE][MAXSIZE], tolerance = -1;
int m, n, totalCommandCount = 0;
FILE *fp;
struct cmdFreq suggestions[1000];
struct node *root;
char *newargs[100], *rootWord;

char **readCMDOutput(char *cmd)
{
    FILE *p;
    int ch, buffer_size = 100024;
    size_t length = 0;
    ssize_t read;

    char *line = (char *)malloc(sizeof(char) * 1024);
    char **wordArr = (char **)malloc(sizeof(char) * buffer_size);

    p = popen(cmd, "r"); /* Unix */

    if (p == NULL)
    {
        puts("Unable to open process");
    }

    int i = 0;
    while ((read = getline(&line, &length, p)) != -1)
    {
        wordArr[i++] = line;
        line = (char *)malloc(sizeof(char) * 1024);
    }

    wordArr[i] = NULL;
    totalCommandCount = i;
    pclose(p);

    return wordArr;
}

void EditDistance(char *x, char *y, int row, int col)
{
    // initialize
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            c[i][j] = 0;
            b[i][j] = 0;
        }
    }

    for (int i = 0; i < row; i++)
    {
        c[0][i] = i;
        b[0][i] = -2;
    }
    for (int i = 0; i < row; i++)
    {
        c[i][0] = i;
        b[i][0] = -1;
    }

    // calculation
    for (int i = 1; i < row; i++)
    {

        for (int j = 1; j < col; j++)
        {
            int subs = c[i - 1][j - 1];
            int del = c[i - 1][j];
            int insert = c[i][j - 1];

            // cout << "X: " << x[i-1] << ", Y: " << y[i-1] << endl;

            if (x[i - 1] == y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1];
                b[i][j] = UNCHANGEditDistance;
            }

            else
            {
                int m1 = std::min(subs, del);
                int minimum = std::min(m1, insert);

                // cout << x[i] << " " << y[j] << endl;
                if (minimum == subs)
                {
                    // min = substitute
                    c[i][j] = c[i - 1][j - 1] + 1;
                    b[i][j] = SUBSTITUE;
                    // cout << "SUBSTITUTE\n";
                }

                else if (minimum == c[i][j - 1])
                {
                    // min = insert
                    c[i][j] = c[i][j - 1] + 1;
                    b[i][j] = INSERT;
                    // cout << "INSERT\n";
                }

                else
                {
                    // min = del
                    c[i][j] = c[i - 1][j] + 1;
                    b[i][j] = DELETE;
                    // cout << "DEL\n";
                }
            }
        }
    }
}

struct node *createNode(int value, char *info)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));

    p->data = value;
    p->word = info;
    p->left = NULL;
    p->right = NULL;

    return p;
}

void addNode(struct node *parent, int value, char *info)
{

    if (value <= parent->data)
    { // left node
        if (parent->left == NULL)
        {
            struct node *leftnode = createNode(value, info);
            parent->left = leftnode;
        }
        else
        {
            addNode(parent->left, value, info);
        }
    }
    else
    {
        if (parent->right == NULL)
        {
            struct node *rightnode = createNode(value, info);
            parent->right = rightnode;
        }
        else
        {
            addNode(parent->right, value, info);
        }
    }

    return;
}

void printTree(struct node *head, char *keyword, FILE *fp, int &id, int flag)
{

    if (head == NULL)
    {
        return;
    }

    else
    {

        printTree(head->left, keyword, fp, id, flag);

        if (head->data <= 3 && (strlen(head->word) >= strlen(keyword)))
        {
            // printf("***FLAG: %d", flag);

            if (flag)
            {
                frequencyCalculator(head->word, fp);
                updateCmdFrequency(); // ==> here is the issue
                int status = generateAutoCommand(head->word);

                if (status)
                {

                    // printf("    command -> %s", head->word);
                    // showValue(head->word);
                    suggestions[id].cmd = head->word;
                    suggestions[id++].freq = status;
                }
            }
            else
            {
                // ==> changes here
                printf("    command -> %s", head->word);
            }
        }

        printTree(head->right, keyword, fp, id, flag);
    }
}

void getSuggestedCommand(char *currentCommand, char *&cmd, int size)
{
    int maxcnt = 0;

    for (int i = 0; i < size; i++)
    {
        int cnt = suggestions[i].freq;
        if (cnt > maxcnt)
        {
            maxcnt = cnt;
            cmd = strcpy(suggestions[i].cmd);
            printf("slsh: Correct \'%s%s%s\' to \'%s%s%s\'\n", FONT_RED, currentCommand, RESET, FONT_GRN, cmd, RESET);
        }

        // printf("CMD: %s, CNT: %d\n", strcpy(suggestions[i].cmd), suggestions[i].freq);
    }
}

void commandSuggestion(int flag, char **args)
{
    int cmdID = 0;
    char *command = args[0];
    BKTreeGeneration(command);

    printf("Command \'%s\' not found, did you mean: \n", rootWord);
    printTree(root, rootWord, fp, cmdID, flag);
    printf("Try: sudo apt install <deb name>\n");

    exit(EXIT_FAILURE);
}

char *AutoCommandCompletion(int flag, char *args)
{

    int i = 0, cmdID = 0;

    BKTreeGeneration(args);
    // printf("CMD: %s\n", args);

    // ==> Will start from HERE
    struct cmdFreq freq[100];

    if ((fp = fopen(".tempfqr", "a")) == NULL)
    {
        puts("Failed to open .tempfqr file");
    }

    // printf("ROOTWORD: %s\n", rootWord);
    // printf("FLAG: %d\n", flag);
    printTree(root, rootWord, fp, cmdID, flag);

    // puts("SECOND");

    char *CMD = (char *)malloc(sizeof(char) * 500);
    getSuggestedCommand(args, CMD, cmdID);
    // puts(CMD);

    fclose(fp);

    return CMD;
}

void BKTreeGeneration(char *allArgs)
{

    // puts("INSIDE BK TREE");
    rootWord = allArgs;

    root = createNode(10, rootWord); // root value

    char **allCMDs = readCMDOutput("ls /usr/bin");
    char **temp = allCMDs;

    while (*temp)
    {

        m = strlen(*temp) + 1;
        n = strlen(rootWord) + 1;

        EditDistance(*temp, rootWord, m, n);

        int EdgeValue = c[m - 1][n - 1];
        if (EdgeValue <= 3 or (m == n))
            addNode(root, EdgeValue, *temp);

        temp++;
    }

    // puts(rootWord);
}

void findExeFileName(char *cmd)
{
    printf("Executable file(s) of \"%s\" are: \n", cmd);

    char *path =
        "ls /usr/bin;"
        "ls /usr/sbin; ls /sbin; ls /usr/local/sbin; ls /bin;"
        "ls /usr/games; ls /usr/local/games; ls /snap/bin; ls /snap/bin";

    char **exeFilePath = readCMDOutput(path);

    while (*exeFilePath)
    {

        int flag = strsubstr(cmd, *exeFilePath);

        if (flag >= 0)
        {

            // Here we'll try to color the searched word.....

            char *newword = strip(*exeFilePath);
            // char **words = strsplit(cmd, newword);

            // while(*words){
            //     printf(">> %s\n", *words);
            //     words++;
            // }

            // // for(int i=0; i<strlen(fileName); i++){

            // //     // if(i <= coloredStrLen) printf("\u001b[31%c\u001b[0m", exeFilePath[i]);
            // //     // else printf("%c", fileName[i]);
            // // }

            printf("%s", *exeFilePath);
            break;
        }

        exeFilePath++;
    }
}

// ----------------------------- SLSH ------------------------

void restart(int sig)
{
    puts("Start again");
    eventLoop();
}

void eventLoopWithColors(char *cmd, char *type)
{

    char *BGCode, *FGCode;

    if (cmd == NULL)
    {
        // perror("Wrong color code\n");
        return;
    }

    if (strcmp(type, "user") || strcmp(type, "host"))
    {
        FGCode = cmd;
        eventLoop(FGCode, type);
    }

    else
    {
        BGCode = cmd;

        if (BGCode != NULL)
            printf("%s", BGCode);

        eventLoop(BGCode);
    }
}

void eventLoop(char *colorFlag, char *colorType)
{
    fprintf(stdout, "\e[1;1H\e[2J");

    char *commandLine, **tokens, **filtered_tokens;
    commandLine = (char *)malloc(sizeof(char) * 500);

    // history
    struct history ht[1000];
    int historyCounter = 0;
    int historySerial = historySerialLocator() + 1;
    int saveInputFileDescriptor, saveOutputFileDescriptor;

    saveInputFileDescriptor = dup(STDIN_FILENO);
    saveOutputFileDescriptor = dup(STDOUT_FILENO);

    do
    {

        dup2(saveInputFileDescriptor, STDIN_FILENO);
        dup2(saveOutputFileDescriptor, STDOUT_FILENO);

        commandLine = takeUserInput(colorFlag, colorType);
        commandLine = strip(commandLine);
        ht[historyCounter].cmd = commandLine;
        ht[historyCounter++].order = historySerial++;

        // ==> control ctrl+C button
        // signal(SIGINT, &restart);

        // checking for pipelined and IO redirected commands
        int flag = 0;
        for (int i = 0; i < strlen(commandLine); i++)
        {
            if (commandLine[i] == '|' or commandLine[i] == '>' or commandLine[i] == '<')
            {
                flag = 1;
                break;
            }
        }

        // ==> will start from here
        if (flag)
        {
            filtered_tokens = strtokenize(commandLine, '|');
            // filtered_tokens = checkForAliasing(filtered_tokens);

            char *simpleCMD[100];
            int cmdCounter = 0;

            while (*filtered_tokens)
            {
                // filtered_tokens = checkForWildCards(filtered_tokens);
                // puts(*filtered_tokens);
                simpleCMD[cmdCounter++] = *filtered_tokens;
                filtered_tokens++;
            }

            struct ShellCommands command = parser(commandLine);
            executePipelinedCommands(cmdCounter, simpleCMD, command);
        }
        else
        {

            // ==> ----- CAREFUL -----
            if (commandLine[0] == '!')
            {
                commandLine = showParticularHistory(commandLine);
            }
            // ----- CAREFUL -----

            tokens = strtokenize(commandLine, ' ');
            filtered_tokens = checkForWildCards(tokens);
            filtered_tokens = checkForAliasing(tokens);

            if (strcmp(filtered_tokens[0], "exit"))
            {
                puts(RESET);
                fprintf(stdout, "\e[1;1H\e[2J");
                break;
            }

            printf("EXE: %s\n", filtered_tokens[0]);
            // printf("LENGTH: %s\n", strlen2(filtered_tokens));
            execute(filtered_tokens);
        }

    } while (1);

    writeHistory(historyCounter, ht);
    return;
}

// ------------------------------- MAIN ---------------------------------

int main()
{
    eventLoop();
}