#include "./../Helper-Functions/headers.h"
extern List *pidList;

void Bg(char *tokens[], ll size)
{
    ll index = atoll(tokens[1]);
    pid_t pid = findPID(pidList, index);

    if (pid == -1)
        write(2, "Invalid job number\n", 19);
    else
        kill(pid, SIGCONT);
}