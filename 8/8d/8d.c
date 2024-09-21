/*
============================================================================
Name : 8d.c
Author : Sriram Bharadwaj
Description : C program to handle SIGALRM signal using alarm() system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void signal_handler(int signum) {
    printf("Received signal: SIGALRM\n");
    exit(0);
}

int main() {
    signal(SIGALRM, signal_handler);

    // Set an alarm for 5 seconds
    alarm(5);

    // Wait for signals
    while (1) {
        pause();
    }

    return 0;
}

