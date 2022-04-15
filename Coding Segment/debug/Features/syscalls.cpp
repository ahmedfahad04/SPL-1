#include <cstdio>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;

void execute(char **args)
{

    char *command = args[0];

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
                //cmdSuggestion(command);
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

int main(){
    char **cmd = (char **) malloc (sizeof(char)*1024);
    scanf("%[^\n]s", cmd);
    execute(cmd);
}