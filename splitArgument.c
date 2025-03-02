#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splitArgument.h"

char **splitArgument(char *str) {
    int word_count = 1; // ספירת המילים
    int i;

    // סופרים את מספר המילים על ידי ספירת הרווחים
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            word_count++;
        }
    }

    // הקצאת זיכרון למערך המצביעים
    char **arguments = (char **)malloc((word_count + 1) * sizeof(char *));
    if (arguments == NULL) {
        perror("שגיאה ב-malloc()");
        return NULL;
    }

    // מפרקים את המחרוזת
    int arg_index = 0;
    arguments[arg_index] = str;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = '\0';
            arg_index++;
            arguments[arg_index] = &str[i + 1];
        }
    }
    arguments[arg_index + 1] = NULL;

    return arguments;
}
