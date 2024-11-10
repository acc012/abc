// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHM_SIZE 1024  // size of shared memory segment

int main() {
    key_t key;
    int shmid;
    char *shmaddr;

    // Generate the same key for shared memory
    key = ftok("shmfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Locate the shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to client process
    shmaddr = (char*) shmat(shmid, NULL, 0);
    if (shmaddr == (char*) -1) {
        perror("shmat");
        exit(1);
    }

    // Read and display the message from the shared memory segment
    printf("Message read from shared memory: %s\n", shmaddr);

    // Detach from shared memory
    //shmdt(shmaddr);

    // Optional: Remove the shared memory segment after reading
   // shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
