#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main()
{

   
    int arr[] = {1, 2, 4, 5, 9, 1};
    int size = sizeof(arr) / sizeof(int);
    int start, end;

    // file descriptor and pipes
    int fd[2];
    if(pipe(fd) == -1){
        cout << "Pipeline error...\n";
    }

    // you have to create this fork call after declaring the pipe call. It's order must be maintained.
    // you have to declare PIPE first
    // then you've to FORK the process
    int id = fork();

    if (id == 0)
    {
        // child process
        start = 0;
        end = size / 2;
    }
    else
    {
        // parent process
        start = size / 2;
        end = size;
    }

    int sum = 0;
    for (int i = start; i < end; i++)
    { // here we've such terms that is dependent on child and parent process
        sum += arr[i];
    }



    if (id == 0)
    {
        close(fd[0]);
        char name[100];
        scanf("%[^\n]s", name);
        
        // write the ans of sum from the child process in your PARENT process
        if(write(fd[1], &name, sizeof(name)) == -1){
            cout << "\nFailed to Write values";
        }
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int readFromChildProcess;
        char fromChild[500];

       
        if(read(fd[0], &fromChild, sizeof(fromChild)) == -1){
            cout << "\nFiled to read values";
        }

        cout << "\nNAME from Child is: " << fromChild << endl;
        close(fd[0]);

        // cout << "\nSummation got from the child process is: " << readFromChildProcess << endl;
        // int newsum = sum + readFromChildProcess;
        // cout << "\nNEW summation: " << newsum << endl;  
    }

    cout << "\nSummation: " << sum << endl;
}