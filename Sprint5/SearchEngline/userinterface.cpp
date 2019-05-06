#include <iostream>
#include <sstream>
#include <fstream>
#include<algorithm>
#include <stdio.h>
#include "userinterface.h"
#include "porter2_stemmer.h"
#include "avltreeinvertedindex.h"
#include "hashtableinvertedindex.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

//Sets Defualt Inverted Index to AVLTree
UserInterface::UserInterface(){
    isHash = false;
}

//Runs the Main User Interface for Scotus Search
void UserInterface::run(){
    cout << "╔════════════════════════╗" << endl;
    cout << "║Welcome to Scotus Search║" << endl;
    cout << "╚════════════════════════╝" << endl << endl;
    cout << "  Please Select Run Mode  " << endl;
    cout << "──────────────────────────" << endl;
    cout << "M : Maintenance Mode" << endl;
    cout << "I : Interactive Mode" << endl;
    cout << "Q : Quit" << endl;

    //Runs Mode Selected by User
    char mode;
    cin >> mode;
    cout << endl;
    if(tolower(mode) == 'q'){
        return;
    }else if(tolower(mode) == 'm'){
        maintenacenMode();
    }else{
        interactiveMode();
    }
}

//Maintenacne Mode allows user to Load File Indexes and clear the Index
void UserInterface::maintenacenMode(){
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
        run();
    }else if(fileName == "clear"){
        cout << endl << "Index Cleared" << endl;
        index.clear();
        maintenacenMode();
    }else{
        JsonParser json;
        ifstream test(fileName);
        if(!test.is_open()){
            cout << "           ";
            for(unsigned int i = 0; i < fileName.length() / 2; i++){
                cout << " ";
            }
            cout << "Warning" << endl;
            cout << "╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳";
            for(unsigned int i = 0; i < fileName.length(); i++){
                cout << "╳";
            }
            cout << endl;
            cout << "╳Directory \"" << fileName << "\" Does not Exist╳" << endl;
            cout << "╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳";
            for(unsigned int i = 0; i < fileName.length(); i++){
                cout << "╳";
            }
            cout << endl << endl;
            cout << "Please Enter New Selection" << endl;
            maintenacenMode();
        }else{
            test.close();
            cout << "Opening " << fileName << " and Parsing Files..." << endl;
            int num = JsonParser::parseFiles(fileName, index);
            if(num == 0){
                cout << "--No Files Found in Directory " << fileName << endl;
            }else{
                cout << num << " Files Loaded Succsesfully" << endl << endl;
            }
            maintenacenMode();
        }
    }
}

void UserInterface::interactiveMode(){
    cout << "Loading Index..." << endl;
    if(!isHash && !index.getIndex()->empty()){
        iii = new AVLTreeInvertedIndex<Entry>(*index.getIndex());
    }else{
        iii = new HashTableInvertedIndex<Entry>(*index.getIndex());
    }
    cout << endl;
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
        run();
    }else if(mode.length() == 1 && tolower(mode[0]) == 'a'){
        isHash = false;
        interactiveMode();
    }else if(mode.length() == 1 && tolower(mode[0]) == 'h'){
        isHash = true;
        interactiveMode();
    }else if(mode.length() == 1 && tolower(mode[0]) == 's'){
        searchMode();
        interactiveMode();
    }else{
        interactiveMode();
    }
}

void UserInterface::searchMode(){
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
    vector<CourtCase> cases = search(ands, ors, nots);
    string userInput = "?";
    unsigned int sum = 0;
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
        for(unsigned int i = sum; i < cases.size() && i < sum + 10 ; i++){
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
    searchMode();
}

vector<CourtCase> UserInterface::search(vector<string>& ands, vector<string>& ors, vector<string>& nots){
    vector<CourtCase> cases;
    vector<tuple<string, int>> results;
    for(unsigned int i = 0; i < ands.size(); i++){
        Entry* entry = iii->find(ands.at(i));
        if(entry != nullptr){
            if(i == 0){
                for(unsigned int j = 0; j < entry->occurrences.size(); j++){
                    results.push_back(entry->occurrences.at(j));
                }
            }else{
                for(unsigned int j = 0; j < results.size(); j++){
                    bool dec = true;
                    for(unsigned int k = 0; k < entry->occurrences.size(); k++){
                        if(get<0>(entry->occurrences.at(k)) == get<0>(results.at(j))){
                            dec = false;
                            get<1>(results.at(j)) += get<1>(entry->occurrences.at(k));
                        }
                    }
                    if(dec){
                        results.erase(results.begin() + j);
                        j--;
                    }
                }
            }
        }
    }

    if(!ors.empty()){
        vector<tuple<string, int>> allOrs;
        Entry* newOr = iii->find(ors.at(0));
        for(unsigned int j = 0; j < newOr->occurrences.size(); j++){
            allOrs.push_back(newOr->occurrences.at(j));
        }
        for(unsigned int j = 1; j < ors.size(); j++){
            Entry* tempOr = iii->find(ors.at(j));
            for(unsigned int k = 0; k < allOrs.size(); k++){
                for(unsigned int l = 0; l < tempOr->occurrences.size(); l++){
                    if(get<0>(tempOr->occurrences.at(l)) == get<0>(allOrs.at(k))){
                        get<1>(allOrs.at(k)) += get<1>(tempOr->occurrences.at(l));
                        tempOr->occurrences.erase(tempOr->occurrences.begin() + l);
                    }
                }
            }
            for(unsigned int k = 0; k < tempOr->occurrences.size(); k++){
                allOrs.push_back(tempOr->occurrences.at(k));
            }
        }
        if(results.empty()){
            for(unsigned int j = 0; j < allOrs.size(); j++){
                results.push_back(allOrs.at(j));
            }
        }else{
            for(unsigned int j = 0; j < results.size(); j++){
                bool dec = true;
                for(unsigned int k = 0; k < allOrs.size(); k++){
                    if(get<0>(allOrs.at(k)) == get<0>(results.at(j))){
                        dec = false;
                        get<1>(results.at(j)) += get<1>(allOrs.at(k));
                    }
                }
                if(dec){
                    results.erase(results.begin() + j);
                    j--;
                }
            }
        }
    }

    if(!nots.empty()){
        vector<tuple<string, int>> allNots;
        Entry* newNot = iii->find(nots.at(0));
        if(newNot != nullptr){
            for(unsigned int j = 0; j < newNot->occurrences.size(); j++){
                allNots.push_back(newNot->occurrences.at(j));
            }
            for(unsigned int j = 1; j < nots.size(); j++){
                Entry* tempNot = iii->find(nots.at(j));
                for(unsigned int k = 0; k < allNots.size(); k++){
                    for(unsigned int l = 0; l < tempNot->occurrences.size(); l++){
                        if(get<0>(tempNot->occurrences.at(l)) == get<0>(allNots.at(k))){
                            tempNot->occurrences.erase(tempNot->occurrences.begin() + l);
                        }
                    }
                }
            }
            for(unsigned int j = 0; j < results.size(); j++){
                for(unsigned int k = 0; k < allNots.size(); k++){
                    if(get<0>(allNots.at(k)) == get<0>(results.at(j))){
                        results.erase(results.begin() + j);
                        j--;
                    }
                }
            }
        }
    }
    sort(results.begin(), results.end(), tupleSort);
    for(unsigned int i = 0; i < results.size(); i++){
        try{
            json file = json::parse(get<0>(results.at(i)));
            CourtCase tempCase(file.at("date_created"), file.at("id"), get<0>(results.at(i)));
            cases.push_back(tempCase);
        } catch(...){
            CourtCase tempCase("", "", get<0>(results.at(i)));
            cases.push_back(tempCase);
        }
    }
}

bool UserInterface::tupleSort(const tuple<string, int>& x, const tuple<string, int>& y){
    return (get<1>(x) > get<1>(y));
}
