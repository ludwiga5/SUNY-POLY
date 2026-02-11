#include <iostream>
using namespace std;

int main(void){

    int array_length, *arrayPtr1, *arrayPtr2;

    cout<<"How long should the array be?"<<endl;
    cin>>array_length;

    //nothrow prevents a crash if the memory allocation failed and gives arrayPtr1 a value of 0
    //Creates and stores with memory from the Heap
    arrayPtr1 = new (nothrow)int[array_length];

    if(arrayPtr1 == 0)
        cout<<"Cannot Create Array"<<endl;
    
    else{

        cout<<"Array successfully created"<<endl;
        cout<<"Array starts at address: "<<arrayPtr1<<endl;

        for (int i=0; i<array_length; i++){
            arrayPtr1[i] = i*2;
            cout<<arrayPtr1[i]<<endl;
        }

        cout<<"Deleting array"<<endl;

        //Returns memory space back to the heap
        delete [] arrayPtr1;

    }

}