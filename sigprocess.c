#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void signhandler(int signum){

   printf("now process receive signal\n");
   exit(0);
}



void main(){
  
  signal(SIGINT,signhandler);
  while(1){


    printf("program is running....PID:%d\n",getpid());
    sleep(1);
  }


}
