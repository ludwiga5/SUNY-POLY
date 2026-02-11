/*
Purpose: 

Creates a magic square in a matrix of size 
{3x3, 5x5, 7x7} which is chosen from user input

Feb 2026
Written by Alex Ludwig
Language: C++
Compiler: g++ Apple clang version 17.0.0 (clang-1700.4.4.1)
*/

#include <iostream>
using namespace std;

//Prototypes
void magicSquare(int mat[7][7], int size);
void printIt(int mat[7][7], int size);
void fillZeroes(int mat[7][7], int size);


int main (void){

    int matrix[7][7];
    int size;

    cout<<"Input an length 3, 5, or 7 to create a magic square"<<endl;
    cin>>size;

    fillZeroes(matrix, size);
    magicSquare(matrix, size);
    printIt(matrix, size);

/*
Fills the matrix with n x n sized magic square 
Algorithm: Start at the top middle and move up-right 1 space and +1 to fill.

Written by Alex Ludwig
Language: C++
Compiler: g++ Apple clang version 17.0.0 (clang-1700.4.4.1)
*/
} void magicSquare(int mat[7][7], int size){

    //establishes starting indicies for algorithm
    int r = 0;
    int c = size/2;

    int next_r;
    int next_c;

    int value = 1;

    //used to prevent exceeding the edge of the square
    int max_run_amt = size*size;

    while(value<=max_run_amt)
    {

        mat[r][c] = value;

        //checks for bottom of square
        if((r-1) < 0)
            next_r = size-1;
        else    
            next_r = r-1;
        //checks for right of square
        if(c+1 == size)
            next_c = 0;
        else    
            next_c = c+1;

        //Checks for if the space is taken
        if(mat[next_r][next_c]!=0){

            r++;

        //After establishing correct next placement, set {r,c} = {next_r, next_c}
        } else{

            r = next_r;
            c = next_c;

        }            

        value++;
    }


/*
Prints the matrix

Written by Alex Ludwig
Language: C++
Compiler: g++ Apple clang version 17.0.0 (clang-1700.4.4.1)
*/
}  void printIt(int mat[7][7], int size){

    for(int r=0; r<size; r++){
        for(int c=0; c<size; c++){
            //Just a simple check to make the columns line up correctly between 1 & 2 digit nums
            if(mat[r][c]<10)
            cout<<mat[r][c]<<"   ";
            else
            cout<<mat[r][c]<<"  ";
        }
        cout<<endl;
    }


/*
Fills the array with 0s to avoid comparing 
garbage values from the compiler in magicSquare

Written by Alex Ludwig
Language: C++
Compiler: g++ Apple clang version 17.0.0 (clang-1700.4.4.1)
*/
}  void fillZeroes(int mat[7][7], int size){

    for(int r=0; r<size; r++)
        for(int c=0; c<size; c++)
            mat[r][c] = 0;
        
    
}

