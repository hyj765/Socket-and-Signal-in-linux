#include<stdio.h>
#include<signal.h>
#include<unistd.h>


int main(){


 int pid;
 printf("If you want to send a signal to process\n");
 printf("Insert Pid Here:");
 scanf("%d",&pid);
 
 kill(pid,SIGINT);

}
