#include <iostream>
#include <fstream>
#include <omp.h>
using  namespace  std;

/**
 * Word Occurrence Finder Algorithmic Steps  <br>
 * 1) Read file contents line by line. <br>
 * 2) For each line find if the searched word matches with the current iteration word (parallelism implemented here). <br>
 * 3) If match found, return the line number of the occurrence. <br>
 * 4) If no match found return notification message. <br>
 **/

bool searchForOccurrence(string text, string phrase, int lineCount){
    string delimiter = " ";
    size_t pos = 0;
    int count = 0;
    string token;
    bool foundSearch = false;
    while ((pos = text.find(delimiter)) != string::npos) {
        token = text.substr(0, pos);
        if (token == phrase){
            foundSearch = true;
            cout << "Wallah! The file does have the word " << "`"<< phrase <<"`" << " at line " << lineCount+1 << endl;
            break;
        }
        text.erase(0, pos + delimiter.length());
        count++;
    }
    return foundSearch;
}

int main() {
    //---User Input Search Phrase Start
    string userInputSearchPhrase;
    cout << "~~~~~WELCOME TO WORD OCCURRENCE FINDER~~~~~" << endl;
    cout << "This program finds occurrences of a word in a file and returns the line position of where the word is found" << endl;
    cout << "The search is case sensitive" << endl;
    cout << endl;
    cout << "~~~~START YOUR SEARCH~~~~~" << endl;
    cout << "Enter word to search: ";
    cin >> userInputSearchPhrase;
    cout << userInputSearchPhrase << endl;
    //---User Input Search Phrase End

    //---File Read Start------
    string text;
    int counter = 0;
    bool exitStatus = 0;
    ifstream MyFileReader("DummyText.txt");
    #pragma omp parallel
    {
        #pragma omp critical
        {
            while (getline(MyFileReader, text)) {
                if (searchForOccurrence(text, userInputSearchPhrase, counter)) {
                    cout << "Thread number " << omp_get_thread_num() << " found occurrence" <<endl;
                    exitStatus = 1;
                    break;
                }
                counter++;
            }
        }
    }
    if (exitStatus == 0){
        cout << "Oooops your search for " << "`"<< userInputSearchPhrase <<"`" << " found no match :)" << endl;
        cout << "Thread number: " << omp_get_thread_num() << " returned match not found notification" <<endl;
    }
    MyFileReader.close();
    //-----File Read End-------
    return 0;
}
