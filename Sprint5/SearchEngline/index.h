#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

struct Entry{
    string entry;
    vector<tuple<string, int>> occurrences;
};

class Index
{
public:
    Index();
    ~Index();
    void clear();
    void add(string, string);
    vector<tuple<string, vector<tuple<string, int>>>>* getIndex();
private:
    vector<tuple<string, vector<tuple<string, int>>>> index;
};

#endif // INDEX_H
