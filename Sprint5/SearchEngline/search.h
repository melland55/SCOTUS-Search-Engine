#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include "courtcase.h"
using namespace std;

class Search
{
public:
    Search();
    Search(vector<string>*, vector<string>*, vector<string>*);
    vector<CourtCase>* getResults();
private:
    vector<CourtCase>* results;
};

#endif // SEARCH_H
