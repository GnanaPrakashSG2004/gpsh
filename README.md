# <center> gpsh

## <ins>Invoking the shell:</ins>
- Run `make` and then `./a.out` on the terminal of your system to invoke the shell.
- Run `make clean` to remove the `.o` and the executable files.

<hr>

## <ins>File Structure:</ins>
```
.
├── Autocomplete              --- Code implementing autocompletion ---
│   ├── Autocomplete.c
│   └── Autocomplete.h
├── Fg-Bg                     --- Codes implementing foreground and background processes ---
│   ├── bg.c
│   ├── bg.h
│   ├── fg.c
│   └── fg.h
├── General                   --- Codes implementing cd, ls, echo, pwd ---
│   ├── cd.c
│   ├── cd.h
│   ├── echo.c
│   ├── echo.h
│   ├── ls.c
│   ├── ls.h
│   ├── Pwd.c
│   └── Pwd.h
├── Helper-Functions          --- Codes common to all functions ---
│   ├── headers.h
│   ├── prompt.c
│   ├── prompt.h
│   ├── tokenise.c
│   └── tokenise.h
├── History                   --- Code implementing history command ---
│   ├── history.c
│   └── history.h
├── Input-Output              --- Code implementing I/O redirection ---
│   ├── redirect.c
│   └── redirect.h
├── Linked-List               --- Linked List ADT ---
│   ├── linkedList.c
│   └── linkedList.h
├── Makefile
├── Pinfo                     --- Code implementing pinfo command ---
│   ├── pinfo.c
│   └── pinfo.h
├── Pipelining                --- Code implementing pipelining ---
│   ├── pipeline.c
│   └── pipeline.h
├── Rawmode                   --- Code implementing rawmode ---
│   ├── rawmode.c
│   └── rawmode.h
├── README.md
├── shell.c                   --- Main code ---
├── Signal-Handling           --- Code implementing signal handling ---
│   ├── signalHandlers.c
│   └── signalHandlers.h
└── User-Defined              --- Code implementing user defined commands ---
    ├── Bg_usr.c
    ├── Bg_usr.h
    ├── discover.c
    ├── discover.h
    ├── Fg_usr.c
    ├── Fg_usr.h
    ├── jobs.c
    ├── jobs.h
    ├── sig.c
    └── sig.h
```

<hr>

## <ins>Assumptions:</ins>
- The command length can be atmost `1e3` characters.
- The absolute/relative path of the directories can be atmost `1e3` characters.
- Tokenising is in the order: `;`, `&`, `|` and `" "`(space character) characters.
- `cd` command does not handle cases where `~` is present in the path but it is not the start character. This is done as the bash shell also follows the same approach.
- Do not run commands where both the background and foreground processes end at the same time as two interrupts occur at the same time and a segmentation fault might occur sometimes.
- Background processes like `vi &` and `nano &` might not function well on few systems.
- In the case of multiple foreground processes, the total time taken to execute all of the foreground processes is printed in the prompt.
- The `pinfo` command prints only the first argument of the input provided, i.e., it prints the command to be executed without its parameters.
- It is assumed that only the file names are provided in the `file_name` argument enclosed in `""` for the `discover` command.
-  All the commands are stored in `.history.txt` file in the `History` directory.
- It is assumed that arguments are present on either side of `<`, `>` and `>>`. Else, an error statement is printed and the shell program waits for the next command.
- The commands in the pipelines are executed in the order left to right one after the other.
- `jobs` command only handles flags of the type `-s` and `-r` and prints the entire input provided.

<hr>

# <center> End Of README