/*Program to illustrate use of the CodeBlocks environment
Consists of main and a function employing input (pass by value)
parameters.
Written by Ron
August 2015
Language: C++ Environment: CodeBlocks 13.12
Compiler: GNU C++
*/
#include <iostream>
using namespace std;
void doit(int cloyd, int gidney, int moonmen); //function prototype
int main(void)
{int rocky, bw, boris;
rocky=3;
bw=4;
boris=rocky+bw;
cout<<"before function call rocky = "<<rocky<<endl<<
"bw = "<<bw<<endl<<
"boris = "<<boris<<endl;
doit(rocky,bw,boris);
cout<<"after function call rocky = "<<rocky<<endl<<
"bw = "<<bw<<endl<<
"boris = "<<boris<<endl;
return 0;
}
void doit(int cloyd, int gidney, int moonmen)
/*Function to demonstrate pass by value (input parameter)
Written by Ron
August 2015
Language: C++ Environment: CodeBlocks 13.12
Compiler: GNU C++
*/
{
cout<<"Entering doit"<<endl<<
"cloyd = "<<cloyd<<endl<<
"gidney = "<<gidney<<endl<<
"moonmen = "<<moonmen<<endl;
moonmen=moonmen*cloyd;
cloyd=moonmen+3;
gidney=cloyd*4;
cout<<"Leaving doit"<<endl<<
"cloyd = "<<cloyd<<endl<<
"gidney = "<<gidney<<endl<<
"moonmen = "<<moonmen<<endl;
return;
}