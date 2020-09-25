#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>


volatile sig_atomic_t alert = false;
int count = 0;

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  //exit(1); //exit after printing
  alert = true;
  //alarm(1);
}
void secondhandler(int signum)
{ //signal handler
  printf("\nDelivered %d alarms\n", count);
  exit(1);

}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(1); //Schedule a SIGALRM for 1 second
  while(1){
    signal(SIGALRM,handler);
    signal(SIGINT, secondhandler); // Register signal handler for SIGINT
    sleep(1);
    if ( alert ) {
        //printf( "Hello\n" );
        alert = false;
        //alarm( 1 ); // Reschedule.
        count += 1;
     }
    printf("Turing was right!\n");
    alarm(1);
  } //busy wait for signal to be delivered
  return 0; //never reached
}

