/*
============================================================================
Name : 8f.c
Author : Sriram Bharadwaj
Description : C program to handle SIGVTALRM signal using setitimer() system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void handle_signal(int sig) {
    printf("Received signal: SIGVTALRM\n");
    exit(0);
}

int main() {
    signal(SIGVTALRM, handle_signal);
    struct itimerval timer = {{10, 0}, {0, 0}};
    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    while (1);
}

