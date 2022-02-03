#include <stdio.h>
#include <signal.h>
void sigint_handler(int signum)
{ //Handler for SIGINT
   //Reset handler to catch SIGINT next time.

   signal(SIGINT, sigint_handler);
   printf("Cannot be stopped using Ctrl+C \n");
   //fflush(stdout);
}
int main()
{

   int a;

   signal(SIGINT, sigint_handler);

   while (1)
   { //create infinite loop
      scanf("%d", &a);
      printf("A: %d", a);
      
   }
}