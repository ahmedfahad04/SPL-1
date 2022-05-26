#include <cstdio>
#include <stdlib.h>

int main(){

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("/etc/passwd", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
    }

    fclose(fp);

    if (line)
    free(line);
}