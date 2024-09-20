/*
============================================================================
Name : 2.c
Author : Sriram Bharadwaj
Description : Write a C program to print system resource limits using getrlimit system call, casting limits to int.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>

void print_limit(int soft_limit, int hard_limit, const char* name) {
    printf("%s: Soft limit = %d, Hard limit = %d\n", name, soft_limit, hard_limit);
}

int main() {
    struct rlimit limit;
    
    getrlimit(RLIMIT_CPU, &limit);
    print_limit((int)limit.rlim_cur, (int)limit.rlim_max, "CPU Time");

    getrlimit(RLIMIT_FSIZE, &limit);
    print_limit((int)limit.rlim_cur, (int)limit.rlim_max, "File Size");

    getrlimit(RLIMIT_DATA, &limit);
    print_limit((int)limit.rlim_cur, (int)limit.rlim_max, "Data Segment Size");

    getrlimit(RLIMIT_STACK, &limit);
    print_limit((int)limit.rlim_cur, (int)limit.rlim_max, "Stack Size");

    getrlimit(RLIMIT_CORE, &limit);
    print_limit((int)limit.rlim_cur, (int)limit.rlim_max, "Core File Size");

    getrlimit(RLIMIT_RSS, &limit);
    print_limit((int)limit.rlim_cur, (int)limit.rlim_max, "Resident Set Size");

    getrlimit(RLIMIT_NPROC, &limit);
    print_limit((int)limit.rlim_cur, (int)limit.rlim_max, "Number of Processes");

    getrlimit(RLIMIT_NOFILE, &limit);
    print_limit((int)limit.rlim_cur, (int)limit.rlim_max, "Number of Open Files");

    getrlimit(RLIMIT_MEMLOCK, &limit);
    print_limit((int)limit.rlim_cur, (int)limit.rlim_max, "Locked Memory Size");

    return 0;
}

