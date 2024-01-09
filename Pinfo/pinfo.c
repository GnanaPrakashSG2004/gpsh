#include "./../Helper-Functions/headers.h"
extern char *HOME;
extern long long HomeLen;

void pinfo(char *tokens[], ll size)
{
    pid_t procID;
    char *mainPath = (char *)calloc(len, sizeof(char));
    assert(mainPath);
    char *changePath = (char *)calloc(len, sizeof(char));
    assert(changePath);
    char *procPath = (char *)calloc(len, sizeof(char));
    assert(procPath);
    char *execPath = (char *)calloc(len, sizeof(char));
    assert(execPath);

    if (size == 1)
    {
        procID = getpid();
        sprintf(procPath, "%d", procID);
    }
    else if (size > 1)
        strcpy(procPath, tokens[1]);

    strcpy(mainPath, "/proc/");
    strcat(mainPath, procPath);

    ll LEN = strlen(mainPath);

    sprintf(changePath, "%s/stat", mainPath);

    FILE *f = fopen(changePath, "r");
    if (f == NULL)
        perror(changePath);

    else
    {
        char *statVal[53];
        for (ll i = 0; i < 53; i++)
            statVal[i] = (char *)calloc(len, sizeof(char));

        ll i = 0;

        while (fscanf(f, "%s", statVal[i]) != EOF)
            i++;

        printf("pid : %s\n", statVal[0]);
        printf("process Status : %s", statVal[2]);
        if (!strcmp(statVal[4], statVal[7]))
            printf("+\n");
        else
            printf("\n");
        printf("memory : %s\n", statVal[22]);

        for (ll i = 0; i < 53; i++)
            free(statVal[i]);

        fclose(f);

        changePath[LEN] = '\0';
        strcpy(changePath, mainPath);
        strcat(changePath, "/exe");

        ll nullChar = readlink(changePath, execPath, len);
        if (nullChar == -1)
            perror(changePath);

        else
        {
            execPath[nullChar] = '\0';

            if (!strncmp(execPath, HOME, HomeLen))
                printf("executable path : %s%s\n", "~", &execPath[HomeLen]);
            else
                printf("executable path : %s\n", execPath);
        }
    }

    free(mainPath);
    free(procPath);
    free(changePath);
    free(execPath);
}