/*
============================================================================
Name : 8c.c
Author : Sriram Bharadwaj
Description : C program to handle SIGFPE signal.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void signal_handler(int signum) {
    printf("Received signal: SIGFPE\n");
    exit(1);
}

int main() {
    signal(SIGFPE, signal_handler);
    int b = 0;
    // Generate SIGFPE by dividing by zero
    int x = 1 / b; // This should trigger SIGFPE if b is 0
    printf("%d\n", x);
    return 0;
}

