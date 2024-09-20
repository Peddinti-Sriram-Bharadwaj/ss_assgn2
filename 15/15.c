/*
============================================================================
Name : 15.c
Author : Sriram Bharadwaj
Description : C program to send data from parent process to child process using a pipe.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    const char *message = "Hello from parent!";
    char buffer[100];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipefd[1]); // Close unused write end
        read(pipefd[0], buffer, sizeof(buffer)); // Read data from pipe
        close(pipefd[0]); // Close read end
        printf("Child received: %s\n", buffer);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(pipefd[0]); // Close unused read end
        write(pipefd[1], message, strlen(message) + 1); // Write data to pipe
        close(pipefd[1]); // Close write end
        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}

