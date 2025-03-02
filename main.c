#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // עבור chdir ו-pipe
#include "Welcome.h"
#include "getLocation.h"
#include "splitArgument.h"
#include "logout.h"
#include "cd.h"
#include "cp.h"
#include "delete.h"
#include "mypipe.h"
#include "move.h"
#include "echoappend.h"
#include "echowrite.h"
#include "myread.h"
#include "wordCount.h"

void cp(char **args);
void delete(char **args);
void mypipe(char **argv1, char **argv2);
void move(char **args);
void echoappend(char **args);
void echowrite(char **args);
void myread(char **args);
void wordCount(char **args);

int main() {
    Welcome();
    char command[100];
    char input[100];

    printf("Welcome to Nagar's myShell!\n");
    printf("Options: welcome, location, split, logout, cd, cp, delete, move, echoappend, echowrite, myread, wc, help, exit (use | for pipes)\n");

    while (1) {
        getLocation();
        printf("> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        char *pipe_pos = strchr(command, '|');
        if (pipe_pos != NULL) {
            *pipe_pos = '\0';
            char *cmd1 = command;
            char *cmd2 = pipe_pos + 1;

            char **argv1 = splitArgument(cmd1);
            char **argv2 = splitArgument(cmd2);

            if (argv1 == NULL || argv2 == NULL) {
                printf("Error: Invalid pipe command\n");
                if (argv1) free(argv1);
                if (argv2) free(argv2);
                continue;
            }

            mypipe(argv1, argv2);

            free(argv1);
            free(argv2);
            continue;
        }

        char **args = splitArgument(command);
        if (args == NULL) continue;

        if (strcmp(args[0], "welcome") == 0) {
            Welcome();
        } else if (strcmp(args[0], "location") == 0) {
            getLocation();
            printf("\n");
        } else if (strcmp(args[0], "split") == 0) {
            printf("Enter a string to split: ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            char **split_args = splitArgument(input);
            if (split_args != NULL) {
                printf("Words in the array:\n");
                for (int i = 0; split_args[i] != NULL; i++) {
                    printf("args[%d] = %s\n", i, split_args[i]);
                }
                free(split_args);
            }
        } else if (strcmp(args[0], "logout") == 0) {
            logout(command);
        } else if (strcmp(args[0], "cd") == 0) {
            cd(args);
        } else if (strcmp(args[0], "cp") == 0) {
            cp(args);
        } else if (strcmp(args[0], "delete") == 0) {
            delete(args);
        } else if (strcmp(args[0], "move") == 0) {
            move(args);
        } else if (strcmp(args[0], "echoappend") == 0) {
            echoappend(args);
        } else if (strcmp(args[0], "echowrite") == 0) {
            echowrite(args);
        } else if (strcmp(args[0], "myread") == 0) {
            myread(args);
        } else if (strcmp(args[0], "wc") == 0) {
            wordCount(args);
        } else if (strcmp(args[0], "help") == 0) {
            printf("Options: welcome, location, split, logout, cd, cp, delete, move, echoappend, echowrite, myread, wc, help, exit (use | for pipes)\n");
        } else if (strcmp(args[0], "exit") == 0) {
            printf("Bye bye!\n");
            free(args);
            break;
        } else {
            printf("Unknown command! Try: welcome, location, split, logout, cd, cp, delete, move, echoappend, echowrite, myread, wc, help, exit\n");
        }
        free(args);
    }

    return 0;
}