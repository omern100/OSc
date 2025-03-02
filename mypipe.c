#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mypipe.h"

/**
 * @brief מפעיל שתי תוכניות עם צינור (pipe) ביניהן
 * @details התוכנית הראשונה שולחת את הפלט שלה כקלט לתוכנית השנייה
 * @param argv1 מערך הארגומנטים לתוכנית הראשונה
 * @param argv2 מערך הארגומנטים לתוכנית השנייה
 * @return אין
 */
void mypipe(char **argv1, char **argv2) {
    int pipefd[2]; // מערך לשני קצוות הצינור: [0] לקריאה, [1] לכתיבה
    pid_t pid1, pid2; // משתנים לזיהוי התהליכים

    if (pipe(pipefd) == -1) { // יוצר צינור
        perror("Error creating pipe");
        return;
    }

    pid1 = fork(); // יוצר תהליך חדש
    if (pid1 == -1) {
        perror("Error in fork");
        return;
    }

    if (pid1 == 0) { // תהליך הילד הראשון (התוכנית הראשונה)
        close(pipefd[0]); // סוגר את קצה הקריאה
        dup2(pipefd[1], STDOUT_FILENO); // שולח את הפלט לצינור
        close(pipefd[1]); // סוגר את קצה הכתיבה
        execvp(argv1[0], argv1); // מפעיל את התוכנית הראשונה
        perror("Error executing first program");
        exit(1);
    }

    pid2 = fork(); // יוצר תהליך חדש נוסף
    if (pid2 == -1) {
        perror("Error in fork");
        return;
    }

    if (pid2 == 0) { // תהליך הילד השני (התוכנית השנייה)
        close(pipefd[1]); // סוגר את קצה הכתיבה
        dup2(pipefd[0], STDIN_FILENO); // לוקח את הקלט מהצינור
        close(pipefd[0]); // סוגר את קצה הקריאה
        execvp(argv2[0], argv2); // מפעיל את התוכנית השנייה
        perror("Error executing second program");
        exit(1);
    }

    // התהליך הראשי סוגר את שני קצוות הצינור ומחכה לילדים
    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL); // מחכה לילד הראשון
    wait(NULL); // מחכה לילד השני
}