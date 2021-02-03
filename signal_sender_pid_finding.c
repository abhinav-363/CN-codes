#include<stdio.h>
#include<signal.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
int cnt=0,max_cnt=10;
static struct sigaction sig;
static void multi_handler(int sig,siginfo_t *siginfo,void *context) 
{
	pid_t sender_pid=siginfo->si_pid;					// get pid of sender
	if(sig==SIGINT) 
	{
	        printf(" INT(%d), from [%d]\n",++cnt,(int)sender_pid);
	        return;
	} 
	else if(sig==SIGQUIT) 
	{
        	printf(" Quit, bye bye, from [%d]\n",(int)sender_pid);
        	exit(0);
	}
	return;
}
int main()
{
	int sig_num;
	printf("Process [%d] started.\n",(int)getpid());
	sig.sa_sigaction=*multi_handler;					// prepare sigaction
	sig.sa_flags|=SA_SIGINFO; 						// get detail info
	// change signal action
	if(sigaction(SIGINT,&sig,NULL)!=0) 
	{
        	printf("error sigaction()");
        	return errno;
	}
	if(sigaction(SIGQUIT,&sig,NULL)!=0) 
	{
        	printf("error sigaction()");
        	return errno;
	}
	// use "ctrl + c" to send SIGINT, and "ctrl + \" to send SIGQUIT
	while(1) 
	{
        	if(cnt<max_cnt)
            	sig_num=SIGINT;
        	else
 		sig_num=SIGQUIT;
       	raise(sig_num); 							// send signal to itself
        	sleep(1); 							// sleep a while, note that: SIGINT will interrupt this, and make program wake up,
    }
    return 0;
}
