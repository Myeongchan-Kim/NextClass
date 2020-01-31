#ifndef TYPES
#define TYPES
	#include <sys/types.h>
#endif

#ifndef STAT
#define STAT
	#include <sys/stat.h>
#endif

#ifndef UNISTD
#define UNISTD
	#include <unistd.h>
#endif

#ifndef DIRENT
#define DIRENT
	#include <dirent.h>
#endif

#ifndef FCNTL
#define FCNTL
	#include <fcntl.h>
#endif

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

#ifndef PWD
#define PWD
	#include <pwd.h>
#endif

#ifndef GRP
#define GRP
	#include <grp.h>
#endif

#ifndef TIME
#define TIME
	#include <time.h>
#endif

#ifndef PTHREAD
#define PTHREAD
	#include <pthread.h>
#endif

#ifndef CONST
#define CONST
	#include "const.h"
#endif

#ifndef EXTERNAL
#define EXTERNAL
	#include "external_cmd.h"
#endif


int built_in_cmd(int , char**);
DIR * setPath( int , char **, char* );

int list_file_ll(int, char**);
int print_LL(DIR * dp, char * pathname);
void show_man_ll();

int list_file_ls(int, char**);
void show_man_ls();

int cat_file(int, char**);
void show_man_cat();

int copy_file(int, char**);
void show_man_cp();

int remove_file(int, char**);
void show_man_rm();

int move_file(int, char**);
void show_man_mv();

int change_directory(int, char**);
void show_man_cd();

int print_current_dir(int, char**);
void show_man_pwd();

int make_directory(int, char**);
void show_man_mkdir();

int remove_directory(int, char**);
int rmDirByRecur(char *);
void show_man_rmdir();

int copy_directory(int, char**);
void* copy_file_thread(void*);
void delete(int , char **);
