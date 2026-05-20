// Producer Consumer using Message Passing (Message Queue)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
struct message
{
    long msg_type;
    int data;
};
int main()
{
    int msgid, i;
    key_t key = ftok("msgfile.txt", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    pid_t pid = fork();
    if (pid > 0)
    {
        struct message msg;
        msg.msg_type = 1;
        for (i = 1; i <= 10; i++)
        {
            msg.data = i;
            msgsnd(msgid, &msg, sizeof(msg.data), 0);
            printf("Producer produced: %d\n", i);
            sleep(1);
        }
        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }
    else if (pid == 0)
    {
        struct message msg;
        for (i = 1; i <= 10; i++)
        {
            msgrcv(msgid, &msg, sizeof(msg.data), 1, 0);
            printf("Consumer consumed: %d\n", msg.data);
            sleep(1);
        }
        exit(0);
    }
    return 0;
}