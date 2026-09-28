// Alex Ludwig
// CS330
// 9/19/2026
// HW3_Basic_Forking

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(void){

	int RUN_COUNT = 12;
	int PROCESS_COUNT = 26;
	
	pid_t cPID, wPID;

	for (int i = 0; i < RUN_COUNT; ++i) {
		for (int j = 0; j < PROCESS_COUNT; ++j) {
			if ((cPID = fork()) == 0) {
				srand(getpid() ^ time(NULL));  // unique random seed per child process
				usleep(rand() % 1000);         // 0-1ms delay between child executions
				printf("%c",(char)(j + 65));
				exit(0);
			}
		}
		while ((wPID = wait(NULL)) > 0);
		printf("\n");
	}

	return 0;
}
