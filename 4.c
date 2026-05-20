#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t chopstick[5];

void *philosopher(void *num) {
    int id = *((int *)num);
    printf("Philosopher %d is visually thinking...\n", id);
    
    sem_wait(&chopstick[id]);
    sem_wait(&chopstick[(id + 1) % 5]);
    
    printf("Philosopher %d is EATING (Has chopsticks %d and %d)\n", id, id, (id+1)%5);
    sleep(1); 
    
    sem_post(&chopstick[id]);
    sem_post(&chopstick[(id + 1) % 5]);
    printf("Philosopher %d finished eating and put down chopsticks.\n", id);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int ids[5];
    for (int i = 0; i < 5; i++) sem_init(&chopstick[i], 0, 1);
    
    for (int i = 0; i < 5; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < 5; i++) pthread_join(threads[i], NULL);
    return 0;
}