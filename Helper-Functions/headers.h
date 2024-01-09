#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <ctype.h>

#include "prompt.h"
#include "tokenise.h"
#include "./../General/echo.h"
#include "./../General/Pwd.h"
#include "./../General/cd.h"
#include "./../General/ls.h"
#include "./../Fg-Bg/bg.h"
#include "./../Fg-Bg/fg.h"
#include "./../Linked-List/linkedList.h"
#include "./../History/history.h"
#include "./../User-Defined/discover.h"
#include "./../Pinfo/pinfo.h"
#include "./../Input-Output/redirect.h"
#include "./../Pipelining/pipeline.h"
#include "./../User-Defined/jobs.h"
#include "./../User-Defined/sig.h"
#include "./../User-Defined/Fg_usr.h"
#include "./../User-Defined/Bg_usr.h"
#include "./../Signal-Handling/signalHandlers.h"
#include "./../Rawmode/rawmode.h"
#include "./../Autocomplete/Autocomplete.h"

#define len 1001LL
typedef long long ll;