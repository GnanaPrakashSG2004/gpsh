#include "./../Helper-Functions/headers.h"

void echo(char *string[], ll size)
{
    for (ll i = 1; i < size - 1; i++)
        printf("%s ", string[i]);
    if (size > 1)
        printf("%s", string[size - 1]);
    printf("\n");
}