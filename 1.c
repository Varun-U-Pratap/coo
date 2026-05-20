#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int shmid = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);
    char *shared_mem = (char*) shmat(shmid, NULL, 0);

    if (fork() == 0) { 
        printf("[Producer] Enter data to write to shared memory: ");
        scanf(" %s", shared_mem); 
        printf("[Producer] Visualizing Buffer: [%s]\n", shared_mem);
        shmdt(shared_mem);
    } else { 
        wait(NULL); 
        printf("[Consumer] Reading from Buffer: [%s]\n", shared_mem);
        shmdt(shared_mem);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}