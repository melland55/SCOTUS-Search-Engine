#ifndef HASHTABLEINVERTEDINDEX_H
#define HASHTABLEINVERTEDINDEX_H

#include <tuple>
#include <vector>
#include <string>

using namespace std;

class HashTableInvertedIndex
{
public:
    HashTableInvertedIndex();
    void add(string, string);
    vector<string> get(string);
private:
    int hash(string);
    void reHash();
    int entries;
    int arraySize;
    tuple<string, vector<string>>* invertedIndex;
};

#endif // HASHTABLEINVERTEDINDEX_H
