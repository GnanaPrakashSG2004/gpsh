#include "./../Helper-Functions/headers.h"
extern char *HOME;
extern List *pidList;
ll err;
pid_t fgPid = -1;

void fg(char *tokens[], ll size)
{
    char *execTokens[size + 1];
    for (ll k = 0; k < size; k++)
    {
        if (tokens[k][0] == '~')
            sprintf(execTokens[k], "%s/%s", HOME, &tokens[k][1]);
        else
            execTokens[k] = tokens[k];
    }
    execTokens[size] = NULL;

    signal(SIGINT, ctrlC_Handler);
    signal(SIGTSTP, ctrlZ_Handler);

    pid_t forkRet = fork();
    if (forkRet == -1)
        perror("fork()");

    else
    {
        if (!forkRet)
        {
            err = execvp(execTokens[0], execTokens);
            if (err == -1)
                perror(execTokens[0]);
            exit(0);
        }

        else
        {
            fgPid = getpid();

            ElementType X;
            X.command = (char *)calloc(len, sizeof(char));
            assert(X.command);
            X.fullCmd = (char *)calloc(len, sizeof(char));
            assert(X.fullCmd);

            strcpy(X.command, execTokens[0]);
            X.pid = forkRet;
            X.index = idx(pidList);

            char *fullCmd = (char *)calloc(len, sizeof(char));
            for (ll i = 0; i < size - 1; i++)
            {
                strcat(fullCmd, tokens[i]);
                strcat(fullCmd, " ");
            }
            strcat(fullCmd, tokens[size - 1]);
            strcpy(X.fullCmd, fullCmd);

            insert(pidList, X);

            int status;
            err = waitpid(forkRet, &status, WSTOPPED);
            if (err == -1)
                perror("waitpid()");

            if (!WIFSTOPPED(status))
                Delete(pidList, X.pid);

            fgPid = -1;
        }
    }
}