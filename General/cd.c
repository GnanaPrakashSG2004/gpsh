#include "./../Helper-Functions/headers.h"
extern char *HOME;
extern char *Initial;
extern char *path;
extern char *dirPath;
extern long long HomeLen;
ll err;

void cd(char *tokens[], ll size)
{
    if (size == 1)
    {
        err = chdir(HOME);
        if (err == -1)
        {
            perror(HOME);
            exit(1);
        }

        else
        {
            sprintf(Initial, "%s", path);
            sprintf(path, "%s", "~");
        }
    }

    else if (size == 2)
    {
        if (strcmp(tokens[1], "") && tokens[1][0] == '~')
        {
            sprintf(dirPath, "%s%s", HOME, &tokens[1][1]);

            err = chdir(dirPath);
            if (err == -1)
                perror(dirPath);

            else
            {
                sprintf(dirPath, "%s", getcwd(NULL, len));
                sprintf(Initial, "%s", path);

                if (strncmp(dirPath, HOME, (size_t)HomeLen) == 0)
                    sprintf(path, "~%s", &dirPath[HomeLen]);
                else
                    sprintf(path, "%s", dirPath);
            }
        }

        else
        {
            if (strcmp(tokens[1], "") && strcmp(tokens[1], "-") == 0)
            {
                if (Initial[0] == '~')
                    sprintf(dirPath, "%s%s", HOME, &Initial[1]);
                else
                    sprintf(dirPath, "%s", Initial);

                sprintf(Initial, "%s", path);

                err = chdir(dirPath);
                if (err == -1)
                    perror(dirPath);

                else
                {
                    sprintf(dirPath, "%s", getcwd(NULL, len));
                    printf("%s\n", dirPath);

                    if (strncmp(dirPath, HOME, (size_t)HomeLen) == 0)
                        sprintf(path, "~%s", &dirPath[HomeLen]);
                    else
                        sprintf(path, "%s", dirPath);
                }
            }

            else if (strcmp(tokens[1], ""))
            {
                err = chdir(tokens[1]);
                if (err == -1)
                    perror(tokens[1]);

                else
                {
                    sprintf(dirPath, "%s", getcwd(NULL, len));
                    sprintf(Initial, "%s", path);

                    if (strncmp(dirPath, HOME, (size_t)HomeLen) == 0)
                        sprintf(path, "~%s", &dirPath[HomeLen]);
                    else
                        sprintf(path, "%s", dirPath);
                }
            }
        }
    }

    else
        write(2, "cd: too many arguments\n", 23);
}