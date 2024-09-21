/*
============================================================================
Name : 8b.c
Author : Sriram Bharadwaj
Description : C program to handle SIGINT signal.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h> // Include this header for pause()

void signal_handler(int signum) {
    printf("Received signal: SIGINT\n");
    exit(0);
}

int main() {
    signal(SIGINT, signal_handler);

    // Wait for signals
    while (1) {
        pause(); // Wait for a signal to arrive
    }

    return 0;
}

