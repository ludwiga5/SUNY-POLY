/*
Purpose:
Queries the user for the name of a file containing one word per line.

Open that file, process each word using basic stack and queue operations to determine if it
is a palindrome, and if so, print it.

At the end report the total number of palindromes found and the total number of words processed.

Also keep track of the number of palindromes containing the letter m (irrespective of case),
and the length of each palindrome containing an m.

At the end display the number of these palindromes containing an m, and all of those sharing 
the longest length. Thus, if the longest palindrome containing a m is seven characters long,
all seven character palindromes containing an m must be displayed.

Written by Alex Ludwig
March 2026
Language: C++
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin25.3.0
*/

#include <iostream>
#include <cctype> //tolower()
#include <fstream> //file readin functions
#include <cassert>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

//prototypes
bool checkPalindrome(string word);
void parseFile(ifstream &file);
void tolowercase(string &word);

int main(void){

    //user input for filename
    cout<<"Please enter the name of the file you wish to filter"<<endl;
    string inputFile;
    cin>>inputFile;

    //open $inputFile
    ifstream fileIn;
    fileIn.open(inputFile.data());
    assert(fileIn.is_open());

    parseFile(fileIn);

return 0;
}

/*
Purpose:
Uses tolower() to make an entire string lowercase

Written by Alex Ludwig
April 2026
Language: C++
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin25.3.0
*/
void tolowercase(string &word){
    for(int i=0; i<word.length(); i++)
        word[i] = tolower(word[i]);
}

/*
Purpose:
Checks if a word is a palindrome by comparing the top of
a Stack to the Front of a queue

Written by Alex Ludwig
April 2026
Language: C++
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin25.3.0
*/
bool checkPalindrome(string word){

    stack<char> stack;
    queue<char> queue;
    bool isPalindrome = true;
    int wordLength = word.length();

    //fill stack & queue
    for(int i=0; i<wordLength; i++){
        stack.push(word[i]);
        queue.push(word[i]);
    }
    //checks if $word is a palindrome
    for(int i=0; i<wordLength && isPalindrome; i++){
        if(stack.top() != queue.front())
            isPalindrome = false;
        stack.pop();
        queue.pop();
    }

    return isPalindrome;

}
/*
Purpose:
Checks if a word is a palindrome, if so print it
Reports total number of word processed and the number of palindromes found
Displays the number of these palindromes containing an m, and all of those sharing 
the longest length. Thus, if the longest palindrome containing an 'm' 
is seven characters long,
all seven character palindromes containing an m must be displayed.

Duplicate palindomes are NOT counted due to "irrespective of case"

Written by Alex Ludwig
April 2026
Language: C++
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin25.3.0
*/
void parseFile(ifstream &file){

    int wordCounter =0;
    int palindromeCounter = 0;
    int palindromeWithMCounter = 0;
    vector<string> palindromesWithM;
    string word;
    int wordLength;
    int maxWordLength=0;

    while(getline(file ,word)){

        wordLength = word.length();
        if(wordLength>0){
            wordCounter++;
            tolowercase(word);

            if(checkPalindrome(word)){
                palindromeCounter++;
                for(char c : word){
                    if(c == 'm'){
                        //searches @palindromWithM for word to prevent duplicates
                        if (find(palindromesWithM.begin(), palindromesWithM.end(), word) == palindromesWithM.end()){
                            palindromesWithM.push_back(word);
                            palindromeWithMCounter++;
                        }
                        if(maxWordLength<wordLength)
                            maxWordLength = wordLength;
                        break;                    
                    }
                }
            }
        }
    }


    //output
    cout<<"Total number of words processed: "<<wordCounter<<endl;
    cout<<"Total number of palindromes:     "<<palindromeCounter<<endl;
    cout<<endl;
    cout<<"Total palindromes with letter m: "<<palindromeWithMCounter<<endl;
    cout<<"Palindromes with 'm' and length "<<maxWordLength<<":"<<endl;

    for(int i=0; i<palindromesWithM.size(); i++)
        if(palindromesWithM[i].length() == maxWordLength)
            cout<<palindromesWithM[i]<<endl;


}