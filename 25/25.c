/*
============================================================================
Name : 25.c
Author : Sriram Bharadwaj
Description : Creates a message queue if it does not exist, then prints details
              such as access permissions, UID, GID, times of message operations,
              queue size, number of messages, maximum number of bytes allowed,
              and PID of message operations.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

int main() {
    key_t key = ftok("25.c", 'A');  // Generate a unique key
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

    struct msqid_ds buf;
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {  // Get message queue info
        perror("msgctl");
        return 1;
    }

    // Access Permissions
    printf("Access Permissions: %o\n", (int)buf.msg_perm.mode);

    // UID and GID
    printf("UID: %d\n", (int)buf.msg_perm.uid);
    printf("GID: %d\n", (int)buf.msg_perm.gid);

    // Times
    printf("Last Message Sent: %s", ctime((time_t *)&buf.msg_stime));
    printf("Last Message Received: %s", ctime((time_t *)&buf.msg_rtime));
    printf("Last Change: %s", ctime((time_t *)&buf.msg_ctime));

    // Size of the queue
    printf("Queue Size: %d bytes\n", (int)buf.msg_qbytes);

    // Number of Messages
    printf("Number of Messages: %d\n", (int)buf.msg_qnum);

    // Maximum Number of Bytes Allowed
    printf("Maximum Number of Bytes Allowed: %d bytes\n", (int)buf.msg_qbytes);

    // PIDs
    printf("PID of Last Message Sent: %d\n", (int)buf.msg_lspid);
    printf("PID of Last Message Received: %d\n", (int)buf.msg_lrpid);

    return 0;
}

