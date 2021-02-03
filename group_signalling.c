#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
void handlerParent(int sig_num)
{
    printf("SIGNAL RECEIVED BY PARENT\n");
}
void handlerChild1(int sig_num)
{
    printf("SIGNAL RECEIVED BY CHILD 1\n");
}
void handlerChild2(int sig_num)
{
    printf("SIGNAL RECEIVED BY CHILD 2\n");
}
void handlerChild3(int sig_num)
{
    printf("SIGNAL RECEIVED BY CHILD 3\n");
}
void handlerChild4(int sig_num)
{
    printf("SIGNAL RECEIVED BY CHILD 4\n");
}
int main()
{
	int pids[5];
	pid_t pid=fork();
	if(pid==0)
	{
        	signal(SIGUSR1,handlerChild1);
        	while(1)
        	{
        		printf("CHILD 1 : Running\n");
            		sleep(1);
            	}	
    	}
    	else
    	{
        	pids[0]=getpid();
        	pids[1]=pid;
        	pid=fork();
        	if(pid==0)
        	{
            		signal(SIGUSR1,handlerChild2);
            		while(1)
			{
				printf("CHILD 2 : Running\n");
		    		sleep(1);
		    	}	
        	}
        	else
        	{
            		pids[2]=pid;
            		pid=fork();
            		if(pid==0)
            		{
                		signal(SIGUSR1,handlerChild3);
                		while(1)
				{
					printf("CHILD 3 : Running\n");
			    		sleep(1);
			    	}	
            		}
            		else
            		{
                		pids[3]=pid;
                		pid=fork();
                		if(pid==0)
                		{
                    			signal(SIGUSR1,handlerChild4);
                    			while(1)
					{
						printf("CHILD 4 : Running\n");
				    		sleep(1);
				    	}	
                		}
                		else
                		{
                			sleep(2);
                        		signal(SIGUSR1, handlerParent);
                        		printf("HELLO\n"); 
                    			pids[4]=pid;
                    			setpgid(pids[4],pids[4]);
                        		setpgid(pids[3],pids[4]);
                        		setpgid(pids[2],pids[4]);
                        		setpgid(pids[1],pids[4]);
                        		kill(getpid(),SIGUSR1);
                        		killpg(getpgid(pids[4]), SIGUSR1);
                        		for(int i=0;i<5;i++)
                        		printf("PGID OF PROCESS %d : %d\n",i,getpgid(pids[i]));
                		}
            		}
        	}
    	}
}
