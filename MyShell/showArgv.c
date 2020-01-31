#include "showArgv.h"

void showArgv(int argc, char* argv[]){
	int i;
	if(!argv || !argv[0])
		return;

	for (i=0; i<argc ; i++){
		printf("%d:\"%s\" ", i, argv[i]);
	}
	printf("\n");
	printf("Total argument : %d\n", i);

	return;
}
