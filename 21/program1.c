/*
============================================================================
Name : program1.c
Author : Sriram Bharadwaj
Description : Creates FIFOs if they don't exist, sends a message to FIFO1, waits for a response from FIFO2, and then exits.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    // Create FIFO1 if it doesn't exist
    if (access(FIFO1, F_OK) == -1) {
        if (mkfifo(FIFO1, 0666) == -1) {
            perror("mkfifo FIFO1");
            return 1;
        }
        printf("FIFO %s created\n", FIFO1);
    } else {
        printf("FIFO %s already exists\n", FIFO1);
    }

    // Create FIFO2 if it doesn't exist
    if (access(FIFO2, F_OK) == -1) {
        if (mkfifo(FIFO2, 0666) == -1) {
            perror("mkfifo FIFO2");
            return 1;
        }
        printf("FIFO %s created\n", FIFO2);
    } else {
        printf("FIFO %s already exists\n", FIFO2);
    }

    // Open FIFOs
    int fd1 = open(FIFO1, O_WRONLY);
    int fd2 = open(FIFO2, O_RDONLY);

    if (fd1 == -1 || fd2 == -1) {
        perror("open");
        return 1;
    }

    // Send message
    const char *message = "Message from Program 1";
    write(fd1, message, strlen(message) + 1);

    // Receive response
    char buffer[100];
    read(fd2, buffer, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0'; // Ensure null termination
    printf("Program 1 received: %s\n", buffer);

    close(fd1);
    close(fd2);

    return 0;
}

