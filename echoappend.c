#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "echoappend.h"

/**
 * @brief מוסיף מחרוזת לקובץ במוד append
 * @details מטפל במחרוזות עם גרשיים או בלי, משתמש ב-fopen במוד "a"
 * @param args מערך של מחרוזות מהמשתמש
 * @return אין
 */
void echoappend(char **args) {
    if (args[0] == NULL || strcmp(args[0], "echo") != 0) { // בודק שהמילה הראשונה היא "echo"
        printf("Error: Invalid command\n");
        return;
    }

    if (args[1] == NULL || args[2] == NULL || strcmp(args[2], ">>") != 0 || args[3] == NULL) { // בודק שיש מחרוזת, >> ונתיב
        printf("Error: Expected format: echo <string> >> <file>\n");
        return;
    }

    char *string = NULL, *path = NULL; // משתנים למחרוזת ולנתיב
    int string_end_idx = 1; // משתנה שמראה איפה המחרוזת נגמרת

    // טיפול במחרוזת
    if (args[1][0] == '"') { // אם המחרוזת מתחילה בגרש
        char combined_string[1024] = {0}; // קופסה לשמירת המחרוזת
        int i = 1;
        strcat(combined_string, args[i]); // מוסיף את המילה הראשונה
        while (args[i + 1] != NULL && args[i][strlen(args[i]) - 1] != '"') { // ממשיך עד גרש סגור
            i++;
            if (strcmp(args[i], ">>") == 0) break; // עוצר כשמגיע ל- >>
            strcat(combined_string, " "); // מוסיף רווח
            strcat(combined_string, args[i]); // מוסיף את המילה
        }
        if (args[i] == NULL || strcmp(args[i], ">>") == 0 || args[i][strlen(args[i]) - 1] != '"') { // בודק סגירה של גרשיים
            printf("Error: Unterminated quoted string\n");
            return;
        }
        string = strdup(combined_string + 1); // מדלג על הגרש הראשון
        string[strlen(string) - 1] = '\0'; // מוחק את הגרש האחרון
        string_end_idx = i; // שומר את המיקום שבו המחרוזת נגמרת
    } else {
        string = strdup(args[1]); // מחרוזת בלי גרשיים
    }

    // טיפול בנתיב
    int path_idx = string_end_idx + 2; // היעד מתחיל אחרי ה- >>
    if (args[path_idx] == NULL) { // בודק שיש נתיב
        printf("Error: Missing file path\n");
        free(string);
        return;
    }

    if (args[path_idx][0] == '"') { // אם הנתיב מתחיל בגרש
        char combined_path[1024] = {0}; // קופסה לשמירת הנתיב
        int i = path_idx;
        strcat(combined_path, args[i]); // מוסיף את המילה הראשונה
        while (args[i + 1] != NULL && args[i][strlen(args[i]) - 1] != '"') { // ממשיך עד גרש סגור
            i++;
            strcat(combined_path, " "); // מוסיף רווח
            strcat(combined_path, args[i]); // מוסיף את המילה
        }
        if (args[i] == NULL || args[i][strlen(args[i]) - 1] != '"') { // בודק סגירה של גרשיים
            printf("Error: Unterminated quoted string in file path\n");
            free(string);
            return;
        }
        path = strdup(combined_path + 1); // מדלג על הגרש הראשון
        path[strlen(path) - 1] = '\0'; // מוחק את הגרש האחרון
    } else {
        path = strdup(args[path_idx]); // נתיב בלי גרשיים
    }

    // פותח את הקובץ במוד append ומוסיף את המחרוזת
    FILE *file = fopen(path, "a"); // פותח במוד "append"
    if (file == NULL) {
        printf("Error: Failed to open file\n");
        free(string);
        free(path);
        return;
    }

    fprintf(file, "%s\n", string); // מוסיף את המחרוזת לקובץ עם שורה חדשה
    fclose(file); // סוגר את הקובץ

    free(string); // שחרור הזיכרון של המחרוזת
    free(path); // שחרור הזיכרון של הנתיב
}