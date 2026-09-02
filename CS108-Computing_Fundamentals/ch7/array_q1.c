#include <stdio.h>

/*************
Written by Alex Ludwig
CS108
11-7-2025
Takes 10 int inputs and are each a value in an array
Then prints a table of values of input values and percent of total value
*************/

//Prototypes
int fillit(int array[]);


//Main
int main(void){


int arr[10];
double total = fillit(arr);


//prints header
printf("n	percent\n	of total\n");
printf("-------------------\n");

//prints table
for(int i=0; i<10; i++)
	printf("%d	%3.2lf\n", arr[i], (arr[i]/total*100));

return 0;
}

//Fills array with scanf and returns the total value
int fillit(int empty[]){
int temp_total=0;
for(int i=0; i<10; i++){

	printf("\nplease enter an integer\n");
	scanf("%d", &empty[i]);
	temp_total+=empty[i];
}
return temp_total;
}
