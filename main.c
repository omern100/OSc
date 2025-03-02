#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Welcome.h"
#include "getLocation.h"
#include "splitArgument.h"

int main() {
    char command[100]; // מערך לשמירת הפקודה של המשתמש
    char input[100];   // מערך לשמירת הטקסט של המשתמש

    printf("Welcome to Nagar's myShell!\n"); // הודעת פתיחה למשתמש
    printf("Options: welcome, location, split, help, exit\n"); // רשימת הפקודות האפשריות

    while (1) { // לולאה שמחכה לפקודות מהמשתמש
        printf("> "); // סימן שמראה שהמשתמש צריך להקליד
        fgets(command, sizeof(command), stdin); // קבלת הפקודה מהמשתמש
        command[strcspn(command, "\n")] = 0; // הסרת ה-\n מהקלט של הפקודה

        if (strcmp(command, "welcome") == 0) {
            Welcome(); // מפעיל את הודעת הברכה מהקובץ welcome.c
        }
        else if (strcmp(command, "location") == 0) {
            getLocation(); // מפעיל את פונקציית המיקום מהקובץ location.c
            printf("\n"); // מוסיף שורה חדשה אחרי המיקום
        }
        else if (strcmp(command, "split") == 0) {
            printf("Enter a string to split: "); // מבקש מהמשתמש להכניס מחרוזת
            fgets(input, sizeof(input), stdin); // קבלת המחרוזת מהמשתמש
            input[strcspn(input, "\n")] = 0; // הסרת ה-\n מהקלט של המחרוזת
            char **args = splitArgument(input); // מפעיל את פונקציית הפיצול מהקובץ split.c
            if (args != NULL) { // בודק שהקצאת הזיכרון הצליחה
                printf("Words in the array:\n"); // מדפיס כותרת לתוצאות
                for (int i = 0; args[i] != NULL; i++) {
                    printf("args[%d] = %s\n", i, args[i]); // מדפיס כל מילה במערך
                }
                free(args); // שחרור הזיכרון שהוקצה למערך
            }
        }
        else if (strcmp(command, "exit") == 0) {
            printf("Bye bye!\n"); // הודעת סיום לפני יציאה
            break; // יציאה מהלולאה לסגירת התוכנית
        }
        else if (strcmp(command, "help") == 0) {
            printf("Options: welcome, location, split, help, exit\n"); // רשימת הפקודות האפשריות
        }
        else {
            printf("Unknown command! Try: welcome, location, split, help, exit\n"); // הודעה אם הפקודה לא מוכרת
        }
    }

    return 0; // מחזיר 0 לסימון שהתוכנית הסתיימה בהצלחה
}