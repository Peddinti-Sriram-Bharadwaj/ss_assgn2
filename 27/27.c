/*
============================================================================
Name : 27.c
Author : Sriram Bharadwaj
Description : Creates a message queue, sends a test message, and receives messages.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>

#define MSG_TYPE 1

struct message {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("27.c", 'B');  // Generate a unique key
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    int msgid = msgget(key, IPC_CREAT | 0666);  // Create or get message queue ID
    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    struct message msg;
    msg.msg_type = MSG_TYPE;
    snprintf(msg.msg_text, sizeof(msg.msg_text), "Test message");

    // Send a test message
    msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);

    // Receive message with blocking flag (0)
    if (msgrcv(msgid, &msg, sizeof(msg.msg_text), MSG_TYPE, 0) != -1) {
        printf("Received message: %s\n", msg.msg_text);
    } else {
        perror("msgrcv");
    }

    // Try to receive message with IPC_NOWAIT flag
    if (msgrcv(msgid, &msg, sizeof(msg.msg_text), MSG_TYPE, IPC_NOWAIT) == -1 && errno == ENOMSG) {
        printf("No message available (non-blocking mode).\n");
    } else {
        perror("msgrcv");
    }

    return 0;
}

