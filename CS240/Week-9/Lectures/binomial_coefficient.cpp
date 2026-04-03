/*Program to demonstrate double recursion
  Calculate binomial coefficient
  Written by Ron
  November 2024
  Language: C++ (Cygwin 64-bit g++ compiler
*/

#include <iostream>

using namespace std;

int BC(int n, int k);

int main(void)
{ int n,k,result;
  cout<<"Enter values for n and k separated by a space: ";
  cin>>n>>k;
  result=BC(n,k);
  cout<<"Binomial coefficient of "<<n<<" and "<<k<<
      "is  "<<result<<endl;
  return 0;
}

int BC(int n, int k)
/*Function to calculate Binomial Coefficient
  Written by Ron
  November 2024
  Language: C++ (Cygwin 64-bit g++ compiler)
*/
{ int R1,R2,result;
  if ((k==0)||(n==k))
       result=1;
  else
    {R1=BC(n-1,k);
     R2=BC(n-1,k-1);
     result=R1+R2;
    }
  return (result);
}
  
