#ifndef HASHTABLEINVERTEDINDEX_H
#define HASHTABLEINVERTEDINDEX_H

//Include needed libraries for the court case class
#include <vector>
#include <string>

using namespace std;

template <typename J, typename T>
struct Entry {
    J entry;
    vector<T>* occurrences;

    Entry(){
        entry = "";
        occurrences = new vector<T>();
    }

    Entry(string tEntry){
        entry = tEntry;
        occurrences = new vector<T>();
    }

    Entry(string tEntry, T loc){
        entry = tEntry;
        occurrences = new vector<T>();
        occurrences->push_back(loc);
    }

    bool operator==(const Entry& entry){
        return this->entry == entry.entry;
    }
};

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
    vector<Entry<T, J>>* invertedIndex;
};

#endif // HASHTABLEINVERTEDINDEX_H
