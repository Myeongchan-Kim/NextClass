#ifndef TYPES
#define TYPES
	#include <sys/types.h>
#endif

#ifndef UNISTD
#define UNISTD
	#include <unistd.h>
#endif

#ifndef H_STDIO
#define H_STDIO
	#include <stdio.h>
#endif

#ifndef H_STDLIB
#define H_STDLIB
	#include <stdlib.h>
#endif

#ifndef WAIT
#define WAIT
	#include <sys/wait.h>
#endif

int external_cmd (int argc , char** argv);
int copyArrCharP(char **, char ** );
int isExcutableFile(char * fileName);
char* getOutputFileName(int*, char**);
int isValidFileName(char *);
int changeStdout(int * saveP, char * outFile);
int restoreStdout(int * saveP);
