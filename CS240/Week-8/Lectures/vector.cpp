//Program to illustrate use of the vector STL container
//Written by Ron
//Mid 2010s
//Language: C++ (g++ compiler)

#include <iostream>
#include <vector>

using namespace std;

int main(void)
{ 
  int peachfuzz[]={16,22,47,9,19,2};
  vector <int> rocky;
  vector <double> boris(5);
  vector <char> bw(5,'Q');
  vector <string> natasha (3,"hello");
  vector <int> cloyd(peachfuzz,peachfuzz+3);
  int i;
  cout<<rocky.capacity()<<rocky.size()<<endl;
  cout<<boris.capacity()<<boris.size()<<endl;
  cout<<bw.capacity()<<bw.size()<<endl;
  cout<<natasha.capacity()<<natasha.size()<<endl;
  rocky.push_back(1);
  cout<<rocky.capacity()<<rocky.size()<<endl;
  cout<<rocky[0]<<rocky[1];
  rocky.push_back(15);
  cout<<rocky.capacity()<<" "<<rocky.size()<<endl;
  cout<<rocky.front()<<endl;
  for (i=0; i<=5; i++)
     cout<<cloyd[i]<<" ";
  cout<<endl;
  return 0;
} 
