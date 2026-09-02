/***********************************************************

Pythagorean Triples:

Inputs 2 ints m and n where m>n and computes
a pythagorean triple from the values

Written By: Alex Ludwig
CS108
9-26-2025

***********************************************************/

#include<stdio.h>

int main(void)
{

//Declares Integers for the lengths of the sides of the triangle
int side1, side2, hyp;

//Declares Integers for the user input
int m, n;


//Prompt Explaining User Input for m & n
printf("\nPlease Enter Two Integers\n");
printf("The First Interger MUST Be Larger Than the Second\n");

//Prompt and scan for input of m
printf("\nPlease enter the first integer\n");
scanf("%d", &m);

//Prompt and scan for input of n
printf("\nPlease enter the second integer\n");
scanf("%d", &n);


//Calculates the Values of the Sides
side1 = (m*m)-(n*n);
side2 = 2*m*n;
hyp   = (m*m)+(n*n);

//Output for the Pythagorean Triple
printf("\n\nThe Pythagorean Triple is %d, %d, %d\n", side1, side2, hyp);



return 0;
}
