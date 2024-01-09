#include "./../Helper-Functions/headers.h"
extern List *pidList;
extern char *HOME;
extern ll waitInput;
ElementType X;
ll err;

static void handler()
{
    int status;
    pid_t retVal = waitpid(-1, &status, WNOHANG | WUNTRACED);

    if (retVal > 0 && (WIFEXITED(status) || WIFSIGNALED(status)))
    {
        if (WEXITSTATUS(status) || WIFSIGNALED(status))
            printf("%s with pid = %d exited abnormally\n", findCMD(pidList, retVal), retVal);

        else
            printf("%s with pid = %d exited normally\n", findCMD(pidList, retVal), retVal);

        if (waitInput)
            printPromptNoFlush();

        Delete(pidList, retVal);
    }
}

void bg(char *tokens[], ll size)
{
    pid_t forkRet = fork();
    if (forkRet == -1)
        perror("fork()");

    else
    {
        if (!forkRet)
        {
            err = setpgid(0, 0);
            if (err == -1)
                perror("setpgid()");

            else
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

                if (strcmp(execTokens[0], "echo") && strcmp(execTokens[0], "pwd") && strcmp(execTokens[0], "cd") && strcmp(execTokens[0], "ls") && strcmp(execTokens[0], "pinfo") && strcmp(execTokens[0], "discover") && strcmp(execTokens[0], "history") && strcmp(execTokens[0], ""))
                {
                    err = execvp(execTokens[0], execTokens);
                    if (err == -1)
                        perror(execTokens[0]);
                }
            }
        }

        else if (strcmp(tokens[0], ""))
        {
            X.command = (char *)calloc(len, sizeof(char));
            assert(X.command);
            X.fullCmd = (char *)calloc(len, sizeof(char));
            assert(X.fullCmd);

            strcpy(X.command, tokens[0]);
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

            printf("[%lld] %d\n", idx(pidList), forkRet);
            insert(pidList, X);

            signal(SIGCHLD, handler);
        }
    }
}