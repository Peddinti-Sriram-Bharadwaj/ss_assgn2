/*
============================================================================
Name : print_microseconds.c
Author : Sriram Bharadwaj
Description : Write a C program to print a dot (.) for every 10 microseconds using ITIMER_REAL.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void handle_signal(int sig) {
    printf(".");
    fflush(stdout); // To ensure the dot is printed immediately
}

int main() {
    signal(SIGALRM, handle_signal);
    struct itimerval timer = {{0, 10}, {0, 10}};
    setitimer(ITIMER_REAL, &timer, NULL);
    while (1);
}

