#ifndef LOGOUT_H
#define LOGOUT_H

/**
 * @brief סוגר את הטרמינל עם הודעה ויוצא מהתוכנית
 * @details מדפיס הודעת יציאה וסוגר את התהליך עם exit(0)
 * @param str המחרוזת שהמשתמש הכניס
 * @return אין (כי התוכנית נסגרת)
 */
void logout(char *str);

#endif