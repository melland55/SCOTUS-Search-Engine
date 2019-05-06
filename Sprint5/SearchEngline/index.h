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
    bool operator==(const string& temp){
        if(temp == entry){
            return true;
        }else{
            return false;
        }
    }
    bool operator>(const string& temp){
        if(temp < entry){
            return true;
        }else{
            return false;
        }
    }
    bool operator<(const string& temp){
        if(temp > entry){
            return true;
        }else{
            return false;
        }
    }
};

class Index
{
public:
    Index();
    ~Index();
    void clear();
    void add(string, string);
    vector<Entry>* getIndex();
private:
    vector<Entry> index;
};

#endif // INDEX_H
