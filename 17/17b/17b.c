/*
============================================================================
Name : 17b.c
Author : Sriram Bharadwaj
Description : C program to execute 'ls -l | wc' using dup2().
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child to execute 'ls -l'
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Child process 1
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]); // Close the original write end
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Fork the second child to execute 'wc'
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Child process 2
        close(pipefd[1]); // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin from pipe
        close(pipefd[0]); // Close the original read end
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent process
    close(pipefd[0]); // Close both ends in parent
    close(pipefd[1]); // Close both ends in parent
    wait(NULL); // Wait for both child processes
    wait(NULL); // Wait for both child processes

    return 0;
}

