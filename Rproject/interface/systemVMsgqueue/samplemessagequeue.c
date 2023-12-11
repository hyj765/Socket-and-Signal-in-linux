#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

/*
 *  
 *	One of the Linux ipc methods
 *	systemV message qeueu do not removed even process is exited, because messages are saved in kernel
 *	as long as message queue capacity is avaliable, messages can continue to be stacked in queue
 *	
 */

struct msgstruct{
	long msg_type;
	char data[100];
};

int main(){

	key_t key= 11172;
	int msgid,status;
	struct msgstruct msg;
	msg.msg_type = 1;
	strcpy(msg.data,"Messageqeue is working now");
	//message queue create
	msgid = msgget(key, 0666 | IPC_CREAT);
	if(0 > msgid){
		printf("msgget failed\n");
		exit(0);
	}

	status=msgsnd(msgid,&msg,100,0);
	if(0 > status){
		printf("msgsnd failed\n");
		exit(0);
	}	
	
	/*	
	 *	this method is saving message in kernel
	 *	msgsnd (int  msqid ,
	 *	const void* msgq, msgbuf struct
	 *	size_t msgsz,
	 *	int msgflg
	 *	);
	 *
	 *	struct msgbuf{
	 *		long mtype,
	 *		char mtext[1];
	 *	}
	 *	
	 *	receive message from kernel
	 *	msgrcv(int msqid,
	 *	void* msgp,
	 *	size_t msgsz,
	 *	long msgtype,
	 *	int msgflg
	 *	);
	 *
	 */	
	
}
