/*
============================================================================
Name : 3.c
Author : Sriram Bharadwaj
Description : Write a C program to set the maximum number of open files resource limit using setrlimit system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit limit;

    // Get current limits
    getrlimit(RLIMIT_NOFILE, &limit);

    // Print current limits
    printf("Current limits for number of open files: Soft limit = %ld, Hard limit = %ld\n",
           (long)limit.rlim_cur, (long)limit.rlim_max);

    // Set new soft limit
    limit.rlim_cur = (rlim_t)1024; // Set the soft limit to 1024

    // Set the limits using setrlimit
    if (setrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("Successfully updated the number of open files limit.\n");
    } else {
        perror("Failed to update the number of open files limit");
    }

    // Print updated limits
    getrlimit(RLIMIT_NOFILE, &limit);
    printf("Updated limits for number of open files: Soft limit = %ld, Hard limit = %ld\n",
           (long)limit.rlim_cur, (long)limit.rlim_max);

    return 0;
}

