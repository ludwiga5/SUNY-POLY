#include <stdio.h>

int main(void){

//Declare Variables

double num1, num2, num3;
double total, average;

//Intialized nums with user input

printf("\nPlease enter your first number\n");
scanf("%lf", &num1);

printf("\nPlease enter your second number\n");
scanf("%lf", &num2);

printf("\nPlease enter your third number\n");
scanf("%lf", &num3);

// Calculate & Print Total

total = num1+num2+num3;
printf("\n\nTotal = %7.3lf\n", total);

//Calculate & Print Average

average = total/3;
printf("\n\nAverage = %7.3lf\n", average);

return 0;

}
