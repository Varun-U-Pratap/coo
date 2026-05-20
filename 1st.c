// Producer Consumer Problem using Shared Memory (IPC)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define SIZE 5
struct shared_memory
{
    int buffer[SIZE];
    int in;
    int out;
    int count;
};
int main()
{
    int shmid, i;
    key_t key = ftok("shmfile", 65);
    shmid = shmget(key, sizeof(struct shared_memory), 0666 | IPC_CREAT);
    struct shared_memory *shm = (struct shared_memory *)shmat(shmid, NULL, 0);
    shm->in = 0;
    shm->out = 0;
    shm->count = 0;
    pid_t pid = fork();
    if (pid > 0)
    {
        for (i = 1; i <= 10; i++)
        {
            while (shm->count == SIZE)
                ;
            shm->buffer[shm->in] = i;
            printf("Producer produced: %d\n", i);
            shm->in = (shm->in + 1) % SIZE;
            shm->count++;
            sleep(1);
        }
        wait(NULL);
    }
    else if (pid == 0)
    {
        for (i = 1; i <= 10; i++)
        {
            while (shm->count == 0)
                ;
            int item = shm->buffer[shm->out];
            printf("Consumer consumed: %d\n", item);
            shm->out = (shm->out + 1) % SIZE;
            shm->count--;
            sleep(1);
        }
        exit(0);
    }
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}