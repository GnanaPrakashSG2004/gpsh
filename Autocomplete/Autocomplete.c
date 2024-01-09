#include "./../Helper-Functions/headers.h"
extern ll startIdx, slashIdx, endIdx, slashFlag;
extern char *HOME, *UNAME, *path, cmd[len];
ll err;

static void rePrint()
{
    printf("\r");
    printPrompt();
    printf("%s", cmd);
    fflush(stdout);
}

void autocomplete()
{
    err = 0;

    if (cmd[0] != '\0')
    {
        char *dirPath = (char *)calloc(len, sizeof(char));
        assert(dirPath);

        if (!slashFlag)
            strcpy(dirPath, "./");
        else
            strncpy(dirPath, &cmd[startIdx], slashIdx - startIdx + 1);

        if (dirPath && dirPath[0] != ' ')
        {
            char *finalPath = (char *)calloc(len, sizeof(char));
            assert(finalPath);
            strcpy(finalPath, dirPath);

            if (dirPath[0] == '~')
                sprintf(finalPath, "%s/%s", HOME, &dirPath[1]);

            struct dirent **fileList;
            ll numFile = scandir(finalPath, &fileList, NULL, alphasort), numMatch = 0;
            if (numFile == -1)
                perror(finalPath);

            else
            {
                struct dirent *matchList[numFile];
                for (ll i = 0; i < numFile; i++)
                    matchList[i] = NULL;

                char *name = (char *)calloc(len, sizeof(char));
                if (!slashFlag)
                    strncpy(name, &cmd[startIdx], endIdx - startIdx + 1);
                else
                    strncpy(name, &cmd[slashIdx + 1], endIdx - slashIdx);
                ll nameLen = strlen(name);

                for (ll i = 0; i < numFile; i++)
                    if (!strncmp(name, fileList[i]->d_name, nameLen) || !strcmp(name, " ") || !strcmp(finalPath, " "))
                        if (strcmp(fileList[i]->d_name, ".") && strcmp(fileList[i]->d_name, ".."))
                            matchList[numMatch++] = fileList[i];

                if (numMatch == 1)
                {
                    char *filePath = (char *)calloc(len, sizeof(char));
                    sprintf(filePath, "%s%s", finalPath, matchList[0]->d_name);
                    struct stat tempStat;
                    err = stat(filePath, &tempStat);

                    if (err == -1)
                        perror(filePath);
                    else
                    {
                        strcat(cmd, &matchList[0]->d_name[nameLen]);
                        if ((tempStat.st_mode & __S_IFMT) == __S_IFDIR)
                            strcat(cmd, "/");
                        else if ((tempStat.st_mode & __S_IFMT) == __S_IFREG && cmd[strlen(cmd) - 1] != ' ')
                            strcat(cmd, " ");

                        rePrint();
                    }

                    free(filePath);
                }

                else if (numMatch > 0)
                {
                    ll strCom = 0;
                    while (!strncmp(matchList[0]->d_name, matchList[numMatch - 1]->d_name, strCom))
                        strCom++;

                    if (strCom - 1 > nameLen)
                    {
                        strncat(cmd, &matchList[0]->d_name[nameLen], strCom - nameLen - 1);
                        rePrint();
                    }

                    else
                    {
                        char *filePath = (char *)calloc(len, sizeof(char));
                        assert(filePath);

                        printf("\n");
                        for (ll i = 0; i < numMatch; i++)
                        {
                            sprintf(filePath, "%s%s", finalPath, matchList[i]->d_name);
                            struct stat tempStat;
                            err = stat(filePath, &tempStat);

                            if (err == -1)
                                perror(filePath);
                            else
                            {
                                if ((tempStat.st_mode & __S_IFMT) == __S_IFDIR)
                                    printf("%s/\n", matchList[i]->d_name);
                                else
                                    printf("%s\n", matchList[i]->d_name);
                            }
                        }
                        rePrint();

                        free(filePath);
                    }
                }

                else
                    printf("\a");
                free(name);
            }
            free(finalPath);
        }
        free(dirPath);
    }
}