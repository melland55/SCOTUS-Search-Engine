#ifndef HASHTABLEINVERTEDINDEX_H
#define HASHTABLEINVERTEDINDEX_H

#include <tuple>
#include <vector>
#include <string>

using namespace std;

template <typename J, typename T>
class HashTableInvertedIndex
{
public:
    HashTableInvertedIndex();
    //add(J key, T value, int occur = 1)
    void add(J, T);
    vector<T> get(J);
    int getNumWords();
private:
    int hash(J);
    void reHash();
    int entries;
    int arraySize;
    tuple<J, vector<T>>* invertedIndex;
};

#endif // HASHTABLEINVERTEDINDEX_H
