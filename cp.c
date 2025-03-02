#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
void cp(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        printf("Error: Two paths required (source and destination)\n");
        return;
    }

    char *source = NULL;
    char *dest = NULL;
    int source_idx = 1;
    int dest_idx = 2;
    
    // טיפול בנתיב המקור
    if (args[1][0] == '"') {
        // מקרה שבו המקור מתחיל במירכאות
        char combined_source[1024] = {0};
        int i = 1;
        
        // מחפש את המילה שמסתיימת במירכאות
        while (args[i] != NULL) {
            strcat(combined_source, args[i]);
            
            // אם המילה הנוכחית מסתיימת במירכאות
            if (args[i][strlen(args[i])-1] == '"') {
                source_idx = i;
                break;
            }
            
            // אם לא מצאנו עדיין את הסוף, נוסיף רווח
            strcat(combined_source, " ");
            i++;
        }
        
        // אם לא מצאנו סגירת מירכאות
        if (args[i] == NULL || args[i][strlen(args[i])-1] != '"') {
            printf("Error: Unterminated quoted string in source path\n");
            return;
        }
        
        // הסרת המירכאות מההתחלה והסוף
        source = strdup(combined_source + 1);  // מדלג על המירכאה הראשונה
        source[strlen(source) - 1] = '\0';     // מסיר את המירכאה האחרונה
        
        // היעד מתחיל אחרי המקור
        dest_idx = source_idx + 1;
    } else {
        // מקרה פשוט - אין מירכאות במקור
        source = strdup(args[1]);
    }
    
    // טיפול בנתיב היעד
    if (args[dest_idx] != NULL && args[dest_idx][0] == '"') {
        // מקרה שבו היעד מתחיל במירכאות
        char combined_dest[1024] = {0};
        int i = dest_idx;
        
        // מחפש את המילה שמסתיימת במירכאות
        while (args[i] != NULL) {
            strcat(combined_dest, args[i]);
            
            // אם המילה הנוכחית מסתיימת במירכאות
            if (args[i][strlen(args[i])-1] == '"') {
                break;
            }
            
            // אם לא מצאנו עדיין את הסוף, נוסיף רווח
            strcat(combined_dest, " ");
            i++;
        }
        
        // אם לא מצאנו סגירת מירכאות
        if (args[i] == NULL || args[i][strlen(args[i])-1] != '"') {
            printf("Error: Unterminated quoted string in destination path\n");
            free(source);
            return;
        }
        
        // הסרת המירכאות מההתחלה והסוף
        dest = strdup(combined_dest + 1);  // מדלג על המירכאה הראשונה
        dest[strlen(dest) - 1] = '\0';     // מסיר את המירכאה האחרונה
    } else if (args[dest_idx] != NULL) {
        // מקרה פשוט - אין מירכאות ביעד
        dest = strdup(args[dest_idx]);
    } else {
        printf("Error: Missing destination path\n");
        free(source);
        return;
    }
    
    // יצירת הפקודה עם גרשיים לפי הצורך
    char command[2048];
    sprintf(command, "cp \"%s\" \"%s\"", source, dest);
    
    // הרצת הפקודה
    if (system(command) != 0) {
        printf("Error: Failed to copy file\n");
    }
    
    // שחרור זיכרון
    free(source);
    free(dest);
}