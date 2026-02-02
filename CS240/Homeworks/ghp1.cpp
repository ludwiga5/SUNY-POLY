/* Really smart program to:
     1) fill a seven element static array of integers
     2) query the user for a target value
     3) call a function that searches the array for the target value
           calculates true if it is found, false otherwise
    Written by Alex Ludwig
    Language: C++ Mac Terminal g++ compiler
    January 2026
*/

#include <iostream>
using namespace std;

//Prototype
bool find_it(int[], int);

int main(void){

    int a[]={16, 9, 45, 23, 19, 43, 22};
    int x;
    cout<<"Enter a value to search for in the array: ";
    cin>>x;  //X is the target value

    if (find_it(a, x))
        cout<<x<<" was found."<<endl;
    else
        cout<<x<<" was not found."<<endl;
    
    return 0;
}

bool find_it(int array[], int target){

    //Parses the array and checks each index for the target value
    for(int i=0; i<sizeof(array); i++){
        if (array[i]==target)
            return true;
    }
    return false;

}