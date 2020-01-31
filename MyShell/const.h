
/*상수 설정 */
#define MAX_LINE    	(1024)
#define MAX_ARGV    	(128)
#define MAX_ARG_LEN		(256)
#define MAX_DIRNAME		(128)
#define MAX_FILENAME	(128)
#define MAX_USRNAME		(128)
#define MAX_LS_ARG		(2)
#define MAX_LL_ARG		(2)
#define MAX_CAT_ARG		(2)
#define MAX_CP_ARG		(3)
#define MAX_RM_ARG		(2)
#define MAX_MV_ARG		(3)
#define MAX_PWD_ARG		(1)
#define MAX_CD_ARG		(2)
#define MAX_MKDIR_ARG	(2)
#define MAX_RMDIR_ARG	(2)
#define MAX_CPDIR_ARG	(3)
#define TIME_STR_LEN	(30)
#define COL_WIDTH		(2)
#define TAB_WIDTH		(8)
#define DEFAULT_DIR		("./")
#define BUFFER_SIZE		(4096)
#define MAX_THREAD		(5)

struct cp_t {
	int argc;
	char target[MAX_FILENAME];
	char source[MAX_FILENAME];
};
