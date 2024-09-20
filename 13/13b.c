/*
============================================================================
Name : 13b.c
Author : Sriram Bharadwaj
Description : C program to send SIGSTOP signal to another process.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Find the PID of the process to be stopped (e.g., the first program's PID)
    printf("Enter the PID of the process to stop: ");
    scanf("%d", &pid);

    // Send SIGSTOP to the specified process
    if (kill(pid, SIGSTOP) == -1) {
        perror("kill");
        exit(EXIT_FAILURE);
    }

    printf("SIGSTOP signal sent to process PID %d.\n", pid);

    return 0;
}

