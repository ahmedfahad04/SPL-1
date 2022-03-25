#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


int main(){

    int fd[2];
    if(pipe(fd) == -1){
        printf("Error creating pipe;");
    }

    int pid1 = fork();

    if(pid1 == 0){
        // child process; write end
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);
        execlp("ls", "ls", NULL);
    }

    // pipe 2
    int fd2[2];
    if(pipe(fd2) == -1){
        printf("Error creating pipe;");
    }

    int pid2 = fork();

    if(pid2 == 0){
        // child process; read end
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);

        // write end
        dup2(fd2[1], STDOUT_FILENO);
        close(fd2[1]);
        close(fd2[0]);
        execlp("cat", "cat", NULL);
    }

    // erpor ar fd er kaj nai tai etake ekhanei off korte hobe
    close(fd[1]);
    close(fd[0]);


    int pid3 = fork();

    if(pid3 == 0){

        // child process; read end
        dup2(fd2[0], STDIN_FILENO);
        close(fd2[1]);
        close(fd2[0]);
        execlp("grep", "grep", "sim", NULL);
    }

    
    close(fd2[1]);
    close(fd2[0]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);


    
}


