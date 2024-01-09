#include "./../Helper-Functions/headers.h"
extern List *pidList;

void sig(char *tokens[], ll size)
{
    if (size == 3)
    {
        ll index = atoll(tokens[1]);
        pid_t pid = findPID(pidList, index);

        if (pid != -1)
        {
            ll sigVal = atoll(tokens[2]);
            kill(pid, sigVal);
        }
        else
            write(2, "Invalid job number\n", 19);
    }
    else
        write(2, "Invalid number of arguments\n", 28);
}