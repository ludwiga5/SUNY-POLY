/*Program to demonstrate use of file input
  and string handling in C++

  Written by Ron 
  Some adaptation of Fig 5-1 from Nyhoff
  February 2011
  Language: C++  (g++ target)
*/
  


#include <iostream>
//file input
#include <fstream>
//string inclusion
#include <string>
#include <cassert>
#include <cstdio>

using namespace std;

int main(void)
{int i;
 string inputFileName;
 string s;
 ifstream fileIn;
 char ch;
 cout<<"Enter name of file of characters :";
 cin>>inputFileName;
 fileIn.open(inputFileName.data());
 assert(fileIn.is_open() );
 i=0;
 while (!(fileIn.eof()))
  {ch=fileIn.get();
   s.insert(i,1,ch);     //insert character at position i
   i++;
  }
 cout<<s;
 cout<<"The length of s is "<<s.length()<<endl;
 cout<<"The capacity of s is "<<s.capacity()<<endl;
 cout<<"Looking for string bw"<<endl;
 cout<<"found at position "<<s.find("bw")<<endl;

 return 0;
}
