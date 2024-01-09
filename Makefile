flags = -Wall -pedantic -g

all: shell.o prompt.o tokenise.o echo.o Pwd.o cd.o ls.o bg.o fg.o linkedList.o pinfo.o discover.o history.o redirect.o pipeline.o jobs.o sig.o Fg_usr.o Bg_usr.o signalHandlers.o rawmode.o Autocomplete.o
	gcc $(flags) *.o

shell.o: ./shell.c
	gcc $(flags) -c ./shell.c

prompt.o: ./Helper-Functions/prompt.c
	gcc $(flags) -c ./Helper-Functions/prompt.c

tokenise.o: ./Helper-Functions/tokenise.c
	gcc $(flags) -c ./Helper-Functions/tokenise.c

echo.o: ./General/echo.c
	gcc $(flags) -c ./General/echo.c

Pwd.o: ./General/Pwd.c
	gcc $(flags) -c ./General/Pwd.c

cd.o: ./General/cd.c
	gcc $(flags) -c ./General/cd.c

ls.o: ./General/ls.c
	gcc $(flags) -c ./General/ls.c

bg.o: ./Fg-Bg/bg.c
	gcc $(flags) -c ./Fg-Bg/bg.c

fg.o: ./Fg-Bg/fg.c
	gcc $(flags) -c ./Fg-Bg/fg.c

linkedList.o: ./Linked-List/linkedList.c
	gcc $(flags) -c ./Linked-List/linkedList.c

pinfo.o: ./Pinfo/pinfo.c
	gcc $(flags) -c ./Pinfo/pinfo.c

discover.o: ./User-Defined/discover.c
	gcc $(flags) -c ./User-Defined/discover.c

history.o: ./History/history.c
	gcc $(flags) -c ./History/history.c

redirect.o: ./Input-Output/redirect.c
	gcc $(flags) -c ./Input-Output/redirect.c

pipeline.o: ./Pipelining/pipeline.c
	gcc $(flags) -c ./Pipelining/pipeline.c

jobs.o: ./User-Defined/jobs.c
	gcc $(flags) -c ./User-Defined/jobs.c

sig.o: ./User-Defined/sig.c
	gcc $(flags) -c ./User-Defined/sig.c

Fg_usr.o: ./User-Defined/Fg_usr.c
	gcc $(flags) -c ./User-Defined/Fg_usr.c

Bg_usr.o: ./User-Defined/Bg_usr.c
	gcc $(flags) -c ./User-Defined/Bg_usr.c

signalHandlers.o: ./Signal-Handling/signalHandlers.c
	gcc $(flags) -c ./Signal-Handling/signalHandlers.c

rawmode.o: ./Rawmode/rawmode.c
	gcc $(flags) -c ./Rawmode/rawmode.c

Autocomplete.o: ./Autocomplete/Autocomplete.c
	gcc $(flags) -c ./Autocomplete/Autocomplete.c

clean:
	rm *.o a.out
