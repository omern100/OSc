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
#include "delete.h" // הכללה של delete.h
#include "mypipe.h" // הכללה של mypipe.h

void cp(char **args); // הצהרה של cp
void delete(char **args); // תיקון ההצהרה ל-char **args
void mypipe(char **argv1, char **argv2); // הצהרה של mypipe

int main() {
    Welcome(); // מפעיל את הודעת הברכה בתחילת התוכנית
    char command[100]; // מערך לשמירת הפקודה של המשתמש
    char input[100];   // מערך לשמירת הטקסט של המשתמש

    printf("Welcome to Nagar's myShell!\n"); // הודעת פתיחה למשתמש
    printf("Options: welcome, location, split, logout, cd, cp, delete, help, exit (use | for pipes)\n"); // רשימת הפקודות האפשריות

    while (1) { // לולאה שמחכה לפקודות מהמשתמש
        getLocation(); // מציג את המיקום הנוכחי לפני כל פקודה
        printf("> "); // סימן שמראה שהמשתמש צריך להקליד
        fgets(command, sizeof(command), stdin); // קבלת הפקודה מהמשתמש
        command[strcspn(command, "\n")] = 0; // הסרת ה-\n מהקלט של הפקודה

        // בדיקה אם יש pipe (|)
        char *pipe_pos = strchr(command, '|');
        if (pipe_pos != NULL) {
            *pipe_pos = '\0'; // מפריד את הפקודה לשני חלקים
            char *cmd1 = command; // החלק לפני ה-|
            char *cmd2 = pipe_pos + 1; // החלק אחרי ה-|

            // מפצל את שני החלקים למערכים
            char **argv1 = splitArgument(cmd1);
            char **argv2 = splitArgument(cmd2);

            if (argv1 == NULL || argv2 == NULL) { // בודק אם הפיצול נכשל
                printf("Error: Invalid pipe command\n");
                if (argv1) free(argv1);
                if (argv2) free(argv2);
                continue;
            }

            mypipe(argv1, argv2); // מפעיל את הצינור עם שתי התוכניות

            free(argv1); // שחרור הזיכרון של המערך הראשון
            free(argv2); // שחרור הזיכרון של המערך השני
            continue; // חוזר ללולאה
        }

        char **args = splitArgument(command); // מפצל את הפקודה למילים
        if (args == NULL) continue; // ממשיך אם הפיצול נכשל

        if (strcmp(args[0], "welcome") == 0) {
            Welcome(); // מפעיל את הודעת הברכה מהקובץ Welcome.c
        }
        else if (strcmp(args[0], "location") == 0) {
            getLocation(); // מפעיל את פונקציית המיקום מהקובץ getLocation.c
            printf("\n"); // מוסיף שורה חדשה אחרי המיקום
        }
        else if (strcmp(args[0], "split") == 0) {
            printf("Enter a string to split: "); // מבקש מהמשתמש להכניס מחרוזת
            fgets(input, sizeof(input), stdin); // קבלת המחרוזת מהמשתמש
            input[strcspn(input, "\n")] = 0; // הסרת ה-\n מהקלט של המחרוזת
            char **split_args = splitArgument(input); // מפעיל את פונקציית הפיצול
            if (split_args != NULL) { // בודק שהקצאת הזיכרון הצליחה
                printf("Words in the array:\n"); // מדפיס כותרת לתוצאות
                for (int i = 0; split_args[i] != NULL; i++) {
                    printf("args[%d] = %s\n", i, split_args[i]); // מדפיס כל מילה במערך
                }
                free(split_args); // שחרור הזיכרון של המחרוזת המפוצלת
            }
        }
        else if (strcmp(args[0], "logout") == 0) {
            logout(command); // מפעיל את פונקציית היציאה מהקובץ logout.c
        }
        else if (strcmp(args[0], "cd") == 0) {
            cd(args); // מפעיל את פונקציית שינוי התיקייה מהקובץ cd.c
        }
        else if (strcmp(args[0], "cp") == 0) {
            cp(args); // מפעיל את פונקציית ההעתקה מהקובץ cp.c
        }
        else if (strcmp(args[0], "delete") == 0) {
            delete(args); // מפעיל את פונקציית המחיקה עם args
        }
        else if (strcmp(args[0], "help") == 0) {
            printf("Options: welcome, location, split, logout, cd, cp, delete, help, exit (use | for pipes)\n"); // רשימת הפקודות האפשריות
        }
        else if (strcmp(args[0], "exit") == 0) {
            printf("Bye bye!\n"); // הודעת סיום לפני יציאה
            free(args); // שחרור הזיכרון של הפקודה
            break; // יציאה מהלולאה לסגירת התוכנית
        }
        else {
            printf("Unknown command! Try: welcome, location, split, logout, cd, cp, delete, help, exit\n"); // הודעה אם הפקודה לא מוכרת
        }
        free(args); // שחרור הזיכרון של הפקודה המפוצלת
    }

    return 0; // מחזיר 0 לסימון שהתוכנית הסתיימה בהצלחה
}