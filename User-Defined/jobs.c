#include "./../Helper-Functions/headers.h"
extern List *pidList;

static int cmp(const void *a, const void *b)
{
    char *p = (*(ElementType *)a).command;
    char *q = (*(ElementType *)b).command;
    char *x = (*(ElementType *)b).fullCmd;
    char *y = (*(ElementType *)b).fullCmd;

    if (!strcmp(p, q))
        return strcmp(x, y);

    return strcmp(p, q);
}

void jobs(char *tokens[], ll size)
{
    if (pidList->size)
    {
        ll stopFlag = 1, runFlag = 1, arrSize = pidList->size, i = 0;

        if (size == 2)
        {
            if (!strcmp(tokens[1], "-s"))
                runFlag = 0;
            else if (!strcmp(tokens[1], "-r"))
                stopFlag = 0;
        }

        ElementType pidArr[arrSize];

        Node *tempNode = (Node *)malloc(sizeof(Node));
        assert(tempNode);
        tempNode = pidList->head;

        while (tempNode)
        {
            pidArr[i++] = tempNode->elem;
            tempNode = tempNode->next;
        }

        qsort(pidArr, arrSize, sizeof(pidArr[0]), cmp);

        for (i = 0; i < arrSize; i++)
        {
            char path[len] = "/proc/";
            char pidStr[len];
            sprintf(pidStr, "%d", pidArr[i].pid);
            strcat(path, pidStr);
            strcat(path, "/stat");

            FILE *fd = fopen(path, "r");
            if (!fd)
                perror(path);
            else
            {
                char state[len] = {'\0'};
                for (ll j = 0; j < 3; j++)
                    fscanf(fd, "%s", state);

                if (!strcmp(state, "T") && stopFlag)
                    printf("[%lld] Stopped %s [%d]\n", pidArr[i].index, pidArr[i].fullCmd, pidArr[i].pid);
                else if (strcmp(state, "T") && runFlag)
                    printf("[%lld] Running %s [%d]\n", pidArr[i].index, pidArr[i].fullCmd, pidArr[i].pid);

                fclose(fd);
            }
        }

        free(tempNode);
    }
}