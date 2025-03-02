#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myread.h"

/**
 * @brief מדפיס את תוכן הקובץ למסך
 * @details מטפל בנתיבים עם גרשיים או בלי, משתמש ב-fopen לקריאה
 * @param args מערך של מחרוזות מהמשתמש
 * @return אין
 */
void myread(char **args) {
    if (args[0] == NULL || strcmp(args[0], "read") != 0) { // בודק שהמילה הראשונה היא "read"
        printf("Error: Invalid command\n");
        return;
    }

    if (args[1] == NULL) { // בודק שיש נתיב
        printf("Error: No file path provided\n");
        return;
    }

    char *path = NULL; // משתנה לשמירת הנתיב

    if (args[1][0] == '"') { // אם יש גרשיים
        char combined_path[1024] = {0}; // קופסה לשמירת הנתיב
        int i = 1;
        strcat(combined_path, args[i]); // מוסיף את המילה הראשונה
        while (args[i + 1] != NULL && args[i][strlen(args[i]) - 1] != '"') { // ממשיך עד גרש סגור
            i++;
            strcat(combined_path, " "); // מוסיף רווח
            strcat(combined_path, args[i]); // מוסיף את המילה
        }
        if (args[i] == NULL || args[i][strlen(args[i]) - 1] != '"') { // בודק סגירה של גרשיים
            printf("Error: Unterminated quoted string\n");
            return;
        }
        path = strdup(combined_path + 1); // מדלג על הגרש הראשון
        path[strlen(path) - 1] = '\0'; // מוחק את הגרש האחרון
    } else {
        path = strdup(args[1]); // נתיב בלי גרשיים
    }

    // פותח את הקובץ לקריאה
    FILE *file = fopen(path, "r"); // פותח במוד "read"
    if (file == NULL) { // אם הקובץ לא קיים, לא עושה כלום
        free(path);
        return;
    }

    char line[1024]; // קופסה לשמירת שורה
    while (fgets(line, sizeof(line), file) != NULL) { // קורא שורה-שורה
        printf("%s", line); // מדפיס את השורה
    }

    fclose(file); // סוגר את הקובץ
    free(path); // שחרור הזיכרון
}