#ifndef HASHTABLEINVERTEDINDEX_H
#define HASHTABLEINVERTEDINDEX_H

#include <courtcase.h>
#include <tuple>
#include <vector>

template <typename J, typename T>
class HashTableInvertedIndex
{
public:
    HashTableInvertedIndex();
    void add(J, T);
    vector<T> get(J);
private:
    int hash(J);
    void reHash();
    int entries;
    int arraySize;
    tuple<J, vector<T>>* invertedIndex;
};

#endif // HASHTABLEINVERTEDINDEX_H
