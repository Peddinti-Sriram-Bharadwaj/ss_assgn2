/*
============================================================================
Name : 24.c
Author : Sriram Bharadwaj
Description : Creates a message queue, prints the key and the message queue ID.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>

int main() {
    key_t key = ftok("24.c", 'A');  // Generate a unique key for the message queue
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    int msgid = msgget(key, IPC_CREAT | 0666);  // Create the message queue
    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

