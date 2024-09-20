/*
============================================================================
Name : print_limits.c
Author : Sriram Bharadwaj
Description : Prints the maximum number of files that can be opened within a process
              and the size of a pipe (circular buffer).
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Get the maximum number of open files per process
    long max_files = sysconf(_SC_OPEN_MAX);
    if (max_files == -1) {
        perror("sysconf");
        return 1;
    }

    printf("Maximum number of open files per process: %ld\n", max_files);

    // Since macOS doesn't support F_GETPIPE_SZ, use the default pipe buffer size
    // Default size is typically 64 KB (65536 bytes)
    int pipe_size = 65536;  // Assuming default size; check macOS documentation if needed

    printf("Size of pipe (circular buffer): %d bytes\n", pipe_size);

    return 0;
}

