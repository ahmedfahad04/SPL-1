#include <bits/stdc++.h>
#include <cstdio>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>

struct termios original_mode;

void disableEcho(){
    
    tcsetattr(STDERR_FILENO, TCSAFLUSH, &original_mode);
}

void enableRawMode(){

    // this will automatically disable the echo mood while
    // terminating this program
    
    tcgetattr(STDIN_FILENO, &original_mode);
    atexit(disableEcho);

    struct termios raw = original_mode;
    
    // ECHO denotes that your pressed button won't the showed in the terminal
    // ICANON denotes instant action to your pressing button without waiting for pressing ENTER
    // raw.c_lflag &= ~(ICANON | ISIG);
    raw.c_lflag &= ~(ICANON);
    raw.c_lflag &= ~(OPOST);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// void testEcho(){

//     struct termios raw;

//     // we get the attribute and store them in raw(struct)
//     tcgetattr(STDIN_FILENO, &raw);  // don't forget to put &


//     //modify the attribute
//     raw.c_lflag &= ~(ECHO);


//     // set the new modified attribute of the terminal
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

// }

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


    enableRawMode();
    

    char ch;
    char * result = (char *) malloc (sizeof(char) * 1024);
    int i=0;

    // printf("Enter your text: ");
    // read() can trce byte by byte input
    while(read(STDIN_FILENO, &ch, 1) == 1){

        if (iscntrl(ch)){
            //printf("%d\n", ch);
        }
        else{
            //printf("%d ('%c')\n", ch, ch);
        }
        
        if(ch == 'q') break;
        result[i++] = ch;

    }

    printf("Your given input is: %s\n", result);

}