#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <sys/wait.h>


int main(){

    // replace all the PID with an ARRAY of PID
    // also replace the file descriptor with 2d integer array
    pid_t pid[100];
    int fd[100][2];

    // pipe 1
    if(pipe(fd[0]) == -1){
        printf("Error creating pipe;");
    }

    // cmd 1
    int x = fork();
    pid[0]  = x;
    if(pid[0] == 0){
        // child process; write end
        dup2(fd[0][1], STDOUT_FILENO);
        close(fd[0][1]);
        close(fd[0][0]);
        
        execlp("ls", "ls", NULL);
    }
    waitpid(pid[0], NULL, 0);
    // ---------------------------------------------------------------

    // pipe 2
    if(pipe(fd[1]) == -1){
        printf("Error creating pipe;");
    }

    // cmd 2
    x = fork();
    pid[1]  = x;
    if(pid[1] == 0){
        // child process; read end
        dup2(fd[0][0], STDIN_FILENO);
        close(fd[0][1]);
        close(fd[0][0]);

        // // write end
        // dup2(fd[1][1], STDOUT_FILENO);
        // close(fd[1][1]);
        // close(fd[1][0]);
        execlp("cat", "cat", NULL);
    }

    // // erpor ar fd er kaj nai tai etake ekhanei off korte hobe
    close(fd[0][1]);
    close(fd[0][0]);
    waitpid(pid[1], NULL, 0);
    // // ===========================================================================

    // // we can place another pipe here...(3)
    // if(pipe(fd[2]) == -1){
    //     printf("Error creating pipe;");
    // }


    // // cmd 3
    // x = fork();
    // pid[2]  = x;
    // if(pid[2] == 0){

    //     // child process; read end
    //     dup2(fd[1][0], STDIN_FILENO);
    //     close(fd[1][1]);
    //     close(fd[1][0]);

    //     // also we can place another write end here which can be linked with pipe3

    //     // write end
    //     dup2(fd[2][1], STDOUT_FILENO);
    //     close(fd[2][1]);
    //     close(fd[2][0]);

    //     execlp("grep", "grep", "sim", NULL);
    // }


    // close(fd[1][1]);
    // close(fd[1][0]);
    // waitpid(pid[2], NULL, 0);
    // // ===========================================================================

    // // cmd 4
    // x = fork();
    // pid[3]  = x;
    // if(pid[3] == 0){

    //     // child process; read end
    //     dup2(fd[2][0], STDIN_FILENO);
    //     close(fd[2][1]);
    //     close(fd[2][0]);

    //     execlp("wc", "wc", "-l", NULL);
    // }

    // close(fd[2][1]);
    // close(fd[2][0]);
    // waitpid(pid[3], NULL, 0);
    // ---------------------------------------------------------------

    
    // waitpid(pid[1], NULL, 0);
    // waitpid(pid[2], NULL, 0);
    // waitpid(pid[3], NULL, 0);




    
}


