#include <iostream>
#include "userinterface.h"

using namespace std;

UserInterface::UserInterface(){

}

UserInterface::UserInterface(bool){

}

void UserInterface::run(HashTableInvertedIndex<string, string>& hashTable){
    cout << "╔════════════════════════╗" << endl;
    cout << "║Welcome to Scotus Search║" << endl;
    cout << "╚════════════════════════╝" << endl << endl;
    cout << "  Please Select Run Mode  " << endl;
    cout << "──────────────────────────" << endl;
    cout << "M : Maintenance Mode" << endl;
    cout << "I : Interactive Mode" << endl;
    char mode;
    cin >> mode;
    cout << endl;
    if(mode == 'M'){
        maintenacenMode(hashTable);
    }else{
        interactiveMode();
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
    string fileName;
    cin >> fileName;
    cout << endl;
    if(fileName == "clear"){
        //Clear Index
    }else{
        JsonParser json;
        //int num = json.parseFiles(fileName, hashTable);
    }
}

void UserInterface::interactiveMode(){

}

void UserInterface::addToIndex(string){

}

void UserInterface::clearIndex(){

}

void UserInterface::newSearch(string){

}

void UserInterface::displayResults(){

}

