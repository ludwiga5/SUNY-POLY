/*---------------------------------------------------------------------
                  Driver program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
using namespace std;
	
#include "Queue.h"

int main()
{
   Queue q1;
   cout << "Queue created.  Empty? " << boolalpha << q1.empty() << endl;

   cout << "How many elements to add to the queue? ";
   int numItems;
   cin >> numItems;
   for (int i = 1; i <= numItems; i++) 
      q1.enqueue(100*i);

   cout << "Contents of queue:\n";
   q1.display(cout); 
   cout << "Queue q1 empty? " << q1.empty() << endl;
   
   cout << "\nFront value in q1: " << q1.front() << endl << endl;

   while (!q1.empty())
   {
     cout << "Remove front -- Queue contents: ";
     q1.dequeue();
     q1.display(cout);
   }
   cout << "\nQueue q1 empty? " << q1.empty() << endl;
   cout << "Now try to retrieve front value in q1" << endl;
   cout << "Front value in q1?" << endl << q1.front() << endl;
   cout << "\nNow Try to remove front of q1: " << endl;
   q1.dequeue();
}
