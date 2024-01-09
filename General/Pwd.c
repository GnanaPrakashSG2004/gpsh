#include "./../Helper-Functions/headers.h"

void Pwd()
{
    char *tempPath = (char *)calloc(len, sizeof(char));
    tempPath = getcwd(NULL, len);

    if (tempPath == NULL)
        perror(tempPath);
    else
    {
        printf("%s\n", tempPath);
        free(tempPath);
    }
}