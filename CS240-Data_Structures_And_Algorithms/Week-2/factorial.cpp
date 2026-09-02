/*
Used to Calculate the Factorial of an input value
Written by alex ludwig
Feb 2026
*/

#include <iostream>
#include <cassert>

using namespace std;

int factorial(int);

int main (void){

    int x;
    cout<<"Enter a non-negative integer <=12 to find the factorial of: "<<endl;
    cin>>x;

    int result = factorial(x);

    cout<<"The factorial of "<<x<<" is "<<result<<endl;;

    return 0;
}

//Function to calculate x factorial
int factorial(int x){

    int r1=1;
    int r2;

    for(int i=1; i<=x; i++){

        r2 = r1*i;
        cout<<i<<"  "<<r2<<endl;
        assert(r1==r2/i);
        r1=r2;
    }
    return r1;
}