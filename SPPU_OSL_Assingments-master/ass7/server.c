// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHM_SIZE 1024  // size of shared memory segment

int main() {
    key_t key;
    int shmid;
    char *shmaddr;

    // Generate a unique key for shared memory
    key = ftok("shmfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to server process
    shmaddr = (char*) shmat(shmid, NULL, 0);
    if (shmaddr == (char*) -1) {
        perror("shmat");
        exit(1);
    }

    // Write a message to the shared memory segment
    printf("Enter a message to write to shared memory: ");
    fgets(shmaddr, SHM_SIZE, stdin);

    printf("Message written to shared memory: %s\n", shmaddr);

    // Detach from shared memory
    //shmdt(shmaddr);

    return 0;
}
