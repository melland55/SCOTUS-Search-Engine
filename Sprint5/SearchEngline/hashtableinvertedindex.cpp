#include "hashtableinvertedindex.h"

template <typename J, typename T>
HashTableInvertedIndex<J, T>::HashTableInvertedIndex(){
    arraySize = 997;
    invertedIndex = new tuple<J, vector<T>>[arraySize];

    for (int k = 0;k < arraySize;k++) {
        invertedIndex[k] = new tuple<J, vector<T>>;
    }

    entries = 0;
}

template <typename J, typename T>
void HashTableInvertedIndex<J, T>::add(J obj1, T obj2){
    int index = hash(obj1);
    vector<T> temp = invertedIndex[index];

    temp.push_back(obj2);

    if(temp.size() <= 1){
        entries += 1;

        if(entries >= (arraySize * 0.75)){
            reHash();
        }
    }

    invertedIndex[index] = temp
;}

template <typename J, typename T>
vector<T> HashTableInvertedIndex<J, T>::get(J obj1){
    int index = hash(obj1);
    return invertedIndex[index];
}

template <typename J, typename T>
int HashTableInvertedIndex<J, T>::hash(J obj1){
    return std::hash<J>(obj1);
}

template <typename J, typename T>
void HashTableInvertedIndex<J, T>::reHash(){
    int newSize = arraySize * 2 + 1;
    tuple<J, vector<T>> tempIndex[] = new tuple<J, vector<T>>[newSize];

    for (int k = 0;k < newSize;k++) {
        invertedIndex[k] = new tuple<J, vector<T>>;
    }

    for (int k = 0;k < arraySize;k++) {
        if((invertedIndex[k].second).size() > 0){

        }
    }
}
