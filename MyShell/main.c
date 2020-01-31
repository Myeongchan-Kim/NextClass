#include "main.h"

int main(){
	char userInput[MAX_LINE];	
	char* prompt = "MyShell>";

	while(1){
		printf("%s",prompt);
		if(!fgets(userInput,MAX_LINE, stdin))
			return 1;

		proc_cmd(userInput);
	}
	
	return 0;
}
