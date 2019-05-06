#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <string>
#include <vector>
#include "courtcase.h"
#include "index.h"
#include "invertedindexinterface.h"
#include "avltreeinvertedindex.h"
#include "hashtableinvertedindex.h"
#include "jsonparser.h"


class UserInterface
{
public:
    UserInterface();
    UserInterface(bool);
    void run();
    void maintenacenMode();
    void interactiveMode();
    void searchMode();
    void addToIndex(string);
    void clearIndex();
    void displayResults();
private:
    bool isHash;
    Index index;
    //InvertedIndexInterface<Entry> iif;
    AVLTreeInvertedIndex<Entry>* avlTree;
    HashTableInvertedIndex<Entry>* hashTable;
    vector<CourtCase> results;
};

#endif // USERINTERFACE_H
