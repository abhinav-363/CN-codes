#include<stdio.h> 
#include<sys/ipc.h> 
#include<sys/msg.h> 
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
struct msg_buffer 
{ 
    long msg_type; 
    char msg_text[100]; 
}message; 
int main()
{
	int pidOfProcess=getpid();
	char *myfifo1="/tmp/myfifo1";
	mkfifo(myfifo1,0666);
	int fd=open(myfifo1,O_WRONLY);
	write(fd,&pidOfProcess,sizeof(pidOfProcess));
	sleep(30);
	key_t key=ftok("msg_queue",100);
	int msgid_ds=msgget(key,0666 | IPC_CREAT);
	int f;
	while(1)
	{
		msgrcv(msgid_ds,&message,sizeof(message),getpid(),0);
		f=strcmp(message.msg_text,"end");
      		if(f==0)
      		break;
		printf("Data entered by user in P1 to P2 is : %s\n",message.msg_text);
	}
}
