/*
============================================================================
Name : print_virtual_microseconds.c
Author : Sriram Bharadwaj
Description : Write a C program to print a dot (.) for every 10 microseconds using ITIMER_VIRTUAL.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void handle_signal(int sig) {
    printf(".");
    fflush(stdout);
}

int main() {
    signal(SIGVTALRM, handle_signal);
    struct itimerval timer = {{0, 10}, {0, 10}};
    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    while (1);
}

