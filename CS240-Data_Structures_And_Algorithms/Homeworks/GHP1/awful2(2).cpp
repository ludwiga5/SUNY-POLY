/* Really dumb program to:
     1) fill a seven element static array of integers
     2) query the user for a target value
     3) call a function that searches the array for the target value
           calculates true if it is found, false otherwise
   Written by Ron
   Language: C++ 98 Cygwin 64-bit g++ compiler 
   August 2022
   Revised February 2025
*/

#include <iostream>

using namespace std;


void find_it(int array[], int & target, int  & size_of_array);

/*Global variables
  Declare 'em once, use 'em everywhere!
*/
bool found;
int size_of_thing=7;
int x, first, last, count;


int main(void)
{  int a[]={16, 9, 45, 23, 19, 43, 22};
   cout<<"Enter a value to search for in the array: ";
   cin>>x;  //x not declared here; it is global
   find_it(a,x,size_of_thing);
   if (found==true)
      cout<<x<<"  was found."<<endl;
   else
      cout<<x<<" was not found."<<endl;
   return 0;
}

/* Really great search function
   Searches array calculating true if target is found false otherwise
   array, target, size_of_array all global for consistency
     so I don't have to think about value parameters
   Written by Ron
   Language: C++ 98 Cygwin 64-bit g++ compiler
   August 2022
*/

void find_it (int array[], int & target, int & size_of_array)


{ //don't have to declare variables here since they are global
  found=false;
  first=0;
  last=size_of_array-1;
  count=1;
  while(count<=size_of_array)
   { if ((count%2)==0)  //count is even
        { if(array[first]==target)
             found=true;
         first++;
         count++;
        }
     else  //count is odd
        { if(array[last]==target)
            found=true;
         last--;
         count++;
        }
   }    
   return;
}


