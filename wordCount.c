#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordCount.h"

/**
 * @brief סופר שורות או מילים בקובץ
 * @details תומך ב--l (שורות) ו--w (מילים), משתמש ב-fopen לקריאה
 * @param args מערך של מחרוזות מהמשתמש
 * @return אין
 */
void wordCount(char **args) {
    if (args[0] == NULL || strcmp(args[0], "wc") != 0) { // בודק שהמילה הראשונה היא "wc"
        printf("Error: Invalid command\n");
        return;
    }

    if (args[1] == NULL || (strcmp(args[1], "-l") != 0 && strcmp(args[1], "-w") != 0) || args[2] == NULL) { // בודק שיש אפשרות ונתיב
        printf("Error: Expected format: wc <-l or -w> <file>\n");
        return;
    }

    char *option = args[1]; // האפשרות (-l או -w)
    char *path = NULL; // משתנה לשמירת הנתיב

    if (args[2][0] == '"') { // אם יש גרשיים
        char combined_path[1024] = {0}; // קופסה לשמירת הנתיב
        int i = 2;
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
        path = strdup(args[2]); // נתיב בלי גרשיים
    }

    // פותח את הקובץ לקריאה
    FILE *file = fopen(path, "r"); // פותח במוד "read"
    if (file == NULL) { // אם הקובץ לא קיים, לא עושה כלום
        free(path);
        return;
    }

    int lines = 0, words = 0; // משתנים לספירת שורות ומילים
    char line[1024]; // קופסה לשמירת שורה
    while (fgets(line, sizeof(line), file) != NULL) { // קורא שורה-שורה
        lines++; // סופר שורות
        char *token = strtok(line, " \n\t"); // מפצל את השורה למילים
        while (token != NULL) { // סופר מילים
            words++;
            token = strtok(NULL, " \n\t");
        }
    }

    fclose(file); // סוגר את הקובץ

    // מדפיס את התוצאה לפי האפשרות
    if (strcmp(option, "-l") == 0) {
        printf("%d\n", lines); // מדפיס מספר השורות
    } else if (strcmp(option, "-w") == 0) {
        printf("%d\n", words); // מדפיס מספר המילים
    }

    free(path); // שחרור הזיכרון
}