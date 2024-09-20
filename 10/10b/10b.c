/*
============================================================================
Name : 10b.c
Author : Sriram Bharadwaj
Description : C program to handle SIGINT signal using sigaction() system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("Caught signal: SIGINT (Interrupt)\n");
    exit(0);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);

    // Wait for SIGINT
    printf("Press Ctrl+C to send SIGINT.\n");
    while (1) {
        pause(); // Wait for the signal
    }

    return 0;
}

