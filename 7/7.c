/*
============================================================================
Name : 7.c
Author : Sriram Bharadwaj
Description : Write a C program to create three threads and print their IDs.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <pthread.h>

// Function to be executed by each thread
void* print_thread_id(void* thread_id) {
    pthread_t id = pthread_self();
    printf("Thread ID: %lu\n", (unsigned long)id);
    return NULL;
}

int main() {
    pthread_t threads[3];
    
    // Create three threads
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, print_thread_id, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

