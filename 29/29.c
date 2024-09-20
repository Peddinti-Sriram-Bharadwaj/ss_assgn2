/*
============================================================================
Name : 29.c
Author : Sriram Bharadwaj
Description : Creates or accesses a message queue, prints its key, and then removes it.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>

int main() {
    key_t key = ftok("29.c", 'D');  // Generate a unique key
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Create or get the message queue ID
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    printf("Key of the message queue to be removed: %d\n", key);

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        return 1;
    }

    printf("Message queue removed successfully.\n");

    return 0;
}

