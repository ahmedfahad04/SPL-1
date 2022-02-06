#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

void cmd_execute(char *cmd, char *args)
{
    // temporarily I'll send the pure text
    // in future I'll send the tokenize text for execution
    //cmd_execute(commandLine);
    
    if (strcmp(cmd, "cd"))
        change_directory(args);
    else if(strcmp(cmd, "nano")){
        launch_nano();
    }

}

void change_directory(char *path)
{

    if (chdir(path) != 0)
        printf("ecsh: cd: %s: No such file or directory\n", path);
}

char* current_directory()
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
        //return 1;
    }

    return addr;
}

char* hostname(){

    FILE *fp;

    if((fp = fopen("/etc/hosts", "r")) == NULL){
        printf("Failed to open /etc/hostname\n");
    }

    // we need to use character array instead of pointers.
    // as pointer array of character lost the input after reading the whole file. 
    char a[200], b[200], hostname[200], *host; 
    int line = 1; 

    while (fscanf(fp, "%s %s ", a, b) != EOF)
    {        
        if(line == 2){
            host = strcpy(b);
        }
        line++;
    }

    fclose(fp);
 
    return host;
}

void launch_nano(){


}

