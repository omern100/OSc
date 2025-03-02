#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delete.h"

/**
 * @brief מוחק קובץ לפי הנתיב שהמשתמש נתן
 * @details מטפל בנתיבים עם גרשיים או בלי, משתמש ב-remove למחיקה
 * @param args מערך של מחרוזות מהמשתמש
 * @return אין
 */
void delete(char **args) {
    if (args[0] == NULL || strcmp(args[0], "delete") != 0) { // בודק שהמילה הראשונה היא "delete"
        printf("Error: Invalid command\n");
        return;
    }

    if (args[1] == NULL) { // בודק אם יש נתיב
        printf("Error: No file path provided\n");
        return;
    }

    char *path = NULL; // משתנה לשמירת הנתיב

    if (args[1][0] == '"') { // אם יש גרשיים
        char combined_path[1024] = {0}; // קופסה לשמירת הנתיב
        int i = 1;
        strcat(combined_path, args[i]); // מוסיף את המילה הראשונה

        // ממשיך לקרוא מילים עד שמוצא גרש סגור
        while (args[i + 1] != NULL) {
            i++;
            strcat(combined_path, " "); // מוסיף רווח
            strcat(combined_path, args[i]); // מוסיף את המילה
            if (args[i][strlen(args[i]) - 1] == '"') { // בודק אם המילה מסתיימת ב-גרש
                break;
            }
        }

        if (args[i] == NULL || args[i][strlen(args[i]) - 1] != '"') { // בודק אם יש סגירה של גרשיים
            printf("Error: Unterminated quoted string\n");
            return;
        }

        // מסיר את הגרשיים מההתחלה והסוף
        path = strdup(combined_path + 1); // מדלג על הגרש הראשון
        path[strlen(path) - 1] = '\0'; // מוחק את הגרש האחרון
    } else {
        path = strdup(args[1]); // לוקח את המילה הראשונה בלי גרשיים
    }

    // מוחק את הקובץ
    if (remove(path) != 0) {
        printf("Error: Failed to delete file\n");
    } else {
        printf("File deleted: %s\n", path);
    }

    free(path); // שחרור הזיכרון
}