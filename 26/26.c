/*
============================================================================
Name : 26.c
Author : Sriram Bharadwaj
Description : Sends a message to a message queue. Use `ipcs -q` to check
              the message queue status after running this program.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MSG_TYPE 1

struct message {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("26.c", 'B');  // Generate a unique key
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

    struct message msg;
    msg.msg_type = MSG_TYPE;
    snprintf(msg.msg_text, sizeof(msg.msg_text), "Hello, Message Queue!");

    // Send the message
    if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    printf("Message sent to message queue with ID: %d\n", msgid);

    return 0;
}

