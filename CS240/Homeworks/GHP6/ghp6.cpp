/*
Query the user for ten integer values and store them in an appropriate STL container.

Using STL algorithms, calculate and display:

1. the number of items in the container.
2. the smallest value, the largest value, the arithmetic mean (the average)
3. the partial sum (if the values are 1,2,3, the partial sums are 1,3,6)
4. the difference from one item to the next (if the values are 6,9,4, the differences are 6, 3, -5)

Written by Alex Ludwig
April 2026
Language: C++
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin25.3.0
*/

#include <iostream>
#include <algorithm> //sort()
#include <numeric>   //accumulate(), partial_sum(), adjacent_difference()
#include <vector>    //size(), begin(), end()

using namespace std;

int main(void){

vector<int> nums(10);

//fill nums
cout<<"Please enter 10 integers: "<<endl;
for(int i=0; i<10; i++)
    cin >> nums[i];

//Pt 1
int size = nums.size();
cout<<"Number of items in container: "<<size<<endl;

//Pt 2
vector<int> sorted = nums;
sort(sorted.begin(), sorted.end());
double mean = accumulate(sorted.begin(), sorted.end(), 0.0)/size;
cout<<"Smallest value in container: "<<*sorted.begin()<<endl;
cout<<"Largest value in container: "<<*(sorted.end()-1)<<endl;
cout<<"Mean of container: "<<mean<<endl;

//Pt 3
vector<int> partialSum(nums.size());
partial_sum(nums.begin(), nums.end(), partialSum.begin());
cout<<"Partial Sum: ";
for(int i : partialSum)
    cout<<i<<"  ";
cout<<endl;

//Pt 4
vector<int> adjacentDifference(nums.size());
adjacent_difference(nums.begin(), nums.end(), adjacentDifference.begin());
cout<<"Adjacent Differences: ";
for(int i : adjacentDifference)
    cout<<i<<"  ";
cout<<endl;

}