#include <stdio.h>

// structure is simply a "user defined data type"
// also the value is stored in runtime, as the 
// memory is allocated in RUNTIME
// therefore you can't declare the value inside the structure
// rather you've to initialize them inside main function
// after the declaration of the struct
struct student{
    int roll;
    float weight;
    char *name;
};

int main(){

    int a;

    // here "struct Student" is a data type
    struct student s1, s2;

    s1.name = "Fahad";
    printf("\nROLL: %d, NAME: %s\n", s1.roll, s1.name);

    // we can also directly cope the content of one struct to another
    s2 = s1;

}