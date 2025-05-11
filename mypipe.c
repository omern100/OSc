#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mypipe.h"
#include "cd.h"
#include "cp.h"
#include "delete.h"
#include "move.h"
#include "echoappend.h"
#include "echowrite.h"
#include "myread.h"
#include "wordCount.h"

void mypipe(char **argv1, char **argv2) {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("Error creating pipe");
        return;
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("Error in fork");
        return;
    }

    if (pid1 == 0) { // Child 1
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        // בדיקה אם הפקודה הראשונה היא פנימית
        if (strcmp(argv1[0], "cd") == 0) {
            cd(argv1);
            exit(0);
        } else if (strcmp(argv1[0], "cp") == 0) {
            cp(argv1);
            exit(0);
        } else if (strcmp(argv1[0], "delete") == 0) {
            delete(argv1);
            exit(0);
        } else if (strcmp(argv1[0], "move") == 0) {
            move(argv1);
            exit(0);
        } else if (strcmp(argv1[0], "echoappend") == 0) {
            echoappend(argv1);
            exit(0);
        } else if (strcmp(argv1[0], "echowrite") == 0) {
            echowrite(argv1);
            exit(0);
        } else if (strcmp(argv1[0], "read") == 0) {
            myread(argv1);
            exit(0);
        } else if (strcmp(argv1[0], "wc") == 0) {
            wordCount(argv1);
            exit(0);
        } else {
            execvp(argv1[0], argv1); // הפעלת פקודה חיצונית
            perror("Error executing first program");
            exit(1);
        }
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("Error in fork");
        return;
    }

    if (pid2 == 0) { // Child 2
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        // בדיקה אם הפקודה השנייה היא פנימית
        if (strcmp(argv2[0], "cd") == 0) {
            cd(argv2);
            exit(0);
        } else if (strcmp(argv2[0], "cp") == 0) {
            cp(argv2);
            exit(0);
        } else if (strcmp(argv2[0], "delete") == 0) {
            delete(argv2);
            exit(0);
        } else if (strcmp(argv2[0], "move") == 0) {
            move(argv2);
            exit(0);
        } else if (strcmp(argv2[0], "echoappend") == 0) {
            echoappend(argv2);
            exit(0);
        } else if (strcmp(argv2[0], "echowrite") == 0) {
            echowrite(argv2);
            exit(0);
        } else if (strcmp(argv2[0], "read") == 0) {
            myread(argv2);
            exit(0);
        } else if (strcmp(argv2[0], "wc") == 0) {
            wordCount(argv2);
            exit(0);
        } else {
            execvp(argv2[0], argv2); // הפעלת פקודה חיצונית
            perror("Error executing second program");
            exit(1);
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);
}