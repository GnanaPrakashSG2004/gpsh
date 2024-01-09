#include "headers.h"
extern char *HOME;
ll err;
ll GFlag = 0, LFlag = 0, GGFlag = 0, fgFlag = 0;

void spaceTokenise(char *tokens[], ll size)
{
    for (ll i = 0; i < size; i++)
    {
        char *spaceTokens[len];
        ll j = 0;

        char *spaceToken = strtok(tokens[i], " \t");

        while (spaceToken)
        {
            spaceTokens[j++] = spaceToken;
            spaceToken = strtok(NULL, " ");
        }

        if (j)
        {
            GFlag = 0, LFlag = 0, GGFlag = 0;
            for (ll k = 0; k < j && !GFlag && !LFlag && !GGFlag; k++)
            {
                if (!strcmp(spaceTokens[k], "<"))
                    LFlag = 1;
                else if (!strcmp(spaceTokens[k], ">"))
                    GFlag = 1;
                else if (!strcmp(spaceTokens[k], ">>"))
                    GGFlag = 1;
            }

            if (LFlag || GFlag || GGFlag)
                redirect(spaceTokens, j);

            else if (strcmp(spaceTokens[0], "echo") == 0)
                echo(spaceTokens, j);

            else if (strcmp(spaceTokens[0], "pwd") == 0)
                Pwd();

            else if (strcmp(spaceTokens[0], "cd") == 0)
                cd(spaceTokens, j);

            else if (strcmp(spaceTokens[0], "ls") == 0)
                ls(spaceTokens, j);

            else if (strcmp(spaceTokens[0], "pinfo") == 0)
                pinfo(spaceTokens, j);

            else if (strcmp(spaceTokens[0], "discover") == 0)
                discover(spaceTokens, j);

            else if (strcmp(spaceTokens[0], "history") == 0)
                historyPrint();
            
            else if (strcmp(spaceTokens[0], "jobs") == 0)
                jobs(spaceTokens, j);

            else if (strcmp(spaceTokens[0], "sig") == 0)
                sig(spaceTokens, j);

            else if (strcmp(spaceTokens[0], "fg") == 0)
                Fg(spaceTokens, j);

            else if (strcmp(spaceTokens[0], "bg") == 0)
                Bg(spaceTokens, j);

            else if (i == size - 1 && strcmp(spaceTokens[0], "") && fgFlag)
                fg(spaceTokens, j);

            else if ((i != size - 1 && strcmp(spaceTokens[0], "")) || !fgFlag)
                bg(spaceTokens, j);
        }
    }
}

static void pipeTokenise(char *tokens[], ll size)
{
    for (ll i = 0; i < size; i++)
    {
        char *pipeTokens[len];
        ll j = 0;

        char *temp = (char *)calloc(len, sizeof(char));
        assert(temp);
        strcpy(temp, tokens[i]);
        strcat(temp, " ");
        char *pipeToken = strtok(temp, "|");

        while (pipeToken)
        {
            pipeTokens[j++] = pipeToken;
            pipeToken = strtok(NULL, "|");
        }

        if (i == size - 1)
            fgFlag = 1;
        else
            fgFlag = 0;

        if (j <= 1)
            spaceTokenise(pipeTokens, j);
        else
            pipeline(pipeTokens, j);
    }
}

static void andTokenise(char *tokens[], ll size)
{
    for (ll i = 0; i < size; i++)
    {
        char *andTokens[len];
        ll j = 0;

        char *temp = (char *)calloc(len, sizeof(char));
        assert(temp);
        strcpy(temp, tokens[i]);
        strcat(temp, " ");
        char *andToken = strtok(temp, "&");

        while (andToken)
        {
            andTokens[j++] = andToken;
            andToken = strtok(NULL, "&");
        }

        pipeTokenise(andTokens, j);
    }
}

void semiColonTokenise(char *tokens)
{
    char *semiTokens[len];
    ll i = 0;
    char *semiToken = strtok(tokens, ";");

    while (semiToken)
    {
        semiTokens[i++] = semiToken;
        semiToken = strtok(NULL, ";");
    }

    andTokenise(semiTokens, i);
}