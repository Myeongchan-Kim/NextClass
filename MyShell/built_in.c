#include "built_in.h"

int built_in_cmd(int argc, char **argv)
{
	// 내장 명령어 문자열과 argv[0]을 비교하여 각각의 처리 함수 호출
	if ((!strcmp(argv[0], "quit") || (!strcmp(argv[0], "exit")))) {
		exit(0); //프로그램 종료
	}

	if (!strcmp(argv[0], "ls")){
		list_file_ls(argc, argv);
	}else if (!strcmp(argv[0], "ll")){
		list_file_ll(argc, argv);
	}else if (!strcmp(argv[0], "cp")){
		copy_file(argc, argv);
	}else if (!strcmp(argv[0], "cat")){
		cat_file(argc, argv);
	}else if (!strcmp(argv[0], "rm")){
		remove_file(argc, argv);
	}else if (!strcmp(argv[0], "mv")){
		move_file(argc, argv);
	}else if (!strcmp(argv[0], "pwd")){
		print_current_dir(argc, argv);
	}else if (!strcmp(argv[0], "cd")){
		change_directory(argc, argv);
	}else if (!strcmp(argv[0], "mkdir")){
		make_directory(argc, argv);
	}else if (!strcmp(argv[0], "rmdir")){
		remove_directory(argc, argv);
	}else if (!strcmp(argv[0], "cpdir")){
		copy_directory(argc, argv);
	}else{
		// 내장 명령어가 아님.
		return 1;
	}

	//정상 종료. 
	return 0;
}

int list_file_ll(int argc, char** argv){
	DIR * dp;
	char pathname[MAX_DIRNAME+1];

	if(argc == 0 || !argv )	return 1;
	if(argc > MAX_LL_ARG){
		perror("명령어 인자 갯수가 맞지 않습니다.");
		//show_man('ls');
		return 0;
	}

	/*set target dir to print LIST*/
	if( !(dp = setPath(argc, argv, pathname)) ){
		show_man_ll();
		return 1;
	}

	/*print out*/
	if(print_LL(dp, pathname)) return 1;

	closedir(dp);

	return 0;
}

int print_LL(DIR * dp, char * pathname){
	struct dirent*	dir_entry_p;
	struct stat 	fstat;
	struct passwd*	pw;
	struct group*	gr;
	int chk = 0;
	char fileName[MAX_FILENAME+1] = "";
	char userName[MAX_USRNAME+1];
	char groupName[MAX_USRNAME+1];
	char fileType[MAX_LINE] = "";
	time_t fileSecond;
	char timeString[TIME_STR_LEN+1];
	int permission = 0;

	// file type, file permissiont, number of hardlink, owner, user group, file size, touch date, file name
	while( (dir_entry_p = readdir(dp)) != NULL  ){
		/*path + file*/
		if(pathname[strlen(pathname)-1] != '/')
			strcat(pathname, "/");
		strcpy(fileName, pathname);
		strcat(fileName, dir_entry_p->d_name);

		if( (chk = lstat( fileName, &fstat)) ){
			fprintf(stderr, "d_name : %s",dir_entry_p->d_name);
			perror("파일정보를 불러오는데실패하였습니다.\n");
			return 1;
		}

		/*file type*/
		if(S_ISDIR(fstat.st_mode))
			fileType[0]='d'; // directory
		else if(S_ISLNK(fstat.st_mode))
			fileType[0]='l'; // Symbolic link
		else if(S_ISCHR(fstat.st_mode))
			fileType[0]='c'; //Charater FIle
		else if(S_ISBLK(fstat.st_mode))
			fileType[0]='b'; //Block file
		else if(S_ISSOCK(fstat.st_mode))
			fileType[0]='s'; //Socket file
		else if(S_ISFIFO(fstat.st_mode))
			fileType[0]='p'; //pipe file
		else if(S_ISREG(fstat.st_mode))
			fileType[0]='-'; //regular file
		else 
			fileType[0]='?'; //none of above
		
		/*file permmision*/
		permission = fstat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
		
		/*author*/
		pw = getpwuid(fstat.st_uid);
		if(pw != NULL )
			strcpy(userName, pw->pw_name);
		
		/*user group*/
		gr = getgrgid(fstat.st_gid);
		if(gr != NULL)
			strcpy(groupName, gr->gr_name);
		
		/*last modification time*/
		fileSecond =  fstat.st_mtim.tv_sec;
		strftime(timeString, TIME_STR_LEN , "%Y-%m-%d %H:%M:%S", localtime(&fileSecond));	

		/*print result*/
		printf("%s%o %ld\t%s\t%s\t%ld\t%s %s\n",
				fileType, permission, (long)fstat.st_nlink, 
				userName, groupName, 
				fstat.st_size , timeString, 
				dir_entry_p->d_name);
	} //end while

	return 0;
}

void show_man_ll(){
	printf(" ll 사용법 : 디렉토리의 파일 목록과 파일의 속성들을 출력합니다. \n");
	printf(" ll [dirname] [ > filename : to redirect ]\n");
	printf(" example :\n");
	printf(" ll (현재 디렉토리 파일 목록 출력)\n");
	printf(" ll > result.txt (result.txt에 결과가 저장됨)\n");
}

int list_file_ls(int argc, char** argv){
	DIR * dp;
	struct dirent * dir_entry_p;
	char pathname[MAX_DIRNAME+1];
	int lenFileName;
	int tabNum;
	int count = 0;

	if(argc == 0 || !argv )
		return 1;
	if(argc > MAX_LS_ARG){
		perror("명령어 인자 갯수가 맞지 않습니다.");
		//show_man('ls');
		return 0;
	}

	/*set target dir to print LIST*/
	if( (dp = setPath(argc, argv, pathname)) == NULL){
		show_man_ls();
		return 1;
	}

	/* 파일 리스트 출력하는 부분 */
	while( (dir_entry_p = readdir(dp)) != NULL ){
		if(count && (count % 5 == 0) )
			printf("\n");
		lenFileName = strlen(dir_entry_p->d_name);
		printf("%s", dir_entry_p->d_name);

		//텍스트 정렬
		for (tabNum = COL_WIDTH; tabNum > (lenFileName / TAB_WIDTH); tabNum--)
			printf("\t");
		count++;
	}
	printf("\n");

	closedir(dp);

	return 0;
}

DIR * setPath(int argc, char ** argv, char * pathname){
	DIR * dp;

	argc = argc;
	//set target pathame for print
	if(argv[1] == NULL || (strlen(argv[1]) < 1)|| argc == 1 )
		strcpy(pathname, DEFAULT_DIR);
	else
		strcpy(pathname, argv[1]);
	//printf("path : %s\n", pathname);
	dp = opendir(pathname);
	if( !dp ){
		fprintf(stderr, "ERROR : pathanem : %s", pathname);
		perror("디렉토리가열리지 않습니다. .\n");
		return NULL;
	}
	return dp;	
}


void show_man_ls(){
	printf(" ls 사용법 : 디렉토리의 파일 리스트 출력 \n");
	printf(" ls [dirname] [ > filename : to redirect ]\n");
	printf(" example :\n");
	printf(" ls (현재 디렉토리 파일 목록 출력)\n");
	printf(" ls > result.txt (result.txt에 결과가 저장됨)\n");
	return ;
}

int cat_file(int argc, char** argv){
	int in_fd;
	int rd_count;
	char buffer[BUFFER_SIZE];
	
	if(argc == 0 || !argv )
		return 1;
	if(argc > MAX_CAT_ARG){
		perror("명령어 인자 갯수가 맞지 않습니다.");
		show_man_cat();
		return 0;
	}


	/*stdout으로 파일 복사*/
	if(( in_fd = open(argv[1], O_RDONLY)) < 0)
		return 1;

	while(1){
		if(( rd_count = read(in_fd, buffer, BUFFER_SIZE )) <= 0 )
			break;
		if( write(1 , buffer, rd_count) <= 0 )
			return 1;
	}
	if (rd_count < 0 ) return 1;
	close(in_fd);

	return 0;
}

void show_man_cat(){
	printf("cat : 파일 내용을 보여줍니다. \n");
	printf("cat filename \n");
	return;
}


int copy_file(int argc, char** argv){
	int in_fd, out_fd, rd_count;
	char buffer[BUFFER_SIZE];

	if(argc == 0 || !argv )
		return 1;
	if(argc > MAX_CP_ARG){
		perror("명령어 인자 갯수가 맞지 않습니다.");
		//show_man('cp');
		return 0;
	}

	printf("copy start. source=%s , dest=%s \n", argv[1], argv[2]);

	/*파일 복사*/
	if(( in_fd = open(argv[1], O_RDONLY)) < 0)
		return 1;
	if(( out_fd = creat(argv[2], 0644)) < 0)
		return 1;

	while(1){
		if(( rd_count = read(in_fd, buffer, BUFFER_SIZE )) <= 0 )
			break;
		if( write(out_fd, buffer, rd_count) <= 0 )
			return 1;
	}
	if (rd_count < 0 ) return 1;
	close(in_fd);
	close(out_fd);


	return 0;
}

void show_man_cp(){
	printf("man_cp\n");
	return;
}

int remove_file(int argc, char** argv){
	if(argc == 0 || !argv )
		return 1;
	if(argc > MAX_RM_ARG){
		perror("명령어 인자 갯수가 맞지 않습니다.");
		//show_man('rm');
		return 0;
	}

	/*remove file */
	if(!isValidFileName( argv[1] )){
		perror("파일 이름이 올바르지 않습니다. ");
		return 1;
	}	
	if(remove( argv[1] ) == -1)
		perror("파일 삭제 실패\n");

	return 0;
}


int move_file(int argc, char** argv){
	char fileDest[MAX_FILENAME+1];
	int index;

	if(argc == 0 || !argv )
		return 1;
	if(argc > MAX_MV_ARG){
		perror("명령어 인자 갯수가 맞지 않습니다.");
		//show_man('rm');
		return 0;
	}

	/*move file */
	if(!isValidFileName( argv[1] )){
		perror("파일 이름이 올바르지 않습니다. ");
		return 1;
	}	
	strcpy(fileDest, argv[2]);
	index = strlen(argv[2]) - 1 ; 
	if( argv[2][index]  != '/' )
		strcat(fileDest, "/");
	strcat(fileDest, argv[1]);
	if( rename( argv[1] , fileDest) )
		perror("파일이동  실패\n");


	return 0;
}

int change_directory(int argc, char** argv){

	if(argc == 0 || !argv )
		return 1;
	if(argc > MAX_CD_ARG){
		perror("명령어 인자 갯수가 맞지 않습니다.");
		//show_man('rm');
		return 0;
	}


	if( chdir( argv[1] ) < 0){
		perror(" fail to change directory" );
		return 1;
	}


	return 0;
}

int print_current_dir(int argc, char** argv){
	char * dirname;
	char buffer[BUFFER_SIZE];

	if(argc == 0 || !argv )
		return 1;
	if(argc > MAX_PWD_ARG){
		perror("명령어 인자 갯수가 맞지 않습니다.");
		//show_man('rm');
		return 0;
	}


	/*print current dir*/
	dirname = getcwd(buffer , MAX_DIRNAME);
	printf("%s\n", dirname);


	return 0;
}

int make_directory ( int argc, char** argv){

	if(argc == 0 || !argv )
		return 1;
	if(argc > MAX_MKDIR_ARG){
		perror("명령어 인자 갯수가 맞지 않습니다.");
		//show_man('rm');
		return 0;
	}

	
	if( mkdir(argv[1], 0775 ) < 0 ){
		perror("fail to make directory");
		return 1;
	}


	return 0;
}

int remove_directory(int argc, char** argv){
	char dirName[MAX_DIRNAME];

	if(argc == 0 || !argv )
		return 1;
	if(argc > MAX_MKDIR_ARG){
		perror("명령어 인자 갯수가 맞지 않습니다.");
		//show_man('rm');
		return 0;
	}

	/*delete dir */
	strcpy( dirName , argv[1] );	
	if(dirName[strlen(dirName)-1] == '/')
		dirName[strlen(dirName)-1] = '\0';
	
	printf("dirName : %s\n", dirName);
 	if(rmDirByRecur( dirName) ){
		perror("err ");
		return 1;
	}

	return 0;
}

int rmDirByRecur( char * targetDir){	
	DIR * dp;
	char fileName[MAX_FILENAME];
	struct dirent * dir_entry_p;
	struct stat fstat;

	//열리는지 확인
	if(( dp = opendir( targetDir)) == NULL ){
		fprintf(stderr, "%s ",targetDir);
		perror("open err");
		return 1;
	}

	while( (dir_entry_p = readdir(dp)) != NULL  ){

		if( strcmp( dir_entry_p->d_name , "." ) && strcmp( dir_entry_p->d_name , "..") ){
			//pathname + filename
			strcpy(fileName, "");
			strcpy(fileName, targetDir);
			strcat(fileName, "/");
			strcat(fileName, dir_entry_p->d_name);

			if( (lstat( fileName, &fstat )) != 0 ){ 
				fprintf(stderr, "d_name : %s",dir_entry_p->d_name);
				perror("파일정보를 불러오는데실패하였습니다.\n");
			}

			printf("%s 를 삭제합니다...", fileName);
			if(S_ISDIR(fstat.st_mode)){
				//각 파일의정보를 불러와서 파일이면 삭제. 디렉토리면 재귀적 실행.
				if( rmDirByRecur( fileName ) )
					printf( "fail" );
				else
					printf( "deleted");
			}else{
				if( remove( fileName ) )
					perror( "fail" );
				else 
					printf( "deleted");
			}
			printf("\n");
		}
	}
	
	closedir(dp);

	//모든 파일이 삭제된 이후에 디렉토리 작제
	if( rmdir(targetDir) < 0 ){
		perror("fail to remove directory");
		return 1;
	}
	return 0;
}

int copy_directory(int argc, char **argv){
	// cpdir (source directory} (target directory)
	// argv[1] : source directory
	// argv[2] : target directory
	DIR * srcDp;
	DIR * tgtDp;
	char tgtName[MAX_FILENAME];
	char srcName[MAX_FILENAME];
	struct cp_t arg[MAX_THREAD];
	struct dirent * dir_entry_p;
	struct stat fstat;
	pthread_t tid[MAX_THREAD];
	int count = 0;
	int i;

	if( argc > MAX_CPDIR_ARG )
		return 1;

	//열리는지 확인
	if(( srcDp = opendir( argv[1])) == NULL ){
		fprintf(stderr, "%s ",argv[1]);
		perror("open err");
		return 1;
	}
	//열리는지 확인
	if(( tgtDp = opendir( argv[2])) == NULL ){
		if( mkdir(argv[2], 0775 ) < 0 ){
			perror("fail to make directory");
			return 1;
		}
	}

	//dirname뒤의 '/'제거
	if( argv[1][strlen(argv[1])-1] == '/' )
		argv[1][strlen(argv[1])-1] = '\0';
	if( argv[2][strlen(argv[2])-1] == '/' )
		argv[2][strlen(argv[2])-1] = '\0';

	while( (dir_entry_p = readdir(srcDp)) != NULL  ){
		//file name + path name
		strcpy(srcName, "");
		strcat(srcName, "./");
		strcat(srcName, argv[1]);
		strcat(srcName, "/");
		strcat(srcName, dir_entry_p->d_name);

		strcpy(tgtName, "");
		strcat(tgtName, "./");
		strcat(tgtName, argv[2]);
		strcat(tgtName, "/");
		strcat(tgtName, dir_entry_p->d_name);

		//read file
		if( lstat( srcName, &fstat) ) {
			fprintf(stderr, "d_name : %s",dir_entry_p->d_name);
			perror("파일정보를 불러오는데실패하였습니다.\n");
			return 1;
		}

		//디렉토리는 무시함
		if(S_ISDIR(fstat.st_mode))
			continue;
		

		if(count >=  MAX_THREAD){
			for( i=0 ; i < MAX_THREAD ; i++){
				pthread_join(tid[i], NULL);
				tid[i] = 0;
			}
			count = 0;
		}
		//스레드에 넘겨줄 arg생성
		strcpy( arg[count].source , srcName);
		strcpy( arg[count].target , tgtName);
		printf("[%d] src : %s, target : %s\n",count , arg[count].source, arg[count].target);
		pthread_create( &tid[count], NULL, copy_file_thread , (void*)&arg[count] );
		count++;
	}

	for( i=0 ; i<MAX_THREAD ; i++ ){
		if( tid[i] > 0 )
			pthread_join(tid[i], NULL);
	}
	
	closedir(srcDp);
	closedir(tgtDp);

	printf("Copy complete.\n");
	return 0;
}

void * copy_file_thread( void * arg){
	int argc = 3;
	char* argv[3];
	struct cp_t * cp = (struct cp_t *)arg;

	argv[0] = (char*)malloc(sizeof(char)* 3);
	argv[1] = (char*)malloc(sizeof(char)* (strlen(cp->source)+1));
	argv[2] = (char*)malloc(sizeof(char)* (strlen(cp->target)+1));

	strcpy( argv[0] , "cp");
	strcpy( argv[1] , cp->source);
	strcpy( argv[2] , cp->target);
	
	//printf("Copy confim src: %s, tgr %s\n", argv[1], argv[2]);
	if( copy_file(argc, (char**)argv) ){
		delete(argc, argv);
		perror("copy fail");
		return (void*)1;
	}
	delete(argc, argv);

	return (void*)0;
}

void delete(int argc, char ** argv){
	int i;
	if( argv == NULL)
		return;

	for( i=0 ; i<argc ; i++){
		free(argv[i]);
	}
	return;
}
