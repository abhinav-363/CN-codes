#include<stdio.h> 
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
	char s[100];
	key_t key=ftok("msg_queue",100);
	int msgid=msgget(key,0666 | IPC_CREAT);
	message.msg_type=1;
	printf("Enter data for sending : ");
	scanf("%s",s);
	strcpy(message.msg_text,s);
	msgsnd(msgid,&message,sizeof(message),0);
	msgrcv(msgid,&message,sizeof(message),1,0);
	printf("Data entered by user is : %s\n",message.msg_text);
	msgctl(msgid,IPC_RMID,NULL);  
}
