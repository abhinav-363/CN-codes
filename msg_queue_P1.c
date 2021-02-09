#include<stdio.h> 
#include<sys/ipc.h> 
#include<sys/msg.h>
#include<string.h> 
#include<unistd.h>
struct msg_buffer 
{ 
    long msg_type; 
    char msg_text[100]; 
}message; 
int main()
{
	int pid2,pid3,n;
	key_t key=ftok("msg_queue",100);
	int msgid=msgget(key,0666 | IPC_CREAT);
	msgrcv(msgid,&message,sizeof(message),0,0);
	pid2=message.msg_type;
	msgrcv(msgid,&message,sizeof(message),0,0);
	pid3=message.msg_type;
	printf("%d\n",pid2);
	printf("%d\n",pid3);
	printf("Enter the total no. of messages you want to send from P1 : ");
	scanf("%d",&n);
	while(n--)
	{
		char s[100];
		printf("To which process you wanna send the message : ");
		scanf("%s",s);
		if(s[1]=='2')
		{
			printf("Enter data for sending to P2 : ");
			char buf[100];
			scanf("%s",buf);
			strcpy(message.msg_text,buf);
			message.msg_type=pid2;
			msgsnd(msgid,&message,sizeof(message),0);
			printf("Data sent by P1 to P2 is %s\n",message.msg_text);
		}
		else
		{
			printf("Enter data for sending to P3 : ");
			char buf[100];
			scanf("%s",buf);
			strcpy(message.msg_text,buf);
			message.msg_type=pid3;
			msgsnd(msgid,&message,sizeof(message),0);
			printf("Data sent by P1 to P3 is %s\n",message.msg_text);
		}
	}
	strcpy(message.msg_text,"end");
	message.msg_type=pid2;
	msgsnd(msgid,&message,sizeof(message),0);
	strcpy(message.msg_text,"end");
	message.msg_type=pid3;
	msgsnd(msgid,&message,sizeof(message),0);
}
