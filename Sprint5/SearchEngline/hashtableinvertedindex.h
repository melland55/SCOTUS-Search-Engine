#ifndef HASHTABLEINVERTEDINDEX_H
#define HASHTABLEINVERTEDINDEX_H

//Include needed libraries for the court case class
#include "index.h"
#include "invertedindexinterface.h"
#define MAX_CHAIN_LEN 5

using namespace std;

template <typename J>
class HashTableInvertedIndex : public InvertedIndexInterface<J>
{
public:
    HashTableInvertedIndex();
    HashTableInvertedIndex(int);
    HashTableInvertedIndex(vector<Entry>);
    J* find(string);
    int getNumWords();
private:
    unsigned int hash(string, int);
    void reHash();
    void add(J);
    int arraySize;
    vector<J>* invertedIndex;
};

//Default constructor that sets arraySize to 997
template <typename J>
HashTableInvertedIndex<J>::HashTableInvertedIndex(){
    arraySize = 997;
    invertedIndex = new vector<Entry>[arraySize];
    this->entries = 0;
}

//Overloaded constructor that sets a starting size for the hashtable
template <typename J>
HashTableInvertedIndex<J>::HashTableInvertedIndex(int size){
    arraySize = size;
    invertedIndex = new vector<Entry>[arraySize];
    this->entries = 0;
}

//Overloaded constructor that creates a hashtable out of a vector of entries
template <typename J>
HashTableInvertedIndex<J>::HashTableInvertedIndex(vector<Entry> vect){
    this->entries = static_cast<int>(vect.size());
    arraySize = static_cast<int>(this->entries * 0.8);
    invertedIndex = new vector<Entry>[arraySize];

    for(unsigned long k = 0;k < vect.size();k++) {
        this->add(vect.at(k));
    }
}

//adds an Entry to the HashTable
template <typename J>
void HashTableInvertedIndex<J>::add(J ent){
    int index = hash(ent.entry, arraySize);
    vector<Entry> hashIndexVector;

    //grabs the vector already there if it exists
    try{
        hashIndexVector = invertedIndex[index];
    } catch(...){}

    hashIndexVector.push_back(ent);
    invertedIndex[index] = hashIndexVector;

    //checks if hashtable needs to be rehashed
    if((hashIndexVector.size() > MAX_CHAIN_LEN) || this->entries > static_cast<int>(arraySize * 0.75)){
        reHash();
    }
}

template <typename J>
J* HashTableInvertedIndex<J>::find(string obj1){
    int index = hash(obj1, arraySize);

    vector<Entry> hashIndexVector = invertedIndex[index];

    for (unsigned long k = 0;k < hashIndexVector.size();k++) {
        if(hashIndexVector.at(k).entry == obj1){
            return hashIndexVector.at(k);
        }
    }

    J* temp = new J();
    return temp;
}

template <typename J>
int HashTableInvertedIndex<J>::getNumWords(){
    return this->entries;
}

//returns a positive int of the index from the hashed word modulused by size of HashTable
template <typename J>
unsigned int HashTableInvertedIndex<J>::hash(string obj1, int size){
    return std::abs(static_cast<int>(std::hash<string>{}(obj1)) % size);
}

//Rehashes all entries now modulused on the new HashTable size
template <typename J>
void HashTableInvertedIndex<J>::reHash(){
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

#endif // HASHTABLEINVERTEDINDEX_H
