#include <iostream>
#include <sstream>
#include <fstream>
#include<algorithm>
#include <stdio.h>
#include "userinterface.h"
#include "porter2_stemmer.h"

using namespace std;

UserInterface::UserInterface(){
    isHash = true;
}

UserInterface::UserInterface(bool dec){
    isHash = dec;
}

void UserInterface::run(HashTableInvertedIndex<string, string>& hashTable){
    cout << "╔════════════════════════╗" << endl;
    cout << "║Welcome to Scotus Search║" << endl;
    cout << "╚════════════════════════╝" << endl << endl;
    cout << "  Please Select Run Mode  " << endl;
    cout << "──────────────────────────" << endl;
    cout << "M : Maintenance Mode" << endl;
    cout << "I : Interactive Mode" << endl;
    cout << "Q : Quit" << endl;
    char mode;
    cin >> mode;
    cout << endl;
    if(tolower(mode) == 'q'){
        return;
    }else if(tolower(mode) == 'm'){
        maintenacenMode(hashTable);
    }else{
        interactiveMode(hashTable);
    }
}

void UserInterface::maintenacenMode(HashTableInvertedIndex<string, string>& hashTable){
    cout << "╭────────────────────────╮" << endl;
    cout << "│    Maintenance Mode    │" << endl;
    cout << "╰────────────────────────╯" << endl << endl;
    cout << "   Please Select Action   " << endl;
    cout << "──────────────────────────" << endl;
    cout << "clear : Clears the Index Completely" << endl;
    cout << "fileName : Directory of File to Add Cases" << endl;
    cout << "Q : Quit to Mode Selection" << endl;
    string fileName;
    cin >> fileName;
    cout << endl;
    if(fileName.length() == 1 && tolower(fileName[0]) == 'q'){
        run(hashTable);
    }else if(fileName == "clear"){
        //Clear Index
    }else{
        JsonParser json;
        ifstream test(fileName);
        if(!test.is_open()){
            cout << "           Warning" << endl;
            cout << "╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳";
            for(int i = 0; i < fileName.length(); i++){
                cout << "╳";
            }
            cout << endl;
            cout << "╳Directory \"" << fileName << "\" Does not Exist╳" << endl;
            cout << "╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳";
            for(int i = 0; i < fileName.length(); i++){
                cout << "╳";
            }
            cout << endl;
            cout << "Please Enter New Selection" << endl;
            maintenacenMode(hashTable);
        }else{
            int num = 0;
            cout << "Opening " << fileName << " and Parsing Files..." << endl;
            //num = json.parseFiles(fileName, hashTable);
            if(num == 0){
                cout << "--No Files Found in Directory " << fileName << endl;
                maintenacenMode(hashTable);
            }else{
                cout << num << " Files Loaded Succsesfully" << endl;
                run(hashTable);
            }
        }
    }
}

void UserInterface::interactiveMode(HashTableInvertedIndex<string, string>& hashTable){
    cout << "╭────────────────────────╮" << endl;
    cout << "│    Interactive Mode    │" << endl;
    cout << "╰┬──────────────────────┬╯" << endl;
    cout << " │Cur Index : ";
    if(isHash){
        cout << "Hash Table│ " << endl;
    }else{
        cout << "AVL Tree  │ " << endl;
    }
    cout << " ╰──────────────────────╯ " << endl << endl;
    cout << "   Please Select Action   " << endl;
    cout << "──────────────────────────" << endl;
    cout << "A : Loads Index into AVL Tree" << endl;
    cout << "H : Loads Index into Hash Table" << endl;
    cout << "S : Search Mode" << endl;
    cout << "Q : Quit to Mode Selection" << endl;
    string mode;
    cin >> mode;
    cout << endl;
    if(mode.length() == 1 && tolower(mode[0]) == 'q'){
        run(hashTable);
    }else if(mode.length() == 1 && tolower(mode[0]) == 'a'){
        isHash = false;
        interactiveMode(hashTable);
    }else if(mode.length() == 1 && tolower(mode[0]) == 'h'){
        isHash = true;
        interactiveMode(hashTable);
    }else if(mode.length() == 1 && tolower(mode[0]) == 's'){
        searchMode(hashTable);
        interactiveMode(hashTable);
    }else{
        interactiveMode(hashTable);
    }
}

void UserInterface::searchMode(HashTableInvertedIndex<string, string>& hashTable){
    cout << endl << endl;
    cout << "┍╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼┒" << endl;
    cout << "╿       Search Mode      ╽" << endl;
    cout << "┖╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾┙" << endl << endl;
    cout << "   Please Input Properly" << endl;
    cout << "  Formatted Boolean Query" << endl;
    cout << "    Type QUIT to quit" << endl;
    cout << "──────────────────────────" << endl;
    cout << "SEARCH: ";
    string line;
    cin.ignore();
    getline(cin, line);
    cout << "──────────────────────────" << endl;
    if(line == "QUIT"){
        return;
    }
    stringstream query(line);
    string temp;
    vector<string> ands;
    vector<string> ors;
    vector<string> nots;
    while(getline(query, temp, ' ')){
        if(temp == "AND"){
            while(getline(query, temp, ' ') && (temp != "OR" && temp != "NOT")){
                if(temp[0] == '['){
                    string bigWord = temp;
                    while(getline(query, temp, ' ') && temp[temp.length() - 1] != ']'){
                        bigWord += " ";
                        bigWord += temp;
                    }
                    bigWord += " ";
                    bigWord += temp;
                    bigWord.erase(bigWord.begin());
                    bigWord.erase(bigWord.end() - 1, bigWord.end());
                    Porter2Stemmer::stem(bigWord);
                    ands.push_back(bigWord);
                }else{
                    Porter2Stemmer::stem(temp);
                    ands.push_back(temp);
                }
            }
        }else{
            if(temp[0] == '['){
                string bigWord = temp;
                while(getline(query, temp, ' ') && temp[temp.length() - 1] != ']'){
                    bigWord += " ";
                    bigWord += temp;
                }
                bigWord += " ";
                bigWord += temp;
                bigWord.erase(bigWord.begin());
                bigWord.erase(bigWord.end() - 1, bigWord.end());
                Porter2Stemmer::stem(bigWord);
                ands.push_back(bigWord);
            }else{
                Porter2Stemmer::stem(temp);
                ands.push_back(temp);
            }
        }
        if(temp == "OR"){
            while(getline(query, temp, ' ') && (temp != "AND" && temp != "NOT")){
                if(temp[0] == '['){
                    string bigWord = temp;
                    while(getline(query, temp, ' ') && temp[temp.length() - 1] != ']'){
                        bigWord += " ";
                        bigWord += temp;
                    }
                    bigWord += " ";
                    bigWord += temp;
                    bigWord.erase(bigWord.begin());
                    bigWord.erase(bigWord.end() - 1, bigWord.end());
                    Porter2Stemmer::stem(bigWord);
                    ors.push_back(bigWord);
                }else{
                    Porter2Stemmer::stem(temp);
                    ors.push_back(temp);
                }
            }
        }
        if(temp == "NOT"){
            while(getline(query, temp, ' ') && (temp != "OR" && temp != "AND")){
                if(temp[0] == '['){
                    string bigWord = temp;
                    while(getline(query, temp, ' ') && temp[temp.length() - 1] != ']'){
                        bigWord += " ";
                        bigWord += temp;
                    }
                    bigWord += " ";
                    bigWord += temp;
                    bigWord.erase(bigWord.begin());
                    bigWord.erase(bigWord.end() - 1, bigWord.end());
                    Porter2Stemmer::stem(bigWord);
                    nots.push_back(bigWord);
                }else{
                    Porter2Stemmer::stem(temp);
                    nots.push_back(temp);
                }
            }
        }
    }
    //vector<CourtCase> cases = hashTable.findCases();
    vector<CourtCase> cases;
    for(int i = 0; i < 35; i++){
        CourtCase file;
        cases.push_back(file);
    }
    string userInput = "?";
    int sum = 0;
    cout << endl;
    cout << "         RESULTS    " << endl;
    cout << "┍╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼┒" << endl;
    cout << "╿ Documents Found : ";
    cout << cases.size();
    for(int i = to_string(cases.size()).length(); i < 5; i++){
        cout << " ";
    }
    cout << "╽" << endl;
    cout << "┖╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾╾┙" << endl << endl;
    while(userInput != "q" && sum < cases.size()){
        if(userInput == "m"){
            userInput = "i";
        }
        for(int i = sum; i < cases.size() && i < sum + 10 ; i++){
            //cases[i].print(i);
            cout << i << endl;
        }
        sum += 10;
        while(userInput != "q" && userInput != "m"){
            if(userInput != "?" && userInput != "i"){
                cout << endl;
                cout << "╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳" << endl;
                cout << "╳ Error: Incorect Input ╳" << endl;
                cout << "╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳" << endl;
                cout << endl;
            }
            if(sum < cases.size()){
                cout << "Press M to Print Another Page" << endl;
            }else{
                cout << "No More Search Results" << endl;
            }
            cout << "Press Q to Quit";
            cin >> userInput;
            transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
        }
    }
    searchMode(hashTable);
}

void UserInterface::addToIndex(string){

}

void UserInterface::clearIndex(){

}

void UserInterface::displayResults(){

}

