#include "hashtableinvertedindex.h"

template <typename J, typename T>
HashTableInvertedIndex<J,T>::HashTableInvertedIndex(){
    arraySize = 997;
    invertedIndex = new vector<Entry<J, T>>[arraySize];
    entries = 0;
}

template <typename J, typename T>
void HashTableInvertedIndex<J,T>::add(J obj1, T obj2){
    int index = abs(hash(obj1) % arraySize);
    vector<Entry<J,T>> hashIndexVector = invertedIndex[index];

    for(int k = 0;k < hashIndexVector.size();k++) {
        if(hashIndexVector.at(k).entry == obj1){
            hashIndexVector.at(k).occurrences->push_back(obj2);
            entries += 1;

            if(entries >= (arraySize * 0.75)){
                reHash();
            }

            return;
        }
    }
    hashIndexVector.push_back(Entry<J,T>(obj1, obj2));
}

template <typename J, typename T>
vector<T> HashTableInvertedIndex<J,T>::get(J obj1){
    int index = hash(obj1);

    vector<Entry<J,T>> hashIndexVector = invertedIndex[index];

    for (int k = 0;k < hashIndexVector.size();k++) {
        if(hashIndexVector.at(k).entry == obj1){
            return *(hashIndexVector.at(k).occurrences);
        }
    }
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
    vector<Entry<string, string>>* tempIndex = new vector<Entry<string, string>>[newSize];

    for (int k = 0;k < arraySize;k++) {
        if(invertedIndex[k].size() > 0){
            vector<Entry<string, string>>* vect = new vector<Entry<string, string>>;

            for(int j = 0; j < vect->size();j++){
                if(((invertedIndex[k]).at(j).occurrences)->size() > 0){
                    int index = hash((invertedIndex[k].at(j)).entry);
                    for(int j = 0; j < (tempIndex[index]).size();j++){
                        (tempIndex[index]).at(j).entry = (invertedIndex[k]).at(j).entry;
                    }

                }
            }
        }
    }

    invertedIndex = tempIndex;
    arraySize = newSize;
}

template class HashTableInvertedIndex<string, string>;
