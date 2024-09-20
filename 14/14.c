/*
============================================================================
Name : 14.c
Author : Sriram Bharadwaj
Description : C program to create a pipe, write to it, read from it, and display the output.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buffer[100];
    const char *message = "Hello, this is a message from the pipe!";
    ssize_t bytesRead;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Write to the pipe
    write(pipefd[1], message, strlen(message) + 1); // Include the null terminator

    // Read from the pipe
    bytesRead = read(pipefd[0], buffer, sizeof(buffer));

    if (bytesRead == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Display the message
    printf("Message from pipe: %s\n", buffer);

    return 0;
}

