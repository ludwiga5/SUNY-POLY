#include <stdio.h>

/************************

User inputs two integers and
the program  prints the sum and average

Written by Alex Ludwig
9-26-2025
CS108

************************/

//Prototypes
double sum(int, int);
double avg(double);

//Global Definitions
double total;
double average;


int main(void){

int num1, num2;

//Prompt for Inputs
printf("Please input 2 integers\n");
scanf("%d%d", &num1, &num2);

total = sum(num1, num2);
average = avg(total);

//Output
printf("Your total is %5.2lf\nYour average is %5.2lf\n", total, average);

return(0);


} double sum (int n1, int n2){

return (n1+n2);

} double avg (double tot){

return (tot/2);

}






