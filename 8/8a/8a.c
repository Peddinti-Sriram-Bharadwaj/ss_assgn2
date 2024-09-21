/*
============================================================================
Name : 8a.c
Author : Sriram Bharadwaj
Description : C program to handle SIGSEGV signal.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void signal_handler(int signum) {
    printf("Received signal: SIGSEGV\n");
    exit(1);
}

int main() {
    signal(SIGSEGV, signal_handler);

    // Generate SIGSEGV by dereferencing NULL
    int *p = NULL;
    *p = 10;

    return 0;
}

