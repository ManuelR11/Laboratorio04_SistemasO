#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t recurso1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t recurso2 = PTHREAD_MUTEX_INITIALIZER;

// Proceso 1 intenta adquirir los recursos en orden A, B
void *proceso1(void *arg) {
    while (1) {
        pthread_mutex_lock(&recurso1);
        printf("Proceso 1 adquirió recurso 1\n");
        sleep(1);
        pthread_mutex_lock(&recurso2);
        printf("Proceso 1 adquirió recurso 2\n");
        // Realiza alguna operación
        sleep(1);
        pthread_mutex_unlock(&recurso2);
        pthread_mutex_unlock(&recurso1);
    }
}

// Proceso 2 intenta adquirir los recursos en orden B, A
void *proceso2(void *arg) {
    while (1) {
        pthread_mutex_lock(&recurso2);
        printf("Proceso 2 adquirió recurso 2\n");
        sleep(1);
        pthread_mutex_lock(&recurso1);
        printf("Proceso 2 adquirió recurso 1\n");
        // Realiza alguna operación
        sleep(1);
        pthread_mutex_unlock(&recurso1);
        pthread_mutex_unlock(&recurso2);
    }
}

int main() {
    pthread_t thread1, thread2;
    
    // Creamos los threads para los procesos
    pthread_create(&thread1, NULL, proceso1, NULL);
    pthread_create(&thread2, NULL, proceso2, NULL);

    // Esperamos a que ambos threads terminen (esto nunca sucederá debido al deadlock)
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    return 0;
}
