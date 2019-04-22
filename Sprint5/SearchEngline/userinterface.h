#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <string>
#include <vector>
#include "courtcase.h"
#include "hashtableinvertedindex.h"
#include "jsonparser.h"


class UserInterface
{
public:
    UserInterface();
    UserInterface(bool);
    void run(HashTableInvertedIndex<string, string>&);
    void maintenacenMode(HashTableInvertedIndex<string, string>&);
    void interactiveMode();
    void addToIndex(string);
    void clearIndex();
    void newSearch(string);
    void displayResults();
private:
    bool isHash;
    vector<CourtCase> results;
};

#endif // USERINTERFACE_H
