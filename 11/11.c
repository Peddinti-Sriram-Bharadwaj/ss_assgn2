/*
============================================================================
Name : 11.c
Author : Sriram Bharadwaj
Description : C program to ignore SIGINT signal and then reset it to default action using sigaction().
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sigint(int sig) {
    // This handler will be invoked if SIGINT is not ignored
    printf("Received SIGINT signal.\n");
    exit(0);
}

int main() {
    struct sigaction sa;

    // Ignore SIGINT signal
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    // Wait for a moment to demonstrate ignoring the signal
    printf("SIGINT is currently ignored. Press Ctrl+C to test.\n");
    sleep(10);

    // Reset SIGINT to default action
    sa.sa_handler = SIG_DFL; // Reset to default action
    sigaction(SIGINT, &sa, NULL);

    // Wait to show that default action is now in effect
    printf("SIGINT has been reset to default action. Press Ctrl+C to test.\n");
    sleep(10);

    return 0;
}

