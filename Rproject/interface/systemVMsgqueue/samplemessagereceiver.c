#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>

struct msgstruct{
	long msg_type;
	char data[100];
};

int main(){

	key_t key= 11172;
	int msgid,status;

	struct msgstruct msg;

	msgid = msgget(key,0666|IPC_CREAT);
	if(0>msgid ){
		printf("msgget failed\n");
		exit(0);
	}

	status = msgrcv(msgid,&msg,100,0,0);
	if(0> status){
		printf("msgrcv failed\n");
		exit(0);
	}

	printf("data: %s",msg.data);

	status = msgctl(msgid,IPC_RMID,NULL);
	if(0>status){
		printf("msgctl failed\n");
		exit(0);
	}


}


