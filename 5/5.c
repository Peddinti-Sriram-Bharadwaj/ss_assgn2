/*
============================================================================
Name : 5.c
Author : Sriram Bharadwaj
Description : Write a C program to print various system limitations and parameters.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <limits.h>
#include <stdlib.h>

int main() {
    // a. Maximum length of arguments to the exec family of functions
    printf("Maximum length of arguments to exec family: %d bytes\n", (int)sysconf(_SC_ARG_MAX));

    // b. Maximum number of simultaneous processes per user id
    int max_processes;
    size_t len = sizeof(max_processes);
    if (sysctlbyname("kern.maxproc", &max_processes, &len, NULL, 0) == 0) {
        printf("Maximum number of simultaneous processes per user id: %d\n", max_processes);
    } else {
        perror("sysctlbyname");
    }

    // c. Number of clock ticks (jiffy) per second
    printf("Number of clock ticks per second: %ld\n", (long)sysconf(_SC_CLK_TCK));

    // d. Maximum number of open files
    struct rlimit limit;
    getrlimit(RLIMIT_NOFILE, &limit);
    printf("Maximum number of open files: Soft limit = %ld, Hard limit = %ld\n",
           (long)limit.rlim_cur, (long)limit.rlim_max);

    // e. Size of a page
    long page_size = sysconf(_SC_PAGESIZE);
    printf("Size of a page: %ld bytes\n", page_size);

    // f. Total number of pages in physical memory
    int pages;
    size_t mem_size = sizeof(pages);
    if (sysctlbyname("hw.memsize", &pages, &mem_size, NULL, 0) == 0) {
        printf("Total number of pages in physical memory: %ld\n", (long)(pages / page_size));
    } else {
        perror("sysctlbyname");
    }

    // g. Number of currently available pages in physical memory
    int free_pages;
    if (sysctlbyname("vm.page_free_count", &free_pages, &mem_size, NULL, 0) == 0) {
        printf("Number of currently available pages in physical memory: %d\n", free_pages);
    } else {
        perror("sysctlbyname");
    }

    return 0;
}

