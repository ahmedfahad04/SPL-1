#include <stdio.h>
#include <dirent.h>

int main(){

    DIR *folder;
    struct dirent *files;

    char ch[100];
    int cnt = 0;
    printf("Enter directory path: ");
    scanf("%s", ch);

    folder = opendir(ch);

    if(folder == NULL){
        perror("Unable to read the directory");
    }

    else{

        while(files = readdir(folder)){
            cnt++;
            printf("> %s\n", files->d_name);
            
        }

        printf("Total Files: %d\n", cnt);
    }

    closedir(folder);

}