#ifndef SPLITARGUMENT_H
#define SPLITARGUMENT_H
/**
 * @brief מפרקת מחרוזת למערך של מילים
 * @details מחליפה רווחים ב-\0 ומחזירה מערך מצביעים למילים
 * @param str המחרוזת שיש לפצל
 * @return מערך של מצביעים למילים, או NULL אם הקצאה נכשלה
 */
char **splitArgument(char *str);

#endif