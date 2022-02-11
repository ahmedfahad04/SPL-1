#include <stdio.h>

int sum (int a, int b){
    return a+b;
}

int sub (int a, int b){
    return a-b;
}

// this is called CALLBACK FUNCTION as it accepts other FUNCTION POINTERS as args
int display(int (*ptr)(int, int), int a, int b){    
    return ptr(a,b);   
};

int main(){

    // this is a function pointer
    int (*fptr)(int, int) = sum;    
    int s = fptr(1,4);
    printf("SUM: %d\n", s);

    // here we're passing function address (sum)
    int ss = display(sum, 5, 6);    
    printf("NEW SUM: %d\n", ss);

    int sss = display(sub, 74, 62);
    printf("SUBSTACTION: %d\n", sss);

}