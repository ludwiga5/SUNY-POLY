//Program to illustrate use of
//reference parameters
//through multiple function calls
//Written by Ron
//January 2010
//Language: C++ (g++ target)
//
// Requires: snidley, green_acres

#include <iostream>

using namespace std;

void snidley (int &dudley, int &nell);  
void green_acres (int &fred, int &arnold);

int main(void)
{int rocky, bw, boris;
 rocky=3;
 bw=4;
 boris=rocky+bw;
 snidley(rocky, boris);           //syntax gives no clue whether
                                  //passed by value or by reference
 cout<<"after snidley rocky = "<<
   rocky<<" bw = "<<bw<<
   "boris = "<<boris<<endl;
 return 0;
}


void snidley (int &dudley, int &nell)     //dudley and nell passed by ref
{/*Function to illustrate reference
   parameters; doesn't do anything
   useful but calls green_acres
  
   Written by Ron
   January 2010
   Language: C++ (g++ target)
   
   Requires: green_acres
 */
 
  int oscar;                            //local variable
  oscar=dudley*nell;
  dudley=oscar+2;
  nell=dudley-1;
  cout<<"oscar = "<<oscar<<
        " dudley = "<<dudley<<
        " nell = "<<nell<<endl;
  green_acres(nell,oscar);             //no clue of parameter treatment
  cout<<"after call on green_acres"<<endl;
  cout<<"oscar = "<<oscar<<
        " dudley = "<<dudley<<
        " nell = " <<nell<<endl;
  return;
}


void green_acres(int &fred, int &arnold)  //fred and arnold are ref params
/*Illustrates cascading reference parameters
  Written by Ron
  January 2010

  Language: C++ (g++ target)
  Requires: nothing

*/

{ int haney;                  //local variable
  haney=fred+arnold*2;
  fred=haney+3;
  arnold=fred+haney;
  cout<<"In green_acres "<<endl;
  cout<<"fred = "<<fred<<
        " arnold = "<<arnold<<
        " haney = "<<haney<<endl;
  return;
} 
