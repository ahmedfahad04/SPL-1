#include <bits/stdc++.h>
using namespace std;

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

typedef struct str{
    char *data;
    int len;

} st;

typedef int integer;

int main(){

    /*-------------------------------------BASIC OF STURCTURE----------------------------------*/

    int a;

    // here "struct Student" is a data type
    struct student s1, s2, *ptr;

    s1.name = "Fahad";
    s1.roll = 14;
    printf("\nROLL: %d, NAME: %s\n", s1.roll, s1.name);

    // we can also directly cope the content of one struct to another
    s2 = s1;
    ptr = &s2;

    st s;
    s.len = 21;
    s.data = "Istiaq Ahmed Fahad";

    printf("NAME: %s, Age: %d", s.data, s.len);
    printf("\nNow I'm printing the name using structure pointer: %s\n", ptr->name);

    /*-------------------------------------TYPEDEF----------------------------------*/

    integer y = 10;
    int z = 15;
    cout << "SUMMATION IS: " << z+y << endl;

    /*-------------------------------------STRUCTURE PADDING----------------------------------*/
    
}