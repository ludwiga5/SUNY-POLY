#include <stdio.h>
#include <stdlib.h>

//Alex Ludwig
//CS108
/*********
Write a function that displays the
values on the diagonals of its 10x10
matrix parameter
*********/


int main(void){

//Prototype
void diagonals(int [][]);

//Creates a 3x3 table
int matrix[10][10];

//Fills the table with random 1-10 ints
for(int r=0; r<10; r++){

	for(int c=0; c<10; c++){
		matrix[r][c] = (rand() % 10)+1
		printf("%d	", matrix[r][c]);
		}
	printf("\n\n");
}
diagonals(matrix);

return 0;
}


//Finds and prints the values on the diagonals of a table
void diagonals (int table[][]){


