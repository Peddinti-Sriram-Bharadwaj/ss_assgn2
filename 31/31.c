/*
============================================================================
Name : 31.c
Author : Sriram Bharadwaj
Description : Creates and initializes a binary semaphore and a counting semaphore.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Binary semaphore
    sem_t *binary_sem = sem_open("/binary_sem", O_CREAT | O_EXCL, 0666, 1);
    if (binary_sem == SEM_FAILED) {
        perror("Failed to create binary semaphore");
        return 1;
    }
    printf("Binary semaphore created and initialized.\n");

    // Counting semaphore
    sem_t *counting_sem = sem_open("/counting_sem", O_CREAT | O_EXCL, 0666, 5);
    if (counting_sem == SEM_FAILED) {
        perror("Failed to create counting semaphore");
        sem_close(binary_sem);
        sem_unlink("/binary_sem");
        return 1;
    }
    printf("Counting semaphore created and initialized with value 5.\n");

    // Cleanup
    if (sem_close(binary_sem) == -1) {
        perror("Failed to close binary semaphore");
    }

    if (sem_close(counting_sem) == -1) {
        perror("Failed to close counting semaphore");
    }

    if (sem_unlink("/binary_sem") == -1) {
        perror("Failed to unlink binary semaphore");
    }

    if (sem_unlink("/counting_sem") == -1) {
        perror("Failed to unlink counting semaphore");
    }

    return 0;
}

