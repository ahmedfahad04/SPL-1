#include <cstdio>

int sum (int a, int b){
    return a+b;
}

int sub (int a, int b){
    return a-b;
}

int multi (int a, int b){
    return a*b;
}

int div (int a, int b){
    if(b != 0) return a/b;
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



    // array of funciton pointer
    int (*choice[10])(int, int) = {sum, sub, multi, div};
    int x = 21, y = 7;
    int chs;
    
    printf("Enter your choice (0-3): ");
    scanf("%d", &chs);

    printf("RESULT IS: %d\n", (*choice[chs])(x,y));

    // for(int i=0; i<4; i++){
    //     printf("RESULT IS: %d\n", (*choice[i])(x,y));
    // }

}