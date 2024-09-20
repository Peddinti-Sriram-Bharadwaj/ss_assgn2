/*
============================================================================
Name : 4.c
Author : Sriram Bharadwaj
Description : Write a C program to measure the time taken to execute 100 getppid() system calls using mach_absolute_time().
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <mach/mach_time.h>

int main() {
    uint64_t start, end;
    mach_timebase_info_data_t timebase;
    uint64_t elapsed;
    pid_t ppid;
    
    // Get the timebase info for mach_absolute_time
    mach_timebase_info(&timebase);

    // Measure time before the system calls
    start = mach_absolute_time();

    // Execute 100 getppid() system calls
    for (int i = 0; i < 100; i++) {
        ppid = getppid();
    }

    // Measure time after the system calls
    end = mach_absolute_time();

    // Calculate the elapsed time in nanoseconds
    elapsed = (end - start) * timebase.numer / timebase.denom;

    printf("Time taken for 100 getppid() calls: %llu nanoseconds\n", (unsigned long long)elapsed);

    return 0;
}

