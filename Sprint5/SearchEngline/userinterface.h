#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <string>
#include <vector>
#include "courtcase.h"


class UserInterface
{
public:
    UserInterface();
    UserInterface(bool);
    void run();
    void maintenacenMode();
    void interactiveMode();
    void addToIndex(String);
    void clearIndex();
    void newSearch(String);
    void displayResults();
private:
    bool isHash;
    Vector<CourtCase> results;
};

#endif // USERINTERFACE_H
