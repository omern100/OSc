#ifndef MYPIPE_H
#define MYPIPE_H

/**
 * @brief מפעיל שתי תוכניות עם צינור (pipe) ביניהן
 * @details התוכנית הראשונה שולחת את הפלט שלה כקלט לתוכנית השנייה
 * @param argv1 מערך הארגומנטים לתוכנית הראשונה
 * @param argv2 מערך הארגומנטים לתוכנית השנייה
 * @return אין
 */
void mypipe(char **argv1, char **argv2);

#endif