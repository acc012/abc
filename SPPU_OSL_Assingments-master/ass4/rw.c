#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Shared data
int shared_data = 0;

// Synchronization tools
sem_t rw_mutex;    // Semaphore to control access to the shared resource
sem_t mutex;       // Semaphore to control access to the reader count
int reader_count = 0;  // Number of active readers

// Reader function
void *reader(void *arg) {
    int reader_id = *((int *)arg);
    free(arg);

    // Start reading
    sem_wait(&mutex);
    reader_count++;
    if (reader_count == 1) {
        sem_wait(&rw_mutex); // First reader locks resource for all readers
    }
    sem_post(&mutex);

    // Reading the shared data
    printf("Reader %d: reads shared data as %d\n", reader_id, shared_data);
    sleep(1); // Simulate reading time

    // End reading
    sem_wait(&mutex);
    reader_count--;
    if (reader_count == 0) {
        sem_post(&rw_mutex); // Last reader unlocks the resource
    }
    sem_post(&mutex);
    return NULL;
}

// Writer function
void *writer(void *arg) {
    int writer_id = *((int *)arg);
    free(arg);

    // Start writing
    sem_wait(&rw_mutex); // Lock the resource for writing

    // Writing to the shared data
    shared_data++;
    printf("Writer %d: updated shared data to %d\n", writer_id, shared_data);
    sleep(1); // Simulate writing time

    // End writing
    sem_post(&rw_mutex); // Unlock the resource for other readers or writers
    return NULL;
}

int main() {
    // Initialize semaphores
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    // Create reader and writer threads
    pthread_t readers[5], writers[3];
    int i;

    // Start readers
    for (i = 0; i < 5; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&readers[i], NULL, reader, id);
    }

    // Start writers
    for (i = 0; i < 3; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&writers[i], NULL, writer, id);
    }

    // Join all threads
    for (i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (i = 0; i < 3; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
