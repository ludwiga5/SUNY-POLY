// Alex Ludwig
// CS330
// 9/12/2026
// HW2_Code_Timer

#include <stdio.h>
#include <sys/time.h> // timeval
#include <unistd.h>   // sleep()

// prototypes
void startTimer();
void endTimer();
void printTime();

// global
struct timeval startTime;
struct timeval endTime;

int main(void) {
   
	printf("--- Real Time Use: 5sec sleep ---\n");
	startTimer();
    
	for(int i = 0; i<5; i++) {
        	sleep(1);
    	}
    
	endTimer();
	printTime();

	// expected result = 3 seconds, 800 microseconds elapsed
	printf("--- Test Case 1: end usec > start usec ---\n");
	startTime.tv_sec = 2; 
	startTime.tv_usec = 100;
	endTime.tv_sec = 5;   
	endTime.tv_usec = 900;
	printTime();

	// expected result = 0 seconds, 2 microseconds elapsed
	printf("--- Test Case 2: end usec < start usec ---\n");
	startTime.tv_sec = 3;
	startTime.tv_usec = 999999;
	endTime.tv_sec = 4;
	endTime.tv_usec = 1;
	printTime();

	return 0;
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
