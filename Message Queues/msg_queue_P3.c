#include<stdio.h> 
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h> 
#include<sys/msg.h>
#include<string.h> 
struct msg_buffer 
{ 
    long msg_type; 
    char msg_text[100]; 
}message; 
int main()
{
	int pidOfProcess=getpid();
	key_t key=ftok("msg_queue",100);
	int msgid=msgget(key,0666 | IPC_CREAT);
	message.msg_type=pidOfProcess;
	strcpy(message.msg_text,"P3");
	msgsnd(msgid,&message,sizeof(message),0);
	sleep(30);
	int f;
	while(1)
	{
		msgrcv(msgid,&message,sizeof(message),getpid(),0);
		f=strcmp(message.msg_text,"end");
      		if(f==0)
      		break;
		printf("Data entered by user in P1 to P3 is : %s\n",message.msg_text);
	}
	msgctl(msgid,IPC_RMID,NULL);
}
