#include "hashtableinvertedindex.h"

template <typename J, typename T>
HashTableInvertedIndex<J, T>::HashTableInvertedIndex(){

}

template <typename J, typename T>
void HashTableInvertedIndex<J, T>::add(J obj1, T obj2){
    int index = hash(obj1);


}

template <typename J, typename T>
vector<T> HashTableInvertedIndex<J, T>::get(J obj1){
    int index = hash(obj1);
    return invertedIndex[index];
}

template <typename J, typename T>
int HashTableInvertedIndex<J, T>::hash(J){

}
