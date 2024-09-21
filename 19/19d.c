/*
============================================================================
Name : create_fifo_mknod.c
Author : Sriram Bharadwaj
Description : Create a FIFO file using mknod system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    const char *fifo_path = "fifo_mknod";
    if (mknod(fifo_path, S_IFIFO | 0666, 0) < 0) {
        perror("mknod");
        exit(EXIT_FAILURE);
    }
    printf("FIFO file '%s' created using mknod\n", fifo_path);
    return 0;
}

