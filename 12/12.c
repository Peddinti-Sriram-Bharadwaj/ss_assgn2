/*
============================================================================
Name : 12.c
Author : Sriram Bharadwaj
Description : C program to create an orphan process. The child process sends SIGKILL to its parent process.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        sleep(2); // Wait for the parent to be killed
        printf("Child process: Sending SIGKILL to parent process (PID %d)\n", getppid());
        kill(getppid(), SIGKILL); // Send SIGKILL to the parent process

        // Wait for a moment to ensure the parent is terminated
        sleep(5);
        printf("Child process: I am now an orphan.\n");
        // Optionally, you can perform further operations here

        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("Parent process: PID %d\n", getpid());
        sleep(10); // Wait to ensure the child process sends SIGKILL

        // The parent process will be killed by the child process before this point

        // This code is unreachable in practice due to the SIGKILL signal
        printf("Parent process should be terminated by the child.\n");
        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}

