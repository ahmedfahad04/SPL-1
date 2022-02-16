#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

void cmd_execute(char **args)
{
    // temporarily I'll send the pure text
    // in future I'll send the tokenize text for execution
    // cmd_execute(commandLine);

    char *cmd = args[0];

    if (strcmp(cmd, "cd"))
        change_directory(args[1]);

    else if (strcmp(cmd, "nano"))
    {
        launch_nano();
    }
}

void change_directory(char *path)
{

    if (chdir(path) != 0)
        printf("ecsh: cd: %s: No such file or directory\n", path);
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

    // int len = strlen(host);
    // host[len] = '\0';

    fclose(fp);

    return host;
}

char *userName()
{
    char *user = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    int id = 0;

    FILE *fp;

    if ((fp = fopen("/etc/passwd", "r")) == NULL)
    {
        printf("Failed to open /etc/passwd\n");
    }

    // we need to use character array instead of pointers.
    // as pointer array of character lost the input after reading the whole file.
    char a[200];
    char *currdir = current_directory();


    while (fscanf(fp, "%s", a) != EOF)
    {
        char **res = str_tokenize(a, ':');

        if (res[5] != 0){
            if(strcontain(currdir, res[5])){
                user = res[0];
            }
        }
    }

    fclose(fp);

    return user;
}

void launch_nano()
{
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

    char *command = args[0];

    if (strcmp(command, "cd"))
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