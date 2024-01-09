#include "./Helper-Functions/headers.h"
extern pid_t fgPid;
List *pidList;
char *HOME;
char *Initial;
char *UNAME;
char *path;
char *dirPath;
char *historyPath;
char *commands[21];
long long HomeLen;
ll historySize = 0, waitInput = 1;
time_t tBegin = 0, tEnd = 0;
char cmd[len];

int main()
{
    HOME = (char *)calloc(len, sizeof(char));
    assert(HOME);
    Initial = (char *)calloc(3 * len + 10, sizeof(char));
    assert(Initial);
    UNAME = (char *)calloc(2 * len + 5, sizeof(char));
    assert(UNAME);
    path = (char *)calloc(3 * len + 10, sizeof(char));
    assert(path);
    dirPath = (char *)calloc(3 * len + 10, sizeof(char));
    assert(dirPath);
    historyPath = (char *)calloc(len, sizeof(char));
    assert(historyPath);
    fgPid = -1;

    sprintf(HOME, "%s", getcwd(NULL, len));
    if (HOME == NULL)
    {
        perror(HOME);
        exit(1);
    }

    HomeLen = strlen(HOME);

    sprintf(dirPath, "%s", getcwd(NULL, len));
    sprintf(historyPath, "%s/%s", HOME, "History/.history.txt");

    FILE *f = fopen(historyPath, "a+");
    if (f == NULL)
    {
        perror(historyPath);
        exit(1);
    }
    fclose(f);

    if (strncmp(dirPath, HOME, (size_t)HomeLen) == 0)
        sprintf(path, "~%s", &dirPath[HomeLen]);
    else
        sprintf(path, "%s", dirPath);
    sprintf(Initial, "%s", HOME);

    prompt(UNAME);

    pidList = CreateEmptyList();

    for (ll i = 0; i < 21; i++)
        commands[i] = (char *)calloc(len, sizeof(char));

    while (1)
    {
        f = fopen(historyPath, "a+");
        if (f == NULL)
        {
            perror(historyPath);
            exit(1);
        }
        fclose(f);

        signal(SIGINT, ctrlC_Handler);
        signal(SIGTSTP, ctrlZ_Handler);

        if (tEnd - tBegin < 1)
            printPrompt();
        else
            timePrintPrompt();

        memset(cmd, '\0', len);
        rawmode();

        tBegin = tEnd = 0;
        waitInput = 0;
        tBegin = time(NULL);

        historyAdd(cmd);
        semiColonTokenise(cmd);

        tEnd = time(NULL);
        waitInput = 1;
    }

    return 0;
}