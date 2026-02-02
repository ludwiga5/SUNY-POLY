#include <stdio.h>

/*
This program is meant to test out for & while loops in Standard C
Takes an imput and finds the factorial value of it

Alex Ludwig
CS108

10-2-2025
*/

//Global Variables
int fact;

//Prototypes
int factorials (int);

//Main
int main(void){

int usrinput;

printf("\n\n%s\n", "Please enter an integer");
scanf("%d", &usrinput);

fact=factorials(usrinput);
printf("Your factorial value is %d\n", fact);

return 0;

} int factorials (int x){

int f=1;
for(int i=1; i<=x; i++){
	f*=i;
	
}

return f;
}



