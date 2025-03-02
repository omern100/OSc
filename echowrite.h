#ifndef ECHOWRITE_H
#define ECHOWRITE_H

/**
 * @brief מחליף את תוכן הקובץ במחרוזת
 * @details מטפל במחרוזות עם גרשיים או בלי, משתמש ב-fopen במוד "w"
 * @param args מערך של מחרוזות מהמשתמש
 * @return אין
 */
void echowrite(char **args);

#endif