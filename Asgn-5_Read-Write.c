#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

sem_t mutex, wrt;
int sharedvar = 99;
int readercount = 0;

void* writer(void* arg) {
    printf("\nWriter is trying to enter");
    sem_wait(&wrt);
    printf("\nWriter had entered CS");
    sharedvar++;
    printf("\nWriter CHANGED VALUE OF SHARED VAR TO %d", sharedvar);
    sem_post(&wrt);
    printf("\nWriter is out of CS");
    return NULL;
}

void* reader(void* arg) {
    while (true) {
        sem_wait(&mutex);
        readercount++;
        if (readercount == 1)
            sem_wait(&wrt);
        sem_post(&mutex);

        printf("\nReader is reading shared variable: %d", sharedvar);
        
        sem_wait(&mutex);
        readercount--;
        if (readercount == 0)
            sem_post(&wrt);
        sem_post(&mutex);

        break;
    }
    return NULL;
}

int main() {
    int n2, i;
    printf("Enter the number of readers and writers: ");
    if (scanf("%d", &n2) != 1 || n2 <= 0) {
        printf("Invalid input.\n");
        return 1;
    }


    pthread_t *writers = malloc(n2 * sizeof(pthread_t));
    pthread_t *readers = malloc(n2 * sizeof(pthread_t));

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < n2; i++) {
        pthread_create(&writers[i], NULL, writer, NULL);
        pthread_create(&readers[i], NULL, reader, NULL);
    }

    for (i = 0; i < n2; i++) {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    free(writers);
    free(readers);

    return 0;
}
