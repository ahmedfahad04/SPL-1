#include <bits/stdc++.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>
#include <termios.h>

struct termios original_mode;

void disableEcho(){
    
    tcsetattr(STDERR_FILENO, TCSAFLUSH, &original_mode);
}

void enableEcho(){

    // this will automatically disable the echo mood while
    // terminating this program
    tcgetattr(STDIN_FILENO, &original_mode);
    atexit(disableEcho);

    struct termios raw = original_mode;

    raw.c_lflag &= ~(ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void testRawMode(){

    struct termios raw;

    // we get the attribute and store them in raw(struct)
    tcgetattr(STDIN_FILENO, &raw);  // don't forget to put &


    //modify the attribute
    raw.c_lflag &= ~(ECHO);


    // set the new modified attribute of the terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

}

int main(){

    // I have to use canonical mood
    // this mood enable you to get the input
    // WITHOUT PRESSING THE ENTER KEY
    // means byte-to-byte input

    // Also I need to use echo mood
    // As we don't want to show the 
    // input value of pressed key.....

    // Also we'll use thread that will detect
    // my key stroke in runtime and act accordingly

    enableEcho();

    char ch;
    //printf("Enter your input now: ");
    while(read(STDIN_FILENO, &ch, 1) == 1 && ch != 'q'){
        printf("%c\n", ch);
    }

}