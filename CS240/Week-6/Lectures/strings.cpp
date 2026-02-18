#include <iostream>
#include <string>

using namespace std;

int main (void){


    string str;

    //boolalpha prints true or false instead of 1 or 0
    cout<<"str is empty "<<boolalpha<<str.empty()<<endl;
    cout<<"the number of characters in str is "<<str.size()<<endl;
    cout<<"the capacity of str is "<<str.capacity()<<endl;
    cout<<"str is "<<str<<endl;

    //alternative to = operator
    string str2("apple");
    cout<<"the number of characters in str2 is "<<str2.length()<<endl;
    cout<<"the capacity of str2 is "<<str2.capacity()<<endl;
    cout<<"str2 is "<<str2<<endl;
    //concatenates banana to the end of str2
    str2.append("banana");
    cout<<"str2 is now "<<str2<<endl;

    //3 is the length and truncates anything after index 2.
    string str3("orange", 3);
    cout<<"the number of characters in str3 is "<<str3.length()<<endl;
    cout<<"str3 is "<<str3<<endl;

    //goes to the 4th index and assigns the next 2 indicies
    string str4("watermelon", 4, 2);
    cout<<"the number of characters in str4 is "<<str4.length()<<endl;
    cout<<"str4 is "<<str4<<endl;

    //Creates a string with 500 '*'s
    string str5(500, '*');
    cout<<"str5 is "<<str5<<endl;
}