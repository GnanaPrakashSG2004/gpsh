#include "./../Helper-Functions/headers.h"
extern char *HOME;
ll err, nFiles, aFlag = 0, lFlag = 0;

static int comparatorFunc(const void *a, const void *b)
{
    char *p = (*(struct dirent **)a)->d_name;
    char *q = (*(struct dirent **)b)->d_name;

    return strcasecmp(p, q);
}

static void lflag(struct dirent *list, struct stat temp)
{
    char permissions[11] = {'-'}, timePrint[20] = {'\0'};
    permissions[10] = '\0';

    if ((temp.st_mode & __S_IFMT) == __S_IFLNK)
        permissions[0] = 'l';

    else if ((temp.st_mode & __S_IFMT) == __S_IFDIR)
        permissions[0] = 'd';

    permissions[1] = ((temp.st_mode & S_IRUSR) == S_IRUSR) ? 'r' : '-';
    permissions[2] = ((temp.st_mode & S_IWUSR) == S_IWUSR) ? 'w' : '-';
    permissions[3] = ((temp.st_mode & S_IXUSR) == S_IXUSR) ? 'x' : '-';

    permissions[4] = ((temp.st_mode & S_IRGRP) == S_IRGRP) ? 'r' : '-';
    permissions[5] = ((temp.st_mode & S_IWGRP) == S_IWGRP) ? 'w' : '-';
    permissions[6] = ((temp.st_mode & S_IXGRP) == S_IXGRP) ? 'x' : '-';

    permissions[7] = ((temp.st_mode & S_IROTH) == S_IROTH) ? 'r' : '-';
    permissions[8] = ((temp.st_mode & S_IWOTH) == S_IWOTH) ? 'w' : '-';
    permissions[9] = ((temp.st_mode & S_IXOTH) == S_IXOTH) ? 'x' : '-';

    printf("%-12s %3lu %10s %10s %6ld ", permissions, temp.st_nlink, getpwuid(temp.st_uid)->pw_name, getgrgid(temp.st_gid)->gr_name, temp.st_size);

    if (time(NULL) - temp.st_mtim.tv_sec <= 15780000)
        strftime(timePrint, 20, "%b %d %H:%M", localtime(&(temp.st_mtim.tv_sec)));
    else
        strftime(timePrint, 20, "%b %d  %Y", localtime(&(temp.st_mtim.tv_sec)));
    printf("%s ", timePrint);

    if ((temp.st_mode & __S_IFMT) == __S_IFLNK)
        printf("\033[1;96m%s\033[0m\n", list->d_name);
    else if ((temp.st_mode & __S_IFMT) == __S_IFDIR)
        printf("\033[1;34m%s\033[0m\n", list->d_name);
    else if ((temp.st_mode & __S_IFMT) == __S_IFREG)
    {
        if ((temp.st_mode & S_IXUSR) == S_IXUSR)
            printf("\033[1;32m%s\033[0m\n", list->d_name);
        else
            printf("%s\n", list->d_name);
    }
}

static void Print(char *dir[], ll size)
{
    for (ll i = 1; i < size; i++)
    {
        if (dir[i][0] != '-')
        {
            struct dirent **list;

            char *tempPath = (char *)calloc(3 * len + 10, sizeof(char));
            assert(tempPath);

            if (dir[i][0] != '~')
                sprintf(tempPath, "%s", dir[i]);
            else
                sprintf(tempPath, "%s/%s", HOME, &dir[i][1]);

            struct stat temp;
            err = lstat(tempPath, &temp);
            if (err == -1)
                perror(tempPath);
            else
            {
                if ((temp.st_mode & __S_IFMT) == __S_IFDIR)
                {
                    ll n = scandir(tempPath, &list, NULL, alphasort);
                    if (n == -1)
                        perror(tempPath);
                    else
                    {
                        qsort(list, n, sizeof(list[0]), comparatorFunc);

                        if (nFiles > 1)
                        {
                            if (dir[i][0] == '~')
                                printf("%s%s:\n", HOME, &dir[i][1]);
                            else
                                printf("%s:\n", dir[i]);
                        }

                        long total = 0;

                        if (lFlag)
                        {
                            for (ll j = 0; j < n; j++)
                            {
                                char *tempFileName = (char *)calloc(3 * len + 10, sizeof(char));
                                sprintf(tempFileName, "%s/%s", tempPath, list[j]->d_name);

                                struct stat tempStat;
                                err = lstat(tempFileName, &tempStat);
                                if (err == -1)
                                    perror(tempFileName);
                                else if (aFlag || (!aFlag && list[j]->d_name[0] != '.'))
                                    total += tempStat.st_blocks;

                                free(tempFileName);
                            }

                            printf("total %ld\n", total / 2);
                        }

                        for (ll j = 0; j < n; j++)
                        {
                            char *tempFileName = (char *)calloc(3 * len + 10, sizeof(char));
                            assert(tempFileName);
                            sprintf(tempFileName, "%s/%s", tempPath, list[j]->d_name);

                            struct stat tempStat;
                            err = lstat(tempFileName, &tempStat);
                            if (err == -1)
                                perror(tempFileName);
                            else
                            {
                                if (lFlag && (aFlag || (!aFlag && list[j]->d_name[0] != '.')))
                                    lflag(list[j], tempStat);

                                else if (aFlag || (!aFlag && list[j]->d_name[0] != '.'))
                                {
                                    if ((tempStat.st_mode & __S_IFMT) == __S_IFLNK)
                                        printf("\033[1;96m%s\033[0m\n", list[j]->d_name);
                                    else if ((tempStat.st_mode & __S_IFMT) == __S_IFDIR)
                                        printf("\033[1;34m%s\033[0m\n", list[j]->d_name);
                                    else if ((tempStat.st_mode & __S_IFMT) == __S_IFREG)
                                    {
                                        if ((tempStat.st_mode & S_IXUSR) == S_IXUSR)
                                            printf("\033[1;32m%s\033[0m\n", list[j]->d_name);
                                        else
                                            printf("%s\n", list[j]->d_name);
                                    }
                                }
                            }

                            free(tempFileName);
                        }

                        if (nFiles > 1)
                            printf("\n");
                    }
                }

                else if ((temp.st_mode & __S_IFMT) == __S_IFREG)
                {
                    if (lFlag)
                    {
                        char permissions[11] = {'-'};
                        permissions[10] = '\0';

                        if ((temp.st_mode & __S_IFMT) == __S_IFLNK)
                            permissions[0] = 'l';
                        else if ((temp.st_mode & __S_IFMT) == __S_IFDIR)
                            permissions[0] = 'd';

                        permissions[1] = ((temp.st_mode & S_IRUSR) == S_IRUSR) ? 'r' : '-';
                        permissions[2] = ((temp.st_mode & S_IWUSR) == S_IWUSR) ? 'w' : '-';
                        permissions[3] = ((temp.st_mode & S_IXUSR) == S_IXUSR) ? 'x' : '-';

                        permissions[4] = ((temp.st_mode & S_IRGRP) == S_IRGRP) ? 'r' : '-';
                        permissions[5] = ((temp.st_mode & S_IWGRP) == S_IWGRP) ? 'w' : '-';
                        permissions[6] = ((temp.st_mode & S_IXGRP) == S_IXGRP) ? 'x' : '-';

                        permissions[7] = ((temp.st_mode & S_IROTH) == S_IROTH) ? 'r' : '-';
                        permissions[8] = ((temp.st_mode & S_IWOTH) == S_IWOTH) ? 'w' : '-';
                        permissions[9] = ((temp.st_mode & S_IXOTH) == S_IXOTH) ? 'x' : '-';

                        printf("%-12s %4lu %10s %10s %-6ld %10ld ", permissions, temp.st_nlink, getpwuid(temp.st_uid)->pw_name, getgrgid(temp.st_gid)->gr_name, temp.st_size, temp.st_mtim.tv_sec);
                    }

                    if ((temp.st_mode & __S_IFMT) == __S_IFLNK)
                        printf("\033[1;96m%s\033[0m\n", tempPath);

                    else if ((temp.st_mode & S_IXUSR) == S_IXUSR)
                        printf("\033[1;32m%s\033[0m\n", tempPath);
                    else
                        printf("%s\n", tempPath);

                    if (nFiles > 1)
                        printf("\n");
                }

                free(tempPath);
            }
        }
    }

    aFlag = lFlag = 0;
}

void ls(char *dir[], ll size)
{
    nFiles = size - 1;

    for (ll i = 1; i < size; i++)
        if (strcmp(dir[i], ""))
            if (dir[i][0] == '-')
            {
                ll length = strlen(dir[i]);

                for (ll j = 1; j < length; j++)
                {
                    if (dir[i][j] == 'a')
                        aFlag = 1;
                    else if (dir[i][j] == 'l')
                        lFlag = 1;
                }
                nFiles--;
            }

    if (nFiles)
        Print(dir, size);
    else
    {
        char *tempDir[size + 1];
        for (ll i = 0; i < size; i++)
            tempDir[i] = dir[i];
        tempDir[size] = ".";
        Print(tempDir, size + 1);
    }

    nFiles = 0;
}