#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<errno.h>
#include<fcntl.h>
#include<pthread.h>
pthread_t tid;
int *shmX,*shmY;
key_t X,Y;
int shmidX,shmidY;
void p2_handler(int sig_no)
{
  int ge=*shmY;
   printf("P1 received the signal\n");
   *shmX=tid;
   sleep(2);
   pthread_kill(ge,SIGUSR1);
}
void *created(void *arg)
{
  return NULL;
}
int main()
{
  signal(SIGUSR2,p2_handler);
  pthread_create(&tid, NULL, created, NULL); 
  X=ftok("aa",100);
    shmidX=shmget(X,sizeof(int),IPC_CREAT|0666);
    shmX=(int *)shmat(shmidX,NULL,0); // attaching with shared memory
    *shmX=0;
    Y=ftok("aa",200);
    shmidY=shmget(Y,sizeof(int),IPC_CREAT|0666);
    shmY=(int *)shmat(shmidY,NULL,0);
    *shmY=0;
    sleep(2); 
  printf("P1 is sending a signal\n");
  *shmX=tid;
  execl("./thread_signalling_t2","./thread_signalling_t2",NULL);
  while(1);
}
