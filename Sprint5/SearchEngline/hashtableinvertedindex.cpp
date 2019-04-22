#include "hashtableinvertedindex.h"

HashTableInvertedIndex::HashTableInvertedIndex(){
    arraySize = 997;
    invertedIndex = new tuple<string, vector<string>>[arraySize];

    for (int k = 0;k < arraySize;k++) {
        invertedIndex[k] = make_tuple("", *(new vector<string>));
    }

    entries = 0;
}

void HashTableInvertedIndex::add(string obj1, string obj2){
    int index = hash(obj1);
    vector<string> temp = std::get<1>(invertedIndex[index]);

    temp.push_back(obj2);

    if(temp.size() <= 1){
        entries += 1;

        if(entries >= (arraySize * 0.75)){
            reHash();
        }
    }

    std::get<1>(invertedIndex[index]) = temp
;}

vector<string> HashTableInvertedIndex::get(string obj1){
    int index = hash(obj1);
    return std::get<1>(invertedIndex[index]);
}

int HashTableInvertedIndex::hash(string obj1){
    return std::hash<string>{}(obj1);
}

void HashTableInvertedIndex::reHash(){
    int newSize = arraySize * 2 + 1;
    tuple<string, vector<string>> tempIndex[newSize];

    for (int k = 0;k < newSize;k++) {
        invertedIndex[k] = make_tuple("", *(new vector<string>));
    }

    for (int k = 0;k < arraySize;k++) {
        if((std::get<1>(invertedIndex[k])).size() > 0){
            int index = hash(std::get<0>(invertedIndex[k]));
            std::get<1>(tempIndex[index]) = std::get<1>(invertedIndex[k]);
        }
    }
    invertedIndex = new tuple<string, vector<string>>[newSize];
    for (int k = 0;k < newSize;k++) {
        invertedIndex[k] = tempIndex[k];
    }

    arraySize = newSize;
}
