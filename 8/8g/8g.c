/*
============================================================================
Name : 8g.c
Author : Sriram Bharadwaj
Description : C program to handle SIGPROF signal using setitimer() system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void signal_handler(int signum) {
    printf("Received signal: SIGPROF\n");
    exit(0);
}

int main() {
    struct itimerval timer;
    signal(SIGPROF, signal_handler);

    // Set up the timer to expire in 5 seconds
    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_PROF, &timer, NULL);

    // Wait for signals
    while (1) {
        pause();
    }

    return 0;
}

