#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>
struct msg_buffer
{
    long msg_type;
    char msg_text[100];
} message;
int msgid;
int pid[3] = {0};
void *reader_handler(void *)
{
    while (1)
    {
        msgrcv(msgid, &message, sizeof(message), pid[0], 0);
        printf("Process P1 received a message :  %s\n\n", message.msg_text);
    }
}

void *writer_handler(void *)
{
    while (1)
    {
        char buf[100];
        printf("Enter message : \n");
        scanf("%s", buf);
        strcpy(message.msg_text, buf);
        message.msg_type = pid[2];
        msgsnd(msgid, &message, sizeof(message), 0);
        printf("Process 1 sent message : %s to Process 2 with PID : %d.\n", message.msg_text, message.msg_type);
        message.msg_type = pid[1];
        msgsnd(msgid, &message, sizeof(message), 0);
        printf("Process 1 sent message : %s to Process 3 with PID : %d.\n\n", message.msg_text, message.msg_type);
    }
}

int main()
{
    sem_t *p1 = sem_open("sem_p1", O_CREAT | O_RDWR, 0660, 0);
    sem_t *f = sem_open("sem_f", O_CREAT | O_RDWR, 0660, 0);
    int pidOfProcess = getpid();
    pid[0] = pidOfProcess;
    int i = 1;
    printf("PID of P1 is : %d\n", pidOfProcess);
    key_t key = ftok("lab3", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    msgctl(msgid, IPC_RMID, NULL);
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = pidOfProcess;
    strcpy(message.msg_text, "P1");
    msgsnd(msgid, &message, sizeof(message), 0);
    msgsnd(msgid, &message, sizeof(message), 0);
    sleep(11);
    while (1)
    {
        msgrcv(msgid, &message, sizeof(message), 0, 0);
        if (message.msg_type == pidOfProcess)
            msgsnd(msgid, &message, sizeof(message), 0);
        else
        {
            if (pid[i] == 0)
                pid[i] = message.msg_type;
            else
            {
                if (pid[i] == message.msg_type)
                {
                    message.msg_type = pid[0];
                    strcpy(message.msg_text, "P1");
                    msgsnd(msgid, &message, sizeof(message), 0);
                }
                else
                {
                    ++i;
                    pid[i] = message.msg_type;
                    break;
                }
            }
        }
    }
    printf("In P1, PID of P2 is : %d\nIn P1, PID of P3 is %d\n", pid[2], pid[1]);
    pthread_t read_th, write_th;
    sem_post(f);
    sem_wait(p1);
    pthread_create(&write_th, NULL, writer_handler, NULL);
    pthread_create(&read_th, NULL, reader_handler, NULL);
    pthread_join(write_th, NULL);
    pthread_join(read_th, NULL);
}