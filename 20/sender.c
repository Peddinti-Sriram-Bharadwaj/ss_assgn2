/*
============================================================================
Name : sender.c
Author : Sriram Bharadwaj
Description : Write a message to a FIFO file.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("my_fifo", O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    const char *message = "Hello from sender";
    write(fd, message, sizeof("Hello from sender"));
    close(fd);

    return 0;
}

