/*
============================================================================
Name : 9.c
Author : Sriram Bharadwaj
Description : C program to ignore SIGINT signal, then reset to default action.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Ignore SIGINT signal
    signal(SIGINT, SIG_IGN);

    // Wait for a moment to demonstrate ignoring the signal
    printf("SIGINT is currently ignored. Press Ctrl+C to test.\n");
    sleep(10);

    // Reset SIGINT to default action
    signal(SIGINT, SIG_DFL);

    // Wait to show that default action is now in effect
    printf("SIGINT has been reset to default action. Press Ctrl+C to test.\n");
    sleep(10);

    return 0;
}

