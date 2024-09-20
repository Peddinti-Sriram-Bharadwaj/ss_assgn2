/*
============================================================================
Name : 28.c
Author : Sriram Bharadwaj
Description : Changes the permissions of an existing message queue and prints
              both the old and new permissions using the msqid_ds structure.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

void print_permissions(mode_t mode) {
    printf("Permissions: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main() {
    key_t key = ftok("28.c", 'C');  // Generate a unique key
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

    struct msqid_ds ds;
    if (msgctl(msgid, IPC_STAT, &ds) == -1) {
        perror("msgctl IPC_STAT");
        return 1;
    }

    printf("Old Permissions: ");
    print_permissions(ds.msg_perm.mode);

    // Change permissions (e.g., to 0644)
    ds.msg_perm.mode = S_IRUSR | S_IWUSR | S_IROTH;  // Owner: read/write, Others: read

    if (msgctl(msgid, IPC_SET, &ds) == -1) {
        perror("msgctl IPC_SET");
        return 1;
    }

    if (msgctl(msgid, IPC_STAT, &ds) == -1) {
        perror("msgctl IPC_STAT");
        return 1;
    }

    printf("New Permissions: ");
    print_permissions(ds.msg_perm.mode);

    return 0;
}

