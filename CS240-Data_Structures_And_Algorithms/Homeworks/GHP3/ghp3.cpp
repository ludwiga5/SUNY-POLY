/*
Purpose: 

Query the user for the name of a file. Open and process that file, 
reporting the number of words in the file and the number of words 
containing each letter, and the length of that word. Assume that any 
word exceeding nine characters is counted as a ten character word. 
If the same letter appears more than once, it is counted only once. 
The result should be a matrix of 26 rows (one row for each letter) and 
ten columns (one column for each word length (1-10), and the contents of 
the matrix must be displayed.

As an example, assume the file contains only two words - “rotten” and “egg”. 
When processing “rotten”, rows for r, o, t, e and n would have the contents 
of column 6 incremented because “rotten” is a six letter word. When processing 
“egg”, rows for e and g would have the contents of column 3 incremented because 
“egg” is a three letter word.

Written by Alex Ludwig

March 2026
Language: C++
Compiler: g++ Apple clang version 17.0.0 (clang-1700.4.4.1)
*/


#include <iostream>
#include <fstream> //file readin functions
#include <string>
#include <cassert>
#include <cctype>  //toLower() & toUpper()

#define WIDTH 10   //max word length
#define HEIGHT 26  //a-z

using namespace std;

//Prototypes
void printMatrix(int mat[HEIGHT][WIDTH]);
void lettersAndLengths(string inputFile, int mat[HEIGHT][WIDTH]);


int main(void){

int letterCounts[HEIGHT][WIDTH] = {0};

cout<<"Please enter the name of the file you wish to filter"<<endl;
string inputFile;
cin>>inputFile;

lettersAndLengths(inputFile, letterCounts);
printMatrix(letterCounts);

return 0;

}


/*
Prints out matrix

Written by Alex Ludwig
March 2026
Language: C++
Compiler: g++ Apple clang version 17.0.0 (clang-1700.4.4.1)
*/
void printMatrix(int mat[HEIGHT][WIDTH]){

    for(int r=0; r<HEIGHT; r++){
        for(int c=0; c<WIDTH; c++)
            cout<<mat[r][c]<<" ";
        cout<<endl;
    }
}

/*
Reporting the number of words in the file and the number of words 
containing each letter, and the length of said word. Assume that any 
word exceeding nine characters is counted as a ten character word. 
If the same letter appears more than once per word, it is counted only once. 

Written by Alex Ludwig
March 2026
Language: C++
Compiler: g++ Apple clang version 17.0.0 (clang-1700.4.4.1)
*/
void lettersAndLengths(string inputFile, int mat[HEIGHT][WIDTH]){

    ifstream fileIn;
    string word;
    int wordLength;
    char ch;                        //sequential characters in file
    char includedLetters[HEIGHT-1]; //stores unique letters in a word
    int numberOfUniqueLetters = 0;  //counts the number of unique letters in a word
    bool uniqueLetter = true;       //temp to store if a letter is unique in a word
    int wordCt = 0;                 //word counter var
    int k = 0;                      //loop var
    bool endOfFile = false;



    // opens file and checks for failure
    fileIn.open(inputFile.data());
    assert(fileIn.is_open());

    // while file is not at the end - .eof() did not work
    while(!endOfFile){

        // runs while ch is a letter - per word
        while(fileIn.get(ch) && (('a'<=ch && ch<='z') || ('A'<=ch && ch<='Z'))){

            ch = tolower(ch);
            word.insert(k,1,ch);
            
            // checks if the current character is already in the word
            for(int i=0; i<numberOfUniqueLetters; i++){
                if(ch == includedLetters[i])
                    uniqueLetter = false;
            }
            // adds unique letters to array
            if(uniqueLetter){
                includedLetters[numberOfUniqueLetters] = ch;
                numberOfUniqueLetters++;
            }
            uniqueLetter = true; //resets unique check value
            k++;
        }

        wordLength = word.length();

        // increments matrix cells for word
        if(wordLength>0){

            for(int i=0; i<numberOfUniqueLetters; i++){
                cout<<includedLetters[i];
                if(wordLength>=10)
                    mat[includedLetters[i]-'a'][9]++;
                else
                    mat[includedLetters[i]-'a'][wordLength-1]++;
            }
            cout<<endl;
            wordCt++;
        }

        word.clear();
        k=0;
        numberOfUniqueLetters = 0;
        
        if(!fileIn) endOfFile = true;
    }

    fileIn.close();
    cout<<"Number of words in file: "<<wordCt<<endl;
}