/*
============================================================================
Name : 32c.c
Author : Patti Sarath
Description: 32. Write a program to implement semaphore to protect any critical section.
c. protect multiple pseudo resources ( may be two) using counting semaphore
Date: 21 sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main() {
    key_t key = ftok("/tmp", 'R');
    int semid = semget(key, 2, 0666 | IPC_CREAT);
    struct sembuf p[2] = {{0, -1, SEM_UNDO}, {1, -1, SEM_UNDO}};
    struct sembuf v[2] = {{0, 1, SEM_UNDO}, {1, 1, SEM_UNDO}};

    semctl(semid, 0, SETVAL, 2);
    semctl(semid, 1, SETVAL, 2);

    semop(semid, p, 2);
    printf("Resource 1 and 2 acquired\n");
    semop(semid, v, 2);
    printf("Resource 1 and 2 released\n");

    return 0;
}

/*

Resource 1 and 2 acquired
Resource 1 and 2 released

*/
