#include "headers.h"
extern char *UNAME, *path;
extern time_t tBegin, tEnd;

void prompt(char *str)
{
    char userName[len], deviceName[len];

    if (gethostname(userName, len) == -1)
    {
        perror(userName);
        exit(1);
    }

    uid_t userID = geteuid();
    errno = 0;
    struct passwd *detail = getpwuid(userID);

    if (errno != 0 && detail == NULL)
    {
        perror("getpwuid()");
        exit(1);
    }

    sprintf(deviceName, "%s", detail->pw_name);
    sprintf(str, "%s@%s:", deviceName, userName);
}

void printPrompt()
{
    printf("\033[1;32m<\033[0m\033[1;31m%s\033[0m\033[1;33m%s\033[0m\033[1;32m>\033[0m ", UNAME, path);
    fflush(stdout);
}

void printPromptNoFlush()
{
    printf("\033[1;32m<\033[0m\033[1;31m%s\033[0m\033[1;33m%s\033[0m\033[1;32m>\033[0m ", UNAME, path);
}

void timePrintPrompt()
{
    printf("\033[1;32m<\033[0m\033[1;31m%s\033[0m\033[1;33m%s\033[0m\033[1;32m took %lds>\033[0m ", UNAME, path, tEnd - tBegin);
    fflush(stdout);
}