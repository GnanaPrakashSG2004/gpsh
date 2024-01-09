#include "./../Helper-Functions/headers.h"
extern char *HOME;
ll fFlag = 0, dFlag = 0, dotFlag = 0, err;
char *dirpath, *filepath, *paramPath;

static void search(char *dir, char *file)
{
    struct stat temp;
    err = stat(dir, &temp);
    if (err == -1)
        perror(dir);

    else
    {
        if ((temp.st_mode & __S_IFMT) == __S_IFDIR)
        {
            DIR *dirTraverser = opendir(dir);
            if (dirTraverser == NULL)
                perror(dir);

            else
            {
                errno = 0;

                struct dirent *dirList = readdir(dirTraverser);
                if (errno != 0 && dirList == NULL)
                    perror(dir);

                else
                {
                    if (dFlag && !strcmp(file, "") && !dotFlag)
                    {
                        printf(".\n");
                        dotFlag = 1;
                    }

                    while (dirList)
                    {
                        if (strcmp(dirList->d_name, ".") && strcmp(dirList->d_name, ".."))
                        {
                            ll lenDir = strlen(dirpath), lenParam = strlen(paramPath);

                            if (strcmp(dirpath, "/"))
                                strcat(dirpath, "/");
                            strcat(dirpath, dirList->d_name);
                            if (strcmp(paramPath, "/"))
                                strcat(paramPath, "/");
                            strcat(paramPath, dirList->d_name);

                            struct stat tempStat;
                            err = stat(paramPath, &tempStat);
                            if (err == -1)
                                perror(paramPath);

                            else
                            {
                                if ((tempStat.st_mode & __S_IFMT) == __S_IFDIR)
                                {
                                    if ((!strcmp(file, "") || !strcmp(dirList->d_name, file)) && dFlag)
                                        printf("%s\n", dirpath);

                                    search(paramPath, file);
                                }

                                else if ((tempStat.st_mode & __S_IFMT) == __S_IFREG)
                                    if ((!strcmp(file, "") || !strcmp(dirList->d_name, file)) && fFlag)
                                        printf("%s\n", dirpath);

                                dirpath[lenDir] = paramPath[lenParam] = '\0';
                            }
                        }

                        errno = 0;
                        dirList = readdir(dirTraverser);
                        if (errno != 0 && dirList == NULL)
                            perror(dir);
                    }
                }
                closedir(dirTraverser);
            }
        }
    }
}

void discover(char *tokens[], ll size)
{
    ll dirFlag = 0, fileFlag = 0;
    dFlag = fFlag = 0;
    dirpath = (char *)calloc(len, sizeof(char));
    assert(dirpath);
    filepath = (char *)calloc(len, sizeof(char));
    assert(filepath);
    paramPath = (char *)calloc(len, sizeof(char));
    assert(paramPath);

    for (ll i = 1; i < size; i++)
        if (strcmp(tokens[i], ""))
            if (tokens[i][0] == '-')
            {
                ll length = strlen(tokens[i]);

                for (ll j = 1; j < length; j++)
                {
                    if (tokens[i][j] == 'd')
                        dFlag = 1;
                    else if (tokens[i][j] == 'f')
                        fFlag = 1;
                }
            }

    if (!dFlag && !fFlag)
        dFlag = fFlag = 1;

    for (ll i = 1; i < size; i++)
        if (strcmp(tokens[i], ""))
            if (tokens[i][0] != '-')
            {
                if (tokens[i][0] != '~' && tokens[i][0] != '\"')
                {
                    sprintf(paramPath, "%s", tokens[i]);
                    dirFlag = 1;
                }

                else if (tokens[i][0] == '~')
                {
                    sprintf(paramPath, "%s%s", HOME, &tokens[i][1]);
                    dirFlag = 1;
                }

                else if (tokens[i][0] == '\"')
                {
                    strncpy(filepath, &tokens[i][1], strlen(tokens[i]) - 2);
                    fileFlag = 1;
                }

                if (tokens[i][0] != '\"')
                    strcpy(dirpath, tokens[i]);
            }

    if (!dirFlag)
    {
        strcpy(dirpath, ".");
        strcpy(paramPath, ".");
    }
    if (!fileFlag)
        strcpy(filepath, "");

    ll dirLen = strlen(dirpath), paramLen = strlen(paramPath);
    if (dirLen > 1 && dirpath[dirLen - 1] == '/')
        dirpath[dirLen - 1] = '\0';
    if (paramLen > 1 && paramPath[paramLen - 1] == '/')
        paramPath[paramLen - 1] = '\0';

    dotFlag = 0;
    search(paramPath, filepath);
    dotFlag = 0;

    free(dirpath);
    free(paramPath);
    free(filepath);
}