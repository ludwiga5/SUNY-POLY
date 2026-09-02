/*Program to illustrate function template
  Written by Ron
  March 2010
  Language: C++ (g++ target)
*/

#include <iostream>

using namespace std;


template <typename DataType>

/* Function template for addemup
    Adds two values of any two variables of the same
    type DataType where the addition operator (+) is defined

    Written by Ron
    March 2010
    Language: C++ (g++ target)

    Preconditon: none
    Postcondition:  the two values (one and two) have been added
                    with the result of the addition returned on
                    the stack.
*/



DataType addemup (DataType & one, DataType & two)
{
   return (one+two);
}
/*====end of template addemup==================================*/

int main(void)
{ int a,b;
  double c,d;
  char e,f;
  a=3;
  b=4;
  c=6.3;
  d=4.72;
  e='a';
  f='b';
/*  adding two integers */
  cout<<"integer addition 3+4 "<< addemup(a,b)<<endl;
/*  adding two doubles   */
  cout<<"double addition 6.3+4.72 "<< addemup(c,d)<<endl;
/*  adding two characters */
  cout<<"character addition a+b "<< addemup(e,f)<<endl;
  return 0;
}
