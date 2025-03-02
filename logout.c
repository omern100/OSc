#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logout.h"

void logout(char *str) {
    char *exit_word = "exit"; // המילה שאנחנו מחפשים
    char *token = strtok(str, " \n"); // מפרק את המחרוזת לפי רווחים וסוף שורה

    if (token != NULL && strcmp(token, exit_word) == 0) {
        printf("Logging out... Bye!\n"); // מדפיס הודעה לפני סגירה
        exit(0); // סוגר את התוכנית בהצלחה
    }
}