/*
Query the user for 8 strings and hashes each via an algorithm to store

Using HashTable class
    1. hash a word to recieve an index
    2. search the array if that index is available and move on if not
    3. store the word at the available index
    4. display the array in HashTable object

Written by Alex Ludwig
April 2026
Language: C++
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin25.3.0
*/

#include <iostream>
#include <string>

using namespace std;

class HashTable{

    private:
        static const int size = 8;
        string values[size];

        /*
        Hashes a word to an index in the table
        Uses the first and last letter of the word to compute a value [0,7]
        Written by Alex Ludwig
        Language: C++
        Apple clang version 17.0.0 (clang-1700.4.4.1)
        Target: arm64-apple-darwin25.3.0
        */
        int hash(string word){
            int firstLetter = (int)word[0];
            int lastLetter = (int)word[word.size()-1];
            int hashIndex = ((firstLetter*3+2) + (lastLetter-6))% 8;
            return hashIndex;
        }

    public:
        /*
        Constructor: initializes the hash table with "???" in all indicies
        Written by Alex Ludwig
        Language: C++
        Apple clang version 17.0.0 (clang-1700.4.4.1)
        Target: arm64-apple-darwin25.3.0
        */
        HashTable(){
            cout<<"Creating hash instance..."<<endl;
            for(int i=0; i<size; i++)
                values[i] = "???";
        } 

        /*
        Displays all contents of the hash table
        Written by Alex Ludwig
        Language: C++
        Apple clang version 17.0.0 (clang-1700.4.4.1)
        Target: arm64-apple-darwin25.3.0
        */
        void display(void){
            cout<<"Displaying Hash Table..."<<endl;
            for(int i=0; i<size; i++)
                cout<<i<<": "<<values[i]<<" "<<endl;
            cout<<endl;
        } 

        /*
        Stores a word at a specified index in the table
        Written by Alex Ludwig
        Language: C++
        Apple clang version 17.0.0 (clang-1700.4.4.1)
        Target: arm64-apple-darwin25.3.0
        */
        void storeWord(string word, int index){
            values[index] = word; 
        } 

        /*
        Finds the next available slot for a word, starting at its hash index
        Uses linear search to find empty slot ("???") 
        Written by Alex Ludwig
        Language: C++
        Apple clang version 17.0.0 (clang-1700.4.4.1)
        Target: arm64-apple-darwin25.3.0
        */
        void search(string word, int &index){
            bool freeSpace = false;
            int i = hash(word);
            int startingI = i;
            //Searches at $startingI to end pf @values
            for(i; i<size; i++){ 
                if(values[i]=="???"){
                    freeSpace = true;
                    break;
                }
            }
            //If free space still not found
            //search beginning of @values to $startingI
            if(!freeSpace){
                for(i=0; i<startingI; i++){
                    if(values[i]=="???"){
                        freeSpace = true;
                        break;
                    }
                }
            }
            index = i;

        }

        /*
        Searches the hash table staring at index hash(word)
        returns True if found and False otherwise
        Written by Alex Ludwig
        Language: C++
        Apple clang version 17.0.0 (clang-1700.4.4.1)
        Target: arm64-apple-darwin25.3.0
        */
        bool findWord(string word) {
            int index = hash(word);   
            int start = index;        

            
            while (values[index] != "???") {

                if (values[index] == word) {
                    return true; 
                }

                index = (index + 1) % size; 

                if (index == start) {
                    break;
                }
            }

            return false; 
        }
};

/*
Main Functions
Prompts user for 8 words, stores them in the hash table, and displays the table.
Written by Alex Ludwig
Language: C++
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin25.3.0
*/
int main(void){

    HashTable wordHash;
    string word;
    int index;

    cout<<"Please enter 5 words"<<endl;
    for(int i=0; i<5; i++){
        cin>>word;
        wordHash.search(word, index);
        wordHash.storeWord(word, index);
    }
    wordHash.display();

    while (true) {
    cout << "\nEnter a word to search (or type '999' to stop): ";
    cin >> word;

    if (word == "999") {
        break;
    }

    if (wordHash.findWord(word)) {
        cout << word << " FOUND in table." << endl;
    } else {
        cout << word << " NOT FOUND." << endl;
    }
    }

    return 0;
}