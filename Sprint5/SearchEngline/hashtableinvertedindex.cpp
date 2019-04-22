#include "hashtableinvertedindex.h"

template <typename J, typename T>
HashTableInvertedIndex<J,T>::HashTableInvertedIndex(){
    arraySize = 997;
    invertedIndex = new tuple<J, vector<T>>[arraySize];

    for (int k = 0;k < arraySize;k++) {
        invertedIndex[k] = make_tuple("", *(new vector<T>));
    }

    entries = 0;
}

template <typename J, typename T>
void HashTableInvertedIndex<J,T>::add(J obj1, T obj2){
    int index = abs(hash(obj1) % arraySize);
    vector<T> temp = std::get<1>(invertedIndex[index]);

    temp.push_back(obj2);

    if(temp.size() <= 1){
        entries += 1;

        if(entries >= (arraySize * 0.75)){
            reHash();
        }
    }

    std::get<1>(invertedIndex[index]) = temp
;}

template <typename J, typename T>
vector<T> HashTableInvertedIndex<J,T>::get(J obj1){
    int index = hash(obj1);
    return std::get<1>(invertedIndex[index]);
}

template <typename J, typename T>
int HashTableInvertedIndex<J,T>::getNumWords(){
    return entries;
}

template <typename J, typename T>
int HashTableInvertedIndex<J,T>::hash(J obj1){
    return std::hash<string>{}(obj1);
}

template <typename J, typename T>
void HashTableInvertedIndex<J,T>::reHash(){
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

template class HashTableInvertedIndex<string, string>;
