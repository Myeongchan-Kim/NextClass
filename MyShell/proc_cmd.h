#ifndef H_STDIO
#define H_STDIO
	#include <stdio.h>
#endif

#ifndef H_STDLIB
#define H_STDLIB
	#include <stdlib.h>
#endif

#ifndef H_STRING
#define H_STRING
	#include <string.h>
#endif

#ifndef CONST
#define CONST
	#include "const.h"
#endif

#ifndef BUILTIN
#define BUILTIN
	#include "built_in.h"
#endif

#ifndef EXTERNAL
#define EXTERNAL
	#include "external_cmd.h"
#endif

int proc_cmd(char* str);
int redirection_cmd(int, char**);
int excution_cmd(int , char**);
int proc_amp_cmd(int, char**);
int copyArgv(int, char**, int, char**);
void delArgv(int, char**);

int trimAndLen(char* str);
int parse_line(char* str, char* argv[]);
void showArgv(int, char**);

