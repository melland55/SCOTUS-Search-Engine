#ifndef HASHTABLEINVERTEDINDEX_H
#define HASHTABLEINVERTEDINDEX_H

//Include needed libraries for the court case class
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include "index.h"
#define MAX_CHAIN_LEN 5

using namespace std;

template <typename J, typename T>
class HashTableInvertedIndex
{
public:
    HashTableInvertedIndex();
    HashTableInvertedIndex(int);
    HashTableInvertedIndex(vector<Entry>);
    void add(Entry);
    vector<tuple<T, int>> get(J);
    int getNumWords();
    int getArraySize();
    HashTableInvertedIndex<J,T>* operator=(HashTableInvertedIndex);
private:
    int hash(J, int);
    void reHash();
    int entries;
    int arraySize;
    vector<Entry>* invertedIndex;
};

template <typename J, typename T>
HashTableInvertedIndex<J,T>::HashTableInvertedIndex(){
    arraySize = 997;
    invertedIndex = new vector<Entry>[arraySize];
    entries = 0;
}

template <typename J, typename T>
HashTableInvertedIndex<J,T>::HashTableInvertedIndex(int size){
    arraySize = size;
    invertedIndex = new vector<Entry>[arraySize];
    entries = 0;
}

template <typename J, typename T>
HashTableInvertedIndex<J,T>::HashTableInvertedIndex(vector<Entry> vect){
    entries = static_cast<int>(vect.size());
    arraySize = static_cast<int>(entries * 0.8);
    invertedIndex = new vector<Entry>[arraySize];

    for(unsigned long k = 0;k < vect.size();k++) {
        this->add(vect.at(k));
    }
}

template <typename J, typename T>
void HashTableInvertedIndex<J,T>::add(Entry ent){
    int index = hash(ent.entry, arraySize);
    vector<Entry>* hashIndexVector = new vector<Entry>();

    try{
        *hashIndexVector = invertedIndex[index];
    } catch(...){}

    hashIndexVector->push_back(ent);
    invertedIndex[index] = *hashIndexVector;
}

template <typename J, typename T>
vector<tuple<T, int>> HashTableInvertedIndex<J,T>::get(J obj1){
    int index = hash(obj1, arraySize);

    vector<Entry<J,T>> hashIndexVector = invertedIndex[index];

    for (unsigned long k = 0;k < hashIndexVector.size();k++) {
        if(hashIndexVector.at(k).entry == obj1){
            return *(hashIndexVector.at(k).occurrences);
        }
    }

    vector<tuple<T, int>>* temp = new vector<tuple<T, int>>();
    return *temp;
}

template <typename J, typename T>
int HashTableInvertedIndex<J,T>::getNumWords(){
    return entries;
}

template <typename J, typename T>
int HashTableInvertedIndex<J,T>::getArraySize(){
    return arraySize;
}

template <typename J, typename T>
HashTableInvertedIndex<J,T>* HashTableInvertedIndex<J,T>::operator=(HashTableInvertedIndex hash){
    arraySize = hash.getArraySize();
    entries = hash.getNumWords();

    invertedIndex = new vector<Entry>[arraySize];

    for(int k = 0;k < arraySize;k++){
        //invertedIndex[k] = h
    }
}

template <typename J, typename T>
int HashTableInvertedIndex<J,T>::hash(J obj1, int size){
    return std::abs(static_cast<int>(std::hash<string>{}(obj1)) % size);
}

template <typename J, typename T>
void HashTableInvertedIndex<J,T>::reHash(){
    int newSize = arraySize * 2 + 1;
    vector<Entry>* temp = new vector<Entry>[newSize];

    for(int k = 0; k < arraySize;k++){
        for(unsigned long j = 0;j < invertedIndex[k].size();j++){
            int newIndex = hash(invertedIndex[k].at(j).entry, newSize);
            temp[newIndex].push_back(invertedIndex[k].at(j));
        }
    }

    delete[] invertedIndex;
    invertedIndex = temp;
    arraySize = newSize;
}

template class HashTableInvertedIndex<string, string>;

#endif // HASHTABLEINVERTEDINDEX_H
