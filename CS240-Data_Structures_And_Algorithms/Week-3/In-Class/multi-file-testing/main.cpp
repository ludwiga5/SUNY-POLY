#include <iostream>
using namespace std;

//Use of Header file containing prototype for factorial
#include "factorial.h"

int main(void){
    int n, result;
    cout<<"Enter an int 0-12"<<endl;
    cin>>n;
    result = fact(n);
    cout<<"Result is "<<result<<endl;
}