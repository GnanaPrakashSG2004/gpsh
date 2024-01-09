#include "./../Helper-Functions/headers.h"
ll err;

void pipeline(char *tokens[], ll size)
{
    ll inp = dup(STDIN_FILENO), out = dup(STDOUT_FILENO);
    if (inp == -1 || out == -1)
        perror("dup()");

    else if (size)
    {
        int pipefd[size][2];
        for (ll i = 0; i < size; i++)
            pipe(pipefd[i]);

        if (tokens[0])
        {
            err = dup2(pipefd[0][1], STDOUT_FILENO);
            if (err == -1)
                perror("dup2()");
            else
            {
                spaceTokenise(&tokens[0], 1);
                close(pipefd[0][1]);
                close(STDOUT_FILENO);
            }
        }

        for (ll i = 0; i < size - 2; i++)
        {
            if (tokens[i + 1])
            {
                err = dup2(pipefd[i][0], STDIN_FILENO);
                ll err2 = dup2(pipefd[i + 1][1], STDOUT_FILENO);

                if (err == -1 || err2 == -1)
                    perror("dup2()");
                else
                {
                    spaceTokenise(&tokens[i + 1], 1);
                    close(pipefd[i][0]);
                    close(pipefd[i + 1][1]);
                    close(STDIN_FILENO);
                    close(STDOUT_FILENO);
                }
            }
        }

        if (tokens[size - 1])
        {
            err = dup2(pipefd[size - 2][0], STDIN_FILENO);
            ll err2 = dup2(out, STDOUT_FILENO);

            if (err == -1 || err2 == -1)
                perror("dup2()");

            else
            {
                spaceTokenise(&tokens[size - 1], 1);
                close(pipefd[size - 2][0]);
            }
        }

        dup2(inp, STDIN_FILENO);
        close(inp);
        close(out);
    }
}