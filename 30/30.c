/*
============================================================================
Name : 30.c
Author : Sriram Bharadwaj
Description : Creates a shared memory segment, writes data to it, attaches 
              with O_RDONLY to check overwriting, detaches, and removes the segment.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
    key_t key = ftok("30.c", 'E');  // Generate a unique key
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Create shared memory segment
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // Attach to the shared memory segment
    char *data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)-1) {
        perror("shmat");
        return 1;
    }

    // Write data to the shared memory segment
    strcpy(data, "Hello, Shared Memory!");

    // Detach from the shared memory segment
    if (shmdt(data) == -1) {
        perror("shmdt");
        return 1;
    }

    // Reattach to the shared memory segment with read-only access
    data = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (data == (char *)-1) {
        perror("shmat");
        return 1;
    }

    // Attempt to overwrite data (will fail if read-only)
    printf("Trying to overwrite shared memory data...\n");
    strcpy(data, "New Data");

    // Check and print the data
    printf("Data in shared memory: %s\n", data);

    // Detach from the shared memory segment
    if (shmdt(data) == -1) {
        perror("shmdt");
        return 1;
    }

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        return 1;
    }

    printf("Shared memory removed successfully.\n");

    return 0;
}

