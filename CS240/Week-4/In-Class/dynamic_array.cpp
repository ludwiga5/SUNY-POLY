#include <iostream>
using namespace std;

int main(void){

    int a[15];
    int *b;
    b=a;

    cout<<"The value of a is "<<a<<endl;
    cout<<"The value of b is "<<a<<endl;

    //fill and print a
    for(int i=0; i<15; i++){

        a[i] = i*2;
        cout<<a[i]<<"   ";

    }
    cout<<endl;
    //Value of b
    for(int i=0; i<15; i++){

        cout<<b<<"   "<<*b<<endl;
        b++;

    }



    return 0;

}