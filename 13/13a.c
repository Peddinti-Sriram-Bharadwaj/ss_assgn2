/*
============================================================================
Name : 13a.c
Author : Sriram Bharadwaj
Description : C program to wait for SIGSTOP signal (which cannot be caught) and print its PID.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sigstop(int sig) {
    // This handler will not be invoked because SIGSTOP cannot be caught or handled
    printf("Received SIGSTOP signal.\n");
}

int main() {
    // Print the PID of this process
    printf("Process PID: %d\n", getpid());

    // Set up a signal handler for SIGSTOP (which will not actually be called)
    signal(SIGSTOP, handle_sigstop);

    printf("Process is running. Try sending SIGSTOP from another program.\n");

    // Infinite loop to keep the program running
    while (1) {
        sleep(1);
    }

    return 0;
}

