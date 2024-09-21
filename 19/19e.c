/*
============================================================================
Name : create_fifo_mkfifo.c
Author : Sriram Bharadwaj
Description : Create a FIFO file using mkfifo library function.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    const char *fifo_path = "fifo_mkfifo";
    if (mkfifo(fifo_path, 0666) < 0) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
    printf("FIFO file '%s' created using mkfifo\n", fifo_path);
    return 0;
}

