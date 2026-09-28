// Alex Ludwig
// CS330
// 10/2/2026
// HW4_Process_Affinity

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h> // timeval
#include <unistd.h>   // sleep()
#include <sched.h>    // affinity

// prototypes
void startTimer();
void endTimer();
void printTime();
void setCpuAffinity(int);

// global
struct timeval startTime;
struct timeval endTime;

int main(void){

	int PROCESS_COUNT = 4;
	
	pid_t cPID, wPID;
	
	printf("--- Test Case 1: Multi Thread Processing ---\n");
	startTimer();
	for (int j = 0; j < PROCESS_COUNT; ++j) {
		cPID = fork();
		if(cPID < 0) {
			perror("error");
			exit(1);
		}
		else if(cPID == 0) {
			volatile int cnt = 0;
			for (long i = 0; i < 1000000000L; i++) cnt++;
			exit(0);
		}
	}
	while ((wPID = wait(NULL)) > 0);
	endTimer();
	printTime();


	printf("--- Test Case 2: Single Thread Processing ---\n");
	setCpuAffinity(0);
	startTimer();
	for (int j = 0; j < PROCESS_COUNT; ++j) {
		cPID = fork();
		if(cPID < 0) {
			perror("error");
			exit(1);
		}
		else if(cPID == 0) {
			volatile int cnt = 0;
			for (long i = 0; i < 1000000000L; i++) cnt++;
			exit(0);
		}
	}
	while ((wPID = wait(NULL)) > 0);
	endTimer();
	printTime();
	return 0;
}

void setCpuAffinity(int thread) {
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(thread, &mask);
	sched_setaffinity(0, sizeof(mask), &mask);
}

void startTimer() {
	gettimeofday(&startTime, NULL);
}

void endTimer() {
	gettimeofday(&endTime, NULL);
}

void printTime() {
	long startTimeMicroseconds = (startTime.tv_sec*1000000 + startTime.tv_usec);
	long endTimeMicroseconds = (endTime.tv_sec*1000000 + endTime.tv_usec);
	long elapsedSeconds =  ((endTimeMicroseconds-startTimeMicroseconds) / 1000000);
	long elapsedMicroseconds = ((endTimeMicroseconds-startTimeMicroseconds) % 1000000);
	printf("Current elapsed time is %ld seconds, %ld microseconds\n", elapsedSeconds, elapsedMicroseconds);
}
