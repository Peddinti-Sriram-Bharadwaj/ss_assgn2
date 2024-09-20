/*
============================================================================
Name : 10a.c
Author : Sriram Bharadwaj
Description : C program to handle SIGSEGV signal using sigaction() system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_sigsegv(int sig) {
    printf("Caught signal: SIGSEGV (Segmentation Fault)\n");
    exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigsegv;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGSEGV, &sa, NULL);

    // Cause a segmentation fault
    int *ptr = NULL;
    *ptr = 0;

    return 0;
}

