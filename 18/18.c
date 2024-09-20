/*
============================================================================
Name : 18.c
Author : Sriram Bharadwaj
Description : C program to find the total number of directories in the current
               working directory using 'ls -l | grep ^d | wc -l' with dup2().
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipefd1[2], pipefd2[2];
    pid_t pid1, pid2;

    // Create the first pipe
    if (pipe(pipefd1) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create the second pipe
    if (pipe(pipefd2) == -1) {
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
        close(pipefd1[0]); // Close unused read end
        dup2(pipefd1[1], STDOUT_FILENO); // Redirect stdout to pipe write end
        close(pipefd1[1]); // Close the original write end
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Fork the second child to execute 'grep ^d'
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Child process 2
        close(pipefd1[1]); // Close unused write end of first pipe
        dup2(pipefd1[0], STDIN_FILENO); // Redirect stdin from first pipe read end
        close(pipefd1[0]); // Close the original read end

        close(pipefd2[0]); // Close unused read end of second pipe
        dup2(pipefd2[1], STDOUT_FILENO); // Redirect stdout to second pipe write end
        close(pipefd2[1]); // Close the original write end

        execlp("grep", "grep", "^d", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent process
    close(pipefd1[0]); // Close both ends of the first pipe
    close(pipefd1[1]); // Close both ends of the first pipe

    close(pipefd2[1]); // Close the write end of the second pipe

    // Redirect stdin to the second pipe read end
    dup2(pipefd2[0], STDIN_FILENO);
    close(pipefd2[0]); // Close the original read end

    execlp("wc", "wc", "-l", NULL);
    perror("execlp");
    exit(EXIT_FAILURE);
}

