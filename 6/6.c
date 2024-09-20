/*
============================================================================
Name : 6.c
Author : Sriram Bharadwaj
Description : Write a C program to create three threads, each printing a unique statement.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <pthread.h>

// Function to be executed by each thread
void* print_message(void* thread_id) {
    int id = *((int*)thread_id);
    switch(id) {
        case 0:
            printf("This is thread 1.\n");
            break;
        case 1:
            printf("This is thread 2.\n");
            break;
        case 2:
            printf("This is thread 3.\n");
            break;
        default:
            printf("Unknown thread.\n");
            break;
    }
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_ids[3] = {0, 1, 2};
    
    // Create three threads
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, print_message, (void*)&thread_ids[i]) != 0) {
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

