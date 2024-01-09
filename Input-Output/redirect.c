#include "./../Helper-Functions/headers.h"
ll err;

void redirect(char *tokens[], ll size)
{
    char commands[len] = {'\0'};

    if (!strcmp(tokens[0], "<") || !strcmp(tokens[0], ">") || !strcmp(tokens[0], ">>") || !strcmp(tokens[size - 1], "<") || !strcmp(tokens[size - 1], ">") || !strcmp(tokens[size - 1], ">>"))
        write(2, "Missing arguments for I/O redirection\n", 38);

    else
    {
        ll inp = dup(STDIN_FILENO), out = dup(STDOUT_FILENO), fIn = 0, fOut = 0;

        for (ll i = 0; i < size; i++)
        {
            if (!strcmp(tokens[i], "<") && i < size - 1)
            {
                fIn = open(tokens[i + 1], O_RDONLY);
                if (fIn == -1)
                    perror(tokens[i + 1]);

                else
                {
                    err = dup2(fIn, STDIN_FILENO);
                    if (err == -1)
                        perror("dup2()");

                    else
                    {
                        strcat(commands, " ");
                        i++;
                    }
                }
            }

            else if (!strcmp(tokens[i], ">") && i < size - 1)
            {
                fOut = open(tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fOut == -1)
                    perror(tokens[i + 1]);

                else if (fIn != -1)
                {
                    err = dup2(fOut, STDOUT_FILENO);
                    if (err == -1)
                        perror("dup2()");

                    else
                    {
                        strcat(commands, " ");
                        i++;
                    }
                }
            }

            else if (!strcmp(tokens[i], ">>") && i < size - 1)
            {
                fOut = open(tokens[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fOut == -1)
                    perror(tokens[i + 1]);

                else if (fIn != -1)
                {
                    err = dup2(fOut, STDOUT_FILENO);
                    if (err == -1)
                        perror("dup2()");

                    else
                    {
                        strcat(commands, " ");
                        i++;
                    }
                }
            }

            else
            {
                strcat(commands, tokens[i]);
                strcat(commands, " ");
            }
        }

        char *spaceTokens[1] = {commands};

        spaceTokenise(spaceTokens, 1);

        if (fIn != -1)
            close(fIn);

        if (fOut != -1)
            close(fOut);

        dup2(inp, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);
        close(inp);
        close(out);
    }
}