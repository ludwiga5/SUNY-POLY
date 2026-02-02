/*

GHP #5
Written by Alex Ludwig
12/5/25
CS108

*/
//Library Inclusion
#include <stdio.h>

//Prototype
int recfun(int);

//main
int main(){

int test_val;
printf("What test value would you like to use?\n");
scanf("%d", &test_val);

int solution = (recfun(test_val));
printf("The answer for the test value of %d is %d\n", test_val, solution);

return 0;
}

//Recursive Function
int recfun(int x){

if(x<=0)
	return 0;

else
	return (recfun(x-1)+4);

}
