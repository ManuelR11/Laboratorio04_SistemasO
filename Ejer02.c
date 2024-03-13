#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5

pthread_mutex_t tenedores[NUM_FILOSOFOS];
sem_t sem_mutex;

void *filosofo(void *arg) {
    int id = *((int *)arg);
    int tenedor_izq = id;
    int tenedor_der = (id + 1) % NUM_FILOSOFOS;

    while (1) {
        printf("Filósofo %d está pensando.\n", id);

        sem_wait(&sem_mutex);

        pthread_mutex_lock(&tenedores[tenedor_izq]);
        pthread_mutex_lock(&tenedores[tenedor_der]);

        printf("Filósofo %d está comiendo.\n", id);
        sleep(2);


        pthread_mutex_unlock(&tenedores[tenedor_der]);
        pthread_mutex_unlock(&tenedores[tenedor_izq]);

        sem_post(&sem_mutex);
    }
}

int main() {
    pthread_t filosofos[NUM_FILOSOFOS];
    int ids[NUM_FILOSOFOS];

    sem_init(&sem_mutex, 0, NUM_FILOSOFOS - 1);

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_mutex_init(&tenedores[i], NULL);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(filosofos[i], NULL);
    }

    sem_destroy(&sem_mutex);
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_mutex_destroy(&tenedores[i]);
    }

    return 0;
}
