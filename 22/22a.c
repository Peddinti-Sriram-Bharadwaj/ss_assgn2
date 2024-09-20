/*
============================================================================
Name : wait_fifo.c
Author : Sriram Bharadwaj
Description : Creates a FIFO if it doesn't exist, waits for data with select system call within 10 seconds, and reads it.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>

#define FIFO "fifo"

int main() {
    // Create FIFO if it doesn't exist
    if (access(FIFO, F_OK) == -1 && mkfifo(FIFO, 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    // Open FIFO for reading
    int fd = open(FIFO, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Set up fd_set and timeout
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    struct timeval timeout = {10, 0}; // 10 seconds

    // Wait for data
    if (select(fd + 1, &readfds, NULL, NULL, &timeout) > 0) {
        char buffer[100];
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("Data: %s\n", buffer);
        }
    } else {
        printf("No data within 10 seconds.\n");
    }

    close(fd);
    return 0;
}

