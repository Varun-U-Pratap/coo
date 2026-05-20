#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 5
int buffer[MAX], in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *pno) {
    for(int i = 0; i < MAX; i++) {
        int item = (i + 1) * 10;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        
        buffer[in] = item;
        printf("Producer %d visually inserted: %d at %d\n", *((int *)pno), item, in);
        in = (in + 1) % MAX;
        
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *cno) {
    for(int i = 0; i < MAX; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        int item = buffer[out];
        printf("Consumer %d visually removed: %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % MAX;
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t pro, con;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, MAX);
    sem_init(&full, 0, 0);
    int id = 1;
    
    pthread_create(&pro, NULL, producer, &id);
    pthread_create(&con, NULL, consumer, &id);
    pthread_join(pro, NULL);
    pthread_join(con, NULL);
    return 0;
}