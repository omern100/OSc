#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include "getLocation.h"


void getLocation() {
    char cwd[1024]; // מערך לשמירת הנתיב הנוכחי
    char hostname[256]; // מערך לשמירת שם המחשב
    struct passwd *pw; // מבנה לקבלת פרטי המשתמש
    uid_t uid = getuid(); // קבלת ה-UID של המשתמש הנוכחי

    //בדיקת באגים
    // קבלת הנתיב הנוכחי
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("שגיאה ב-getcwd()");
        return;
    }

    // קבלת שם המשתמש
    pw = getpwuid(uid);
    if (pw == NULL) {
        perror("שגיאה ב-getpwuid()");
        return;
    }

    // קבלת שם המחשב
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        perror("שגיאה ב-gethostname()");
        return;
    }

    // הדפסה עם צבעים והדגשה
    // ירוק מודגש לשם המשתמש, תכלת מודגש לשם המחשב, כחול מודגש לנתיב
    printf("\033[1;32m%s\033[0m@\033[1;36m%s\033[0m:\033[1;34m%s\033[0m$ ", 
           pw->pw_name, hostname, cwd);
}