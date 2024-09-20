/*
============================================================================
Name : 16.c
Author : Sriram Bharadwaj
Description : C program to demonstrate two-way communication between parent and child processes using pipes.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe1[2]; // Pipe for parent to child
    int pipe2[2]; // Pipe for child to parent
    pid_t pid;
    const char *parent_message = "Hello from parent!";
    const char *child_message = "Hello from child!";
    char buffer[100];

    // Create the pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
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
        close(pipe1[1]); // Close unused write end of pipe1
        close(pipe2[0]); // Close unused read end of pipe2

        // Read data from parent
        read(pipe1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(pipe1[0]); // Close read end

        // Send data to parent
        write(pipe2[1], child_message, strlen(child_message) + 1);
        close(pipe2[1]); // Close write end

        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(pipe1[0]); // Close unused read end of pipe1
        close(pipe2[1]); // Close unused write end of pipe2

        // Send data to child
        write(pipe1[1], parent_message, strlen(parent_message) + 1);
        close(pipe1[1]); // Close write end

        // Read data from child
        read(pipe2[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        close(pipe2[0]); // Close read end

        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}

