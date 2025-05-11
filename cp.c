#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cp.h"

void cp(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        printf("Error: Two paths required (source and destination)\n");
        return;
    }

    char *source = NULL, *dest = NULL;
    int source_idx = 1, dest_idx = 2;

    // טיפול בנתיב המקור
    if (args[1][0] == '"') {
        char combined_source[1024] = {0};
        int i = 1;
        while (args[i] != NULL) {
            strcat(combined_source, args[i]);
            if (args[i][strlen(args[i]) - 1] == '"') {
                source_idx = i;
                break;
            }
            strcat(combined_source, " ");
            i++;
        }
        if (args[i] == NULL || args[i][strlen(args[i]) - 1] != '"') {
            printf("Error: Unterminated quoted string in source path\n");
            return;
        }
        source = strdup(combined_source + 1);
        source[strlen(source) - 1] = '\0';
        dest_idx = source_idx + 1;
    } else {
        source = strdup(args[1]);
    }

    // טיפול בנתיב היעד
    if (args[dest_idx] != NULL && args[dest_idx][0] == '"') {
        char combined_dest[1024] = {0};
        int i = dest_idx;
        while (args[i] != NULL) {
            strcat(combined_dest, args[i]);
            if (args[i][strlen(args[i]) - 1] == '"') {
                break;
            }
            strcat(combined_dest, " ");
            i++;
        }
        if (args[i] == NULL || args[i][strlen(args[i]) - 1] != '"') {
            printf("Error: Unterminated quoted string in destination path\n");
            free(source);
            return;
        }
        dest = strdup(combined_dest + 1);
        dest[strlen(dest) - 1] = '\0';
    } else if (args[dest_idx] != NULL) {
        dest = strdup(args[dest_idx]);
    } else {
        printf("Error: Missing destination path\n");
        free(source);
        return;
    }

    // העתקת הקובץ
    FILE *src_file = fopen(source, "rb");
    if (src_file == NULL) {
        printf("Error: Failed to open source file\n");
        free(source);
        free(dest);
        return;
    }

    FILE *dest_file = fopen(dest, "wb");
    if (dest_file == NULL) {
        printf("Error: Failed to open destination file\n");
        fclose(src_file);
        free(source);
        free(dest);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);
    printf("File copied from %s to %s\n", source, dest);

    free(source);
    free(dest);
}