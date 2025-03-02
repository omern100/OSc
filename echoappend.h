#ifndef ECHOAPPEND_H
#define ECHOAPPEND_H

/**
 * @brief מוסיף מחרוזת לקובץ במוד append
 * @details מטפל במחרוזות עם גרשיים או בלי, משתמש ב-fopen במוד "a"
 * @param args מערך של מחרוזות מהמשתמש
 * @return אין
 */
void echoappend(char **args);

#endif