#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h> 


int main(){
    int pid = fork();

    if(pid == 0){

        int file = open("STDOUT.txt", O_WRONLY | O_CREAT, 0777);
        if(file == -1){
            puts("Error writing file");
        }

        printf("Previous FD: %d\n", file);
        int fdout = dup2(file, 1);  // permanently converted the stdout...
        
        printf("NEW FD: %d\n", fdout);
        close(file);
        

        // we're creating the execution in child process
        // becasue if we do it in parent process it won't
        // allow us to execute any more commands after
        // this execlp() system call
        // it's because execlp() take control off the whole system
        // process execution and replace the memory of the process
        // with it's own memory and finally it becomes the ultimate
        // code to be executed.
        execlp("ls", "ls", "-al", NULL);
        // execlp("ping", "ping", "-c", "2", "google.com", NULL);
        printf("Its a child process....\n.");
    }
    else{

        // wait(NULL); // parent wait for child to finish then the foremost lines to be executed.
        // puts("Hello");

        int wstatus;

        wait(&wstatus);
        if(WIFEXITED(wstatus)){
            int statusCode = WEXITSTATUS(wstatus);

            if(statusCode == 0){
                puts("SUCCESS");
            } else {
                printf("Failure with code: %d\n", statusCode);
            }

        }

        printf("SOMETHING ELSE\n");
    }
}
