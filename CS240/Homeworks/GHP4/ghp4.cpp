/*

Purpose: 

1. Queries the user for 12 letters; place the first 6 on Stack 1 and the second 6 on Stack 2.
2. Write a function that returns a bool comparing the two stacks, returning true if the
contents of both stacks are identical – that is the same values in the same order, false
otherwise.
3. Pass Stack 1 and Stack 2 to this function and display whether or not the stacks are
identical.
4. After displaying the result, display the contents of the two stacks, each in their original
order

Written by Alex Ludwig

March 2026
Language: C++
Compiler: g++ Apple clang version 17.0.0 (clang-1700.4.4.1)

*/

#include <iostream>

using namespace std;

#include "stack.h"

//used throughout the program as the size of eack stack
#define LENGTH 6

//prototypes
bool compareStacks(Stack, Stack);
void originalPrint(Stack);

//main Function
int main(void){

    Stack stack1;
    Stack stack2;
    char input;
    bool stackEqual;

    cout<<"Please input 12 letters.\nThe first six will be in a stack, and the second six will be in another stack"<<endl;
    
    //fill $stack1
    for(int i=0; i<LENGTH; i++){
        cin>>input;
        stack1.push(input);
    }
    //fill $stack2
    for(int i=0; i<LENGTH; i++){
        cin>>input;
        stack2.push(input);
    }

    stackEqual = compareStacks(stack1, stack2);

    if(stackEqual)
        cout<<"The stacks are exactly the same"<<endl;
    else
        cout<<"The stacks are not the same"<<endl;

    cout<<"Stack 1:"<<endl;
    originalPrint(stack1);
    cout<<"Stack 2:"<<endl;
    originalPrint(stack2);
    return 0;

}

/*
Purpose:
Function used to compare the values within two stacks,
returning true if the stacks are the same, and false otherwise

Written by Alex Ludwig
March 2026
Language: C++
Compiler: g++ Apple clang version 17.0.0 (clang-1700.4.4.1)
*/
bool compareStacks(Stack s1, Stack s2){

    bool stackEqual = true;
    while(!s1.empty() && stackEqual){

        if(s1.top() != s2.top())
            stackEqual = false;

        s1.pop();
        s2.pop();
    }

    return stackEqual;
}


/*
Purpose:
Function used to print a stack bottom to top

Written by Alex Ludwig
March 2026
Language: C++
Compiler: g++ Apple clang version 17.0.0 (clang-1700.4.4.1)
*/
void originalPrint(Stack s1){

    char arr[LENGTH];

    for(int i=LENGTH-1; i>=0; i--){
        arr[i] = s1.top();
        s1.pop();
    }
    for(int i=0; i<LENGTH; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

