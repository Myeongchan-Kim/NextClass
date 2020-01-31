#include "external_cmd.h"

int external_cmd(int argc, char** argv){
	pid_t pid ;
	char ** newArgv; 
	int newArgc;
	//int i=0;
	
	//make new argv for external excution.
	newArgv = (char**)malloc(sizeof(char*) * (argc+1));
	//printf("size of newArgv : %d \n", (int)sizeof(newArgv));
	newArgc = copyArrCharP(newArgv, argv);
	newArgv[newArgc] = NULL;
	
	pid = fork();
	if(pid < 0){
		perror("fork fail.");
		return 1;
	}else if(pid == 0){ //child process
		if( execvp(argv[0], newArgv) < 0 )
			perror("excution fail");
			exit(0); //실행 실패시 종료
	}else{
		//shell
		pid = waitpid(pid, NULL, 0);
		printf("PID: %d is terminated.\n",(int)pid);
		free(newArgv);
	}

	return 0;
}


int copyArrCharP(char ** targetArr, char ** srcArr){
	int i = 0;

	if(targetArr == NULL)
		return -1;

	while(srcArr[i]){
		targetArr[i] = srcArr[i];
		i++;
	}
	return i;
}
