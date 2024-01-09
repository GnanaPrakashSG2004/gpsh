#include "./../Helper-Functions/headers.h"
extern char *UNAME, *path, cmd[len];
extern time_t tEnd, tBegin;
struct termios orig_termios;

static void die(const char *s)
{
    perror(s);
    exit(1);
}

static void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr()");
}

static void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr()");
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr()");
}

ll startIdx = 0, endIdx = 0, slashIdx = 0, slashFlag = 0;

void rawmode()
{
    char c;
    setbuf(stdout, NULL);
    enableRawMode();

    memset(cmd, '\0', len);
    ll inpIdx = 0;

    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        ll lenCMD = inpIdx = strlen(cmd);
        startIdx = endIdx = slashIdx = slashFlag = 0;
        for (ll i = 0; i < lenCMD; i++)
        {
            if (cmd[i] == ' ')
            {
                startIdx = slashIdx = endIdx = i;
                slashFlag = 0;
            }

            if (i > 0 && cmd[i - 1] == ' ' && cmd[i] != ' ')
                startIdx = i;

            if (!slashFlag)
                slashIdx = startIdx;

            if (cmd[i] != ' ')
                endIdx = i;

            if (cmd[i] == '/')
            {
                slashIdx = i;
                slashFlag = 1;
            }
        }

        if (iscntrl(c))
        {
            if (c == 10)
            {
                printf("\n");
                break;
            }

            else if (c == 27)
            {
                char buf[3];
                buf[2] = 0;
                if (read(STDIN_FILENO, buf, 2) == 2)
                    printf("^[%s", buf);
            }

            else if (c == 127)
            {
                if (inpIdx > 0)
                {
                    cmd[--inpIdx] = '\0';
                    printf("\b \b");
                }
            }

            else if (c == 9)
                autocomplete();

            else if (c == 4)
            {
                printf("\n");
                exit(0);
            }

            else
                printf("%c\n", c);
        }

        else
        {
            cmd[inpIdx++] = c;
            printf("%c", c);
        }
    }

    disableRawMode();
}