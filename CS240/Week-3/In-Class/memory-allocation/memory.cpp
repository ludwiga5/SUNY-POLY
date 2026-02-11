/*

Used for testing of memory allocation
Written by Alex Ludwig
Feb 2026
Language: C++


int takes 32bits / 4 bytes
First allocation is given the higher 4 byte value
Second allocation is the next 4 bytes
Claimed from "the stack"

*ptr = new int
Dynamic allocation
Claimed from "the heap"
*/




#include <iostream>
using namespace std;

int main(void){

    //Allocates memory at compile time
    int x, y, z;
    int *I_ptr1, *I_ptr2, *I_ptr3, *I_ptr4;
    x = 3;
    y = 4;
    z = 5;

    cout<<"x = 3 is stored in "<<&x<<endl;
    //Ex.  x = 3 is stored in 0x16f70ace8

    cout<<"y = 4 is stored in "<<&y<<endl;
    //Ex.  y = 4 is stored in 0x16f70ace4

    cout<<"z = 5 is stored in "<<&z<<endl;
    //Ex.  z = 5 is stored in 0x16b07ace0


    I_ptr1 = &x;
    I_ptr2 = &y;
    I_ptr3 = &z;


    //The value is the address of x but it has its own location

    cout<<"I_ptr1 = "<<I_ptr1<<" is stored in"<<&I_ptr1<<endl;
    //Ex.  I_ptr1 = 0x16b07ace8 is stored in 0x16f70ace8

    cout<<"I_ptr2 = "<<I_ptr2<<" is stored in"<<&I_ptr2<<endl;
    //Ex.  I_ptr2 = 0x16b07ace4 is stored in 0x16f70ace4

    cout<<"I_ptr3 = "<<I_ptr3<<" is stored in"<<&I_ptr3<<endl;
    //Ex.  I_ptr3 = 0x16b07ace0 is stored in 0x16f70ace0

    //Incrementing pointer works and points to the next allocation upwards
    //Increments by 4 bytes -> I_ptr3 references y now

    I_ptr3++;
    cout<<"I_ptr3 after incrementing = "<<I_ptr3<<" and the value stored is "<<*I_ptr3<<endl;

    /*
    Allocates memory at runtime
    Grabs memory from "the heap"
    Only accesible through the pointer (Anonymous Variable)
    */
    I_ptr4 = new int;
    cout<<"I_ptr4 = "<<I_ptr4<<endl;
    *I_ptr4 = x+3; // (6)
    cout<<"The value stored is "<<*I_ptr4<<endl;



    return 0;
}