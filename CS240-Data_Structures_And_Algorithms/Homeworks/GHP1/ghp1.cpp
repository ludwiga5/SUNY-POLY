/* Really smart program to:
     1) fill a seven element static array of integers
     2) query the user for a target value
     3) call a function that searches the array for the target value
           calculates true if it is found, false otherwise
    Written by Alex Ludwig
    Language: C++, g++ compiler
    January 2026
*/

#include <iostream>
using namespace std;

//Definitions
#define size_of_array 7

//Prototypes
bool find_it(int[], int);

/*
Gathers user input and calls find_it
Prints whether or not the target value was found
*/
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

/*
Parses the array and checks each index for the target value
*/
bool find_it(int array[], int target){

    for(int i=0; i<size_of_array; i++){
        if (array[i]==target)
            return true;
    }
    return false;

}