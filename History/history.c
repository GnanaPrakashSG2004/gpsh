#include "./../Helper-Functions/headers.h"
#define max(a, b) (((a) > (b)) ? (a) : (b))
extern ll historySize;
extern char *commands[21];
extern char *historyPath;

void historyAdd(char cmd[])
{
    char *temp = (char *)calloc(len, sizeof(char));
    assert(temp);
    ll index = 0;

    for (ll i = 0; i < 21; i++)
        strcpy(commands[i], "");

    FILE *f1 = fopen(historyPath, "r");
    if (f1 == NULL)
    {
        perror(historyPath);
        exit(1);
    }
    
    while (fscanf(f1, "%[^\n]s", temp) != EOF)
    {
        strcpy(commands[index++], temp);
        fgetc(f1);
    }

    free(temp);
    fclose(f1);

    if (strcmp(cmd, ""))
    {
        if (!index)
            strcpy(commands[index++], cmd);

        else if (strcmp(commands[index - 1], cmd) != 0)
            strcpy(commands[index++], cmd);
    }

    historySize = index;

    f1 = fopen(historyPath, "w");

    for (ll i = max(0, index - 20); i < index; i++)
        fprintf(f1, "%s\n", commands[i]);

    fclose(f1);
}

void historyPrint()
{
    for (ll i = max(0, historySize - 10); i < historySize; i++)
        printf("%s\n", commands[i]);
}