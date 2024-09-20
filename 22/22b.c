/*
============================================================================
Name : write_fifo.c
Author : Sriram Bharadwaj
Description : Writes data to a FIFO every second.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO "fifo"

int main() {
    // Open FIFO for writing
    int fd = open(FIFO, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write data to FIFO every second
    for (int i = 0; ; i++) {
        char message[50];
        snprintf(message, sizeof(message), "Message %d\n", i);
        write(fd, message, sizeof(message));
        sleep(1);
    }

    close(fd);
    return 0;
}

