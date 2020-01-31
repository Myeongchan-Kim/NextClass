#include "proc_cmd.h"

int proc_cmd(char* str){ //return 0 : err , return 1 : noraml return
	int argc;
	char* argv[MAX_ARGV];

	if ( !str ) //treat null pointer
		return 1;

	argc = parse_line(str, argv); //prase str by words	
	if (!argc || argc < 1)
		return 1;

	/*백 그라운드 처리하는 부분 */
	if( proc_amp_cmd(argc, argv) ){
		//amp 단위로 명령줄을 끊어서 각각 다른 쓰레드로 백 그라운드  실행.	
	}
	
	return 0;
}

int proc_amp_cmd(int argc, char ** argv){
	int i;
	int newArgc;
	char *newArgv[MAX_ARGV];
	int chk = 0; //새로운 쓰레드가 생성되면 1로 변함. 
	int chkMalloc = 0;
	pid_t pid;


	/*새로운 명령어 생성하는 부분 */
	for( i=0; i< argc ; i++){
		if(strcmp(argv[i], "&") == 0 ){
			// & 가 있으면 그 앞까지의 명령어를 복사해서 새로운 명령어 생성. 
			newArgc = i;
			if( (chkMalloc = copyArgv(newArgc, newArgv, argc, argv)) ){ //mallco and copy new argv
				perror("새 명령어라인 생성 실패:");
			}

			// & 앞쪽을 재외한 나머지 부분으로 수정된 argc, argv로 만듬.  
			argc = argc - newArgc - 1;
			if(argc > 0){
				argv = &argv[newArgc+1]; //앞쪽에 새로 만들어진 명령어랑 & 를 버리고 그 다음 명령어로 위치를 바꿈. 
			}
			chk = 1;
			break;
		}
	}
	
	/*새로 생성된 명령어 실행하는 부분*/
	if(chk == 1){ //새로 생성된 명령어로 쓰레드 생성후 실행함. 
		pid = fork();
		if( pid == 0 ){
			excution_cmd(newArgc, (char**)newArgv);
			exit(0); //자식은 해당 작업 완료하면 종료. 
		}else{
			if(chkMalloc == 0)
				delArgv(newArgc, newArgv); //free new argv
			if(argc > 0) //만약에 남은 명령어가 있으면
				proc_amp_cmd(argc, (char**)argv); //부모는 자식을 기다리지 않고, 본인명령어를 재귀 실행함. 
		}
	}else{
		// & 가 없으면 그냥 실행. 
		if(excution_cmd(argc, argv))
			return 1;
	}

	
	return 0;
}

int copyArgv(int targetArgc, char ** targetArgv, int srcArgc, char ** srcArgv){
	int i;
	int len;

	if(targetArgc == 0 || targetArgv == NULL || srcArgv == 0 || srcArgv == NULL)
		return 1;

	for(i=0; i< targetArgc && i< srcArgc; i++){
		len = strlen(srcArgv[i]);
		targetArgv[i] = (char*)malloc(sizeof(char)*(len+1));
		strcpy(targetArgv[i], srcArgv[i]);
	}

	return 0;
}

void delArgv(int argc, char **argv){
	int i;
	
	for(i=0; i< argc; i++)
		free(argv[i]);

	return;
}

int excution_cmd(int argc, char ** argv){
	int i;
	int chk = 0;
	int chkMalloc = 0;
	int newArgc;
	char *newArgv[MAX_ARGV];
	int pipefd[2]; //file discripter for pipe . 0=in , 1=out
	pid_t pid1;
	pid_t pid2;

	//showArgv(argc, argv);// print all arguments.

	if(argc < 0)	return 1;

	/*새로운 명령어 생성하는 부분 */
	for( i=0; i< argc ; i++){
		if(strcmp(argv[i], "|") == 0 ){
			// '|'가 있으면 그 앞까지의 명령어를 복사해서 새로운 명령어 생성. 
			newArgc = i;
			if( (chkMalloc = copyArgv(newArgc, newArgv, argc, argv)) ) //mallco and copy new argv
				perror("새 명령어라인 생성 실패:");

			// | 앞쪽을 재외한 나머지 부분으로 수정된 argc, argv로 만듬.  
			argc = argc - newArgc - 1;
			if(argc > 0){
				argv = &argv[newArgc+1]; //앞쪽에 새로 만들어진 명령어랑 & 를 버리고 뒤로 미룸
			}
			chk = 1;
			break;
		}
	}


	if(chk == 1){
		if( pipe(pipefd) == -1 ) //파이프  생성
		{
			perror("pipe creation err");
			return 1;
		}		

		pid1 = fork();
		if( pid1 < 0 ){
			perror("fork err");
			return 1;
		}else if( pid1 == 0 ){ //자식 프로세스 1. 앞쪽 명령어를 실행함. 
			close(pipefd[0]) ; // read는 닫아놈. 
			dup2(pipefd[1], STDOUT_FILENO);
			redirection_cmd(newArgc, newArgv);
			exit(0); //실행하고 종료.
		}

		pid2 = fork();
		if( pid2 < 0){
			perror("fork err");
			return 1;
		}else if( pid2 == 0){ //자식 프로세스 2. 뒷쪽 명령어를 실행함. 
			close(pipefd[1]); // write는 닫아놈.
			dup2(pipefd[0], STDIN_FILENO);
			excution_cmd(argc , argv); // 나머지를명령어를  재귀적으로 실행함. 
			exit(0);
		}
		
		if(pid1 >0 && pid2 >0 ){
			close(pipefd[0]);
			close(pipefd[1]); // 부모는 파이프를 둘다닫고 응답을 기다림. 

			while( wait(NULL) >= 0 ); //자식이 모두 종료될 때까지 기다림. 
		}

	} else {
		//pipe가 없을경우 곧장 실행
		/*redirection을 포함한 실행 부분*/
		if(redirection_cmd(argc, argv)){
			return 1;
		}
	}
	return 0;

}

int redirection_cmd(int argc, char** argv){
	char * outFile;
	int saved_stdout;

	//redirection
	outFile = getOutputFileName(&argc, argv);
	printf("outfile: %s\n",outFile);
	if( outFile ){ //if redirection exist 
		printf("Print out in file(%s)\n", outFile);
		if(changeStdout(&saved_stdout, outFile)){
			perror("fail to change stdout");
			printf("화면에 출력합니다.");
		}
	}

		/* 내장 명령 처리 함수를 수행한다.내장 명령어가 아니면 1 리턴 */
	if ( built_in_cmd( argc, argv ) ) {
		/* 외부 명령어 실행하는 부분 */
		printf("외부 실행:%s \n",argv[0]);
		if(external_cmd( argc, argv)){
			perror("외부 실행에 실패하였습니다. \n");
		}
	}

	//출력을 원래 stdout으로 복구
	if(outFile){
		restoreStdout(&saved_stdout);
		free(outFile);
	}

	return 0;
}

int changeStdout(int * saveP, char * outFile){
	int fd ;
	
	if( !saveP || !outFile )
		return 1;
	fd = creat(outFile, 0644);
	if( fd < 1)
		return 1;
	*saveP = dup(1); // 1 means stdout' file discript No.
	dup2( fd, 1); //change to fd from stdout
	close(fd);

	return 0;
}

int restoreStdout(int * saveP){
	if( dup2( *saveP ,1 ) == -1 ){
		perror("fail to restore");
		return 1;
	}
	return 0;
}

char* getOutputFileName(int *argcP, char** argv){
	int i;
	char * outputFileName = NULL;
	for(i=0; i<*argcP; i++){
		if( !strcmp(argv[i] , ">") ){
			if (i == *argcP-1){
				perror("리다이렉션 파일을 지정하지 않았습니다.");
				strcpy(argv[i], "");
				return NULL;
			}else{
				if(!isValidFileName(argv[i+1])){
					perror("파일 이름이 올바르지 않습니다. \n");
					return NULL;
				}
				outputFileName = (char*)malloc(sizeof(char)*MAX_FILENAME);
				strncpy(outputFileName ,  argv[i+1], MAX_FILENAME);
				argv[i+1] = NULL;//처리한 아규먼트는 삭제
				argv[i] = NULL; // 처리한 아규먼트는 삭제
				*argcP -=2; //아규먼트 개수도 줄임. 
				//strcpy(argv[i+1], ""); //처리한 아규먼트는 삭제
				//strcpy(argv[i], ""); //처리한 아규먼트는 삭제:
			}
			return outputFileName;
		}
	}
	return NULL;
}

int isValidFileName(char * FileName){
	int i;
	char c;
	for(i=0; i<(int)strlen(FileName); i++){
		c = FileName[i];
		if( c==':' || c=='*' || c=='?' || c=='"' || c=='<' || c=='>' || c=='|')
			return 0; //is not valid
	}
	
	return 1; //is valid
}

int parse_line(char * str, char * argv[]){
	int argc = 0;
	int len = 0;
	
	len = trimAndLen(str); //remove newline
	if ( *str == '\0' || len == 0)
		return 0;

	if( ( argv[argc] =(char *)strtok(str, " \n")) != NULL)
		argc++;

	while( ( argv[argc] = strtok(NULL, " \n")) != NULL )
		argc++;
	
	return argc;
}

int trimAndLen( char* str){ //remove newline
	int len=strlen(str); 
	
	if( !str || len == 0 )
		return 0;
	
	len = strlen(str); //return length after trim
	return len;
}
