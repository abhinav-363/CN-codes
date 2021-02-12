#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/msg.h>
#include <stdio.h>
int main()
{
    sem_unlink("sem_p1");
    sem_unlink("sem_p2");
    sem_unlink("sem_p3");
    sem_unlink("sem_f");
    sem_t *p1 = sem_open("sem_p1", O_CREAT | O_RDWR, 0660, 0);
    sem_t *p2 = sem_open("sem_p2", O_CREAT | O_RDWR, 0660, 0);
    sem_t *p3 = sem_open("sem_p3", O_CREAT | O_RDWR, 0660, 0);
    sem_t *f = sem_open("sem_f", O_CREAT | O_RDWR, 0660, 0);
    sem_wait(f);
    sem_wait(f);
    sem_wait(f);
    sem_post(p1);
    sem_post(p2);
    sem_post(p3);
    char buf[100];
    while (1)
    {
        scanf("%s", buf);
        if (strcmp(buf, "end"))
            continue;
        break;
    }
    key_t key = ftok("lab3", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    msgctl(msgid, IPC_RMID, NULL);
}