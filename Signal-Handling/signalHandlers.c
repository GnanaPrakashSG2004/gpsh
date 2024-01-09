#include "./../Helper-Functions/headers.h"
extern pid_t fgPid;
extern ll waitInput;

void ctrlC_Handler(int signo)
{
    signal(SIGINT, ctrlC_Handler);

    if (waitInput)
    {
        printf("^C\n");
        printPrompt();
    }
    else if (fgPid != -1)
        kill(fgPid, SIGINT);
    fgPid = -1;
}

void ctrlZ_Handler(int signo)
{
    signal(SIGTSTP, ctrlZ_Handler);

    if (waitInput)
    {
        printf("^Z\n");
        printPrompt();
    }
    else if (fgPid != -1)
        kill(fgPid, SIGTSTP);
    fgPid = -1;
}