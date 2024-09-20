/*
============================================================================
Name : print_seconds.c
Author : Sriram Bharadwaj
Description : Write a C program to print "10 seconds passed" every 10 seconds using ITIMER_REAL.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void handle_signal(int sig) {
    printf("10 seconds passed\n");
}

int main() {
    signal(SIGALRM, handle_signal);
    struct itimerval timer = {{10, 0}, {10, 0}};
    setitimer(ITIMER_REAL, &timer, NULL);
    while (1);
}

