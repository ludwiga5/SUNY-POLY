/*

Written by Alex Ludwig
Language: C++ target g++

*/

#include <iostream>
using namespace std;

void doit (int);

int main (void){

    int x = 3;
    doit(x+3); //Note: Error

    return 0;

// Passing of &a must be addressible to pass as reference
// Must be an "L-value" / a variable
} void doit(int &a){
    cout<<"x is "<<a<<endl;
    return;
}