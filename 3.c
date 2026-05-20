#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>

sem_t wrt;
pthread_mutex_t mutex;
int readcount = 0, shared_data = 1;

void *reader(void *rno) {
    wait(NULL);
    pthread_mutex_lock(&mutex);
    readcount++;
    if (readcount == 1) sem_wait(&wrt); 
    pthread_mutex_unlock(&mutex);

    printf("Reader %d is visually reading data: %d\n", *((int *)rno), shared_data);

    pthread_mutex_lock(&mutex);
    readcount--;
    if (readcount == 0) sem_post(&wrt);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *writer(void *wno) {
    sem_wait(&wrt);
    printf("Writer %d wants to modify data. Enter new value: ", *((int *)wno));
    scanf("%d", &shared_data); 
    printf("Writer %d wrote data: %d\n", *((int *)wno), shared_data);
    sem_post(&wrt);
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);
    int ids[3] = {1, 2, 3};

    pthread_create(&r[0], NULL, reader, &ids[0]);
    pthread_create(&w[0], NULL, writer, &ids[0]);
    pthread_create(&r[1], NULL, reader, &ids[1]);
    pthread_create(&r[2], NULL, reader, &ids[2]);
    pthread_create(&w[1], NULL, writer, &ids[1]);

    for (int i = 0; i < 3; i++) pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++) pthread_join(w[i], NULL);
    return 0;
}