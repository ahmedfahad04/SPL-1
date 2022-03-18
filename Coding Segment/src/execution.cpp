#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "shell.h"

void cmd_execute(char **args)
{
    // temporarily I'll send the pure text
    // in future I'll send the tokenize text for execution
    // cmd_execute(commandLine);

    char *cmd = args[0];

    if (strcmp(cmd, "cd"))
        change_directory(args[1]);

    if (strcmp(cmd, "apropos"))
        findExeFileName(args[1]);

    if (strcmp(cmd, "color"))
    {
        if(strcmp(args[1], "--bg")){ 
            char * bgCode = selectBGColor(args[2]);
            eventLoopWithColors(bgCode);
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
        printf("NEW: %s\n", newPath);

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
    char *currdir = current_directory();
    static char *user = (char *)malloc(sizeof(char) * BUFFER_SIZE);
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
        char **chunk = str_tokenize(line, ':');

        if (chunk[5] != 0)
        {
            // this following two condition is a must.
            // it's because if I don't add the first condition
            // it matches '/' with currentdir and that produce faulty results
            if (strcontain(chunk[5], "/home/") && strcontain(currdir, chunk[5]))
            {
                user = chunk[0];
            }
        }
    }

    fclose(fp);

    if (line)
        free(line);

    return user;
}

bool isBuiltInCmd(char *cmd)
{

    bool status = 0;

    if (strcmp(cmd, "cd"))
    {
        status = 1;
    }

    // else if (strcmp(cmd, "color"))
    // {
    //     status = 1;
    //     colorManager();
    // }

    else
    {
        status = 0;
    }

    return status;
}

void execute(char **args)
{

    char *command = args[0];

    if (strcmp(command, "cd"))
    {
        cmd_execute(args);
    }

    else if (strcmp(command, "apropos"))
    {
        cmd_execute(args);
    }

    else if (strcmp(command, "color"))
    {
        cmd_execute(args);
    }

    else
    {

        // store process id
        // check if the process if child or parent
        // if it's the child process run execv()
        // if it's parent process then wait for the child process to be terminated

        pid_t status;

        pid_t process_id;

        process_id = fork();

        // child process
        if (process_id == 0)
        {
            if (execvp(command, args) == -1)
            {
                cmdSuggestion(command);
                // findExeFileName(command);
                perror("Execution failed\n");
            }
            exit(EXIT_FAILURE);
        }
        else if (process_id < 1)
        {
            perror("Process Forking Failed\n");
        }

        else
        {
            status = waitpid(process_id, NULL, 0);
            // printf("It's a parent proecss\n");
        }
    }
}

char *getCurrentDirectory()
{

    char *dir = current_directory();
    char *tilde = strcatt("/home/", userName());
    char *dirPath;

    if (strcontain(dir, tilde))
    {
        dirPath = strreplace(dir, tilde, "~");
    }
    else
    {
        dirPath = dir;
    }

    return dirPath;
}