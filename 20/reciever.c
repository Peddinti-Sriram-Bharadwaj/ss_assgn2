/*
============================================================================
Name : receiver.c
Author : Sriram Bharadwaj
Description : Read a message from a FIFO file.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("my_fifo", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[bytesRead] = '\0';  // Null-terminate the string
    printf("Received message: %s\n", buffer);
    close(fd);

    return 0;
}

