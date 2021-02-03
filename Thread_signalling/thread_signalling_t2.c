#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<errno.h>
#include<fcntl.h>
#include<pthread.h>
using namespace std;
pthread_t tid1;
int *shmX,*shmY;
key_t X,Y;
int shmidX,shmidY;
void p1_handler(int sig_no)
{
   int ge=*shmX;
   printf("P2 received the signal\n");
   *shmY=tid1;
   sleep(2);
   pthread_kill(ge,SIGUSR2);
}
void *created(void *arg)
{
  return NULL;
}
int main()
{
  signal(SIGUSR1,p1_handler);
  pthread_create(&tid1, NULL, created, NULL); 
  X=ftok("aa",100);
    shmidX=shmget(X,sizeof(int),0666);
    shmX=(int *)shmat(shmidX,NULL,0); // attaching with shared memory
    Y=ftok("aa",200);
    shmidY=shmget(Y,sizeof(int),0666);
    shmY=(int *)shmat(shmidY,NULL,0);
    int id=*shmX;
    *shmY=tid1;
  printf("P2 is sending a signal\n");
  pthread_kill(id,SIGUSR2);
   while(1);
}
