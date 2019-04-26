#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <string>
#include <vector>
#include "courtcase.h"
#include "index.h"
#include "jsonparser.h"


class UserInterface
{
public:
    UserInterface();
    UserInterface(bool);
    void run(Index&);
    void maintenacenMode(Index&);
    void interactiveMode(Index&);
    void searchMode(Index&);
    void addToIndex(string);
    void clearIndex();
    void displayResults();
private:
    bool isHash;
    vector<CourtCase> results;
};

#endif // USERINTERFACE_H
