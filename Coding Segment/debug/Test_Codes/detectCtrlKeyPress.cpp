#include <cstdio>
#include <signal.h>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;

void another_function(){
   int x = -1;
  
   while(x != 0){
      cin >> x;
   cout << "You have entered: " << x << endl;
   }
   
}

void sig_handler(int signum)
{
   // Return type of the handler function should be void
   printf("\nInside handler function\n");
   another_function();
}

int main()
{
   signal(SIGINT, sig_handler); // Register signal handler

   for (int i = 1;; i++)
   { // Infinite loop
      printf("%d : Inside main function\n", i);
      sleep(1); // Delay for 1 second
   }
   return 0;
}