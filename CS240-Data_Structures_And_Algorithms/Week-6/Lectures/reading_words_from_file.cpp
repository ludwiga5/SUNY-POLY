/*Alternate means to read from a file
  Avoids last case issue with eof
  Written by Ron
  September 2021
  Language: C++98  Compiler: Cygwin mingw 64 bit g++
 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

int main(void)
{ string inputFileName;
  string s;
  ifstream fileIn;
  int word_count;
  word_count=0;
  cout<<"Enter name of file of characters: ";
  cin>>inputFileName;
  fileIn.open(inputFileName.data());
  assert(fileIn.is_open());
  while (fileIn>>s)
      {cout<<s<<"  "<<s.length()<<endl;
       word_count++;
      }
  cout<<"Number of words in file:  "<<word_count<<endl;
  return 0;
}

