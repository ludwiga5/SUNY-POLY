/********************
*
Written by Alex Ludwig
12/12/25
CS108
Extra Credit Assignment
*
********************/
#include <stdio.h>
#include <math.h>

//Prototypes
void fillarr(int[]);
void product(int[], int[], int[]);
void sum(int[]);
void printit(int[], int[], int[]);

//Global Var
int n=20;

//Main
int main(void){

//Array Declarations
int x[20];
int y[20];
int z[20];

fillarr(x);
fillarr(y);
product(x, y, z);
sum(z);
printit(x, y, z);

return 0;
}//End Main


//Used to fill the array with user input data
void fillarr(int arr[]){

int input=0;//User Input Var
int i=0;    //Index Var for loop
int size=n;

printf("Please enter your values - to a maximum of 20 values\n");
printf("Enter -999 to quit\n");
//Gather user data
while((input!=-999) && (i<size)){

scanf("%d", &input);
if(input!=-999){
arr[i] = input;
i++;
}
}
n=i;
}//End fillarr



//Used to fill the third array with the product of arr1 and arr2
void product(int arr1[], int arr2[], int arr3[]){

int size = n;
for(int i=0; i<size; i++)
	arr3[i] = arr1[i]*arr2[i];

}//End product



//Finds & prints the sum of an array 
//Finds & prints the square root of the sum
void sum(int arr[]){

int size = n;
int sum=0;
double sqrt_sum;

for(int i=0; i<size; i++)
	sum+=arr[i];

printf("The sum of items in z is %d\n", sum);
sqrt_sum = sqrt(sum);
printf("The square root of sum is %f\n", sqrt_sum);
}//End sum




//Used to print three arrays in columns
void printit(int arr1[], int arr2[], int arr3[]){

int size = n;
for (int i=0; i<size; i++)
printf("%d	%d	%d\n", arr1[i], arr2[i], arr3[i]);
}//End printit
