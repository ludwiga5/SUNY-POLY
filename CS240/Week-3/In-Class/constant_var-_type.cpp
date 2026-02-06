/*

Written by Alex Ludwig
Language: C++ target g++

*/

#include <iostream>
using namespace std;

// Prototype
void printit(const int[]);

// Main
int main (void){

int a[5], i;
for(i=0; i<5; i++)
    a[i] = i*3;
printit(a);
//cout<<"\n"<<a[0]<<endl;
return 0;


// Funtion to illustrate the use of read-only reference parameter
} void printit(const int x[]){

    int j;
//    x[0] = 256;   Note: Causes an error due to use of "const int" (read-only reference)
    for (j=0; j<5; j++)
        cout<<x[j]<<"   ";
    
    return;

}