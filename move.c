#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "move.h"

/**
 * @brief מעביר קובץ ממקור ליעד
 * @details מטפל בנתיבים עם גרשיים או בלי, משתמש ב-rename להעברה
 * @param args מערך של מחרוזות מהמשתמש
 * @return אין
 */
void move(char **args) {
    if (args[0] == NULL || strcmp(args[0], "move") != 0) { // בודק שהמילה הראשונה היא "move"
        printf("Error: Invalid command\n");
        return;
    }

    if (args[1] == NULL || args[2] == NULL) { // בודק שיש שני נתיבים
        printf("Error: Two paths required (source and destination)\n");
        return;
    }

    char *source = NULL, *dest = NULL; // משתנים לנתיבים
    int source_end_idx = 1; // משתנה שמראה איפה המקור נגמר

    // טיפול בנתיב המקור
    if (args[1][0] == '"') { // אם המקור מתחיל בגרש
        char combined_source[1024] = {0}; // קופסה לשמירת המקור
        int i = 1;
        strcat(combined_source, args[i]); // מוסיף את המילה הראשונה
        while (args[i + 1] != NULL && args[i][strlen(args[i]) - 1] != '"') { // ממשיך עד גרש סגור
            i++;
            strcat(combined_source, " "); // מוסיף רווח
            strcat(combined_source, args[i]); // מוסיף את המילה
        }
        if (args[i] == NULL || args[i][strlen(args[i]) - 1] != '"') { // בודק אם יש סגירה של גרשיים
            printf("Error: Unterminated quoted string in source path\n");
            return;
        }
        source = strdup(combined_source + 1); // מדלג על הגרש הראשון
        source[strlen(source) - 1] = '\0'; // מוחק את הגרש האחרון
        source_end_idx = i; // שומר את המיקום שבו המקור נגמר
    } else {
        source = strdup(args[1]); // מקור בלי גרשיים
    }

    // טיפול בנתיב היעד
    int dest_idx = source_end_idx + 1; // היעד מתחיל אחרי המקור
    if (args[dest_idx] == NULL) { // בודק שיש יעד
        printf("Error: Missing destination path\n");
        free(source);
        return;
    }

    if (args[dest_idx][0] == '"') { // אם היעד מתחיל בגרש
        char combined_dest[1024] = {0}; // קופסה לשמירת היעד
        int i = dest_idx;
        strcat(combined_dest, args[i]); // מוסיף את המילה הראשונה
        while (args[i + 1] != NULL && args[i][strlen(args[i]) - 1] != '"') { // ממשיך עד גרש סגור
            i++;
            strcat(combined_dest, " "); // מוסיף רווח
            strcat(combined_dest, args[i]); // מוסיף את המילה
        }
        if (args[i] == NULL || args[i][strlen(args[i]) - 1] != '"') { // בודק אם יש סגירה של גרשיים
            printf("Error: Unterminated quoted string in destination path\n");
            free(source);
            return;
        }
        dest = strdup(combined_dest + 1); // מדלג על הגרש הראשון
        dest[strlen(dest) - 1] = '\0'; // מוחק את הגרש האחרון
    } else {
        dest = strdup(args[dest_idx]); // יעד בלי גרשיים
    }

    // העברת הקובץ
    if (rename(source, dest) != 0) {
        printf("Error: Failed to move file\n");
    } else {
        printf("File moved from %s to %s\n", source, dest);
    }

    free(source); // שחרור הזיכרון של המקור
    free(dest); // שחרור הזיכרון של היעד
}