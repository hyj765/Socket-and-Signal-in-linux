#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>


void sigIntHandler(int signum){
	printf("Demonlize Process is Done\n");
	exit(0);
}

void deamonize(){
  pid_t pid = fork();

  if(pid < 0){
  	printf("Failed to fork\n");
	exit(0);
  }else if(pid > 0){
	exit(0);
  } 
  umask(0);
  pid_t sid = setsid();
  if(sid < 0) {
	printf("failed to setsid");
	exit(0);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

}


int main(){
 deamonize();
 signal(SIGINT,sigIntHandler);
 while(1){

	
	

  
 }


}