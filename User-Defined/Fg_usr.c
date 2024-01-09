#include "./../Helper-Functions/headers.h"
extern List *pidList;
ll err;

void Fg(char *tokens[], ll size)
{
    err = 0;

    ll index = atoll(tokens[1]);
    pid_t pid = findPID(pidList, index);

    if (pid == -1)
        write(2, "Invalid job number\n", 19);
    else
    {
        char pidStr[len];
        sprintf(pidStr, "%d", pid);
        char path[len] = "/proc/";
        strcat(path, pidStr);
        strcat(path, "/stat");

        FILE *fd = fopen(path, "r");
        if (!fd)
            perror(path);
        else
        {
            for (ll i = 0; i < 5; i++)
                fscanf(fd, "%s", pidStr);

            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);

            pid_t Pid = atoi(pidStr), present = getpgrp();
            tcsetpgrp(0, Pid);
            kill(pid, SIGCONT);

            int status;
            err = waitpid(pid, &status, WSTOPPED);
            if (err == -1)
                perror("waitpid()");
            else
            {
                tcsetpgrp(0, present);
                Delete(pidList, pid);

                signal(SIGTTIN, SIG_DFL);
                signal(SIGTTOU, SIG_DFL);
            }
        }
    }
}