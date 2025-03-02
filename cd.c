#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cd.h"

void cd(char **args) {
    if (args[1] == NULL) { // אם אין נתיב אחרי "cd"
        printf("Error: No path provided\n"); // שגיאה אם אין תיקייה
        return;
    }

    char *path = NULL; // משתנה לשמירת הנתיב הסופי
    int len = 0;

    if (args[1][0] == '"') { // אם יש גרשיים
        // חיפוש סוף הגרשיים וחיבור כל המילים
        for (int i = 1; args[i] != NULL; i++) {
            len += strlen(args[i]) + 1; // סופר את האורך כולל רווחים
        }
        path = (char *)malloc(len * sizeof(char)); // מקצה זיכרון לנתיב
        if (path == NULL) {
            perror("Error in malloc");
            return;
        }
        path[0] = '\0'; // מתחיל עם מחרוזת ריקה

        for (int i = 1; args[i] != NULL; i++) {
            strcat(path, args[i]); // מוסיף את המילה
            if (args[i + 1] != NULL) strcat(path, " "); // מוסיף רווח בין מילים
        }
        // מסיר את הגרשיים מההתחלה והסוף
        path[strlen(path) - 1] = '\0'; // מסיר גרש סוגר
        memmove(path, path + 1, strlen(path)); // מסיר גרש פותח
    } else {
        path = args[1]; // לוקח את המילה הראשונה בלבד
    }

    // שינוי התיקייה
    if (chdir(path) != 0) {
        perror("Error changing directory"); // שגיאה אם התיקייה לא קיימת
    }

    if (args[1][0] == '"') {
        free(path); // שחרור הזיכרון אם הקצנו אותו
    }
}