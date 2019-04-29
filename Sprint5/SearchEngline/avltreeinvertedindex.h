#ifndef AVLTREEINVERTEDINDEX_H
#define AVLTREEINVERTEDINDEX_H

#include <string>
#include <vector>
#include "invertedindexinterface.h"

using namespace std;

template<class T>
struct Node{
    Node* parent;
    Node* left;
    Node* right;
    T data;
};

template<class T>
class AVLTreeInvertedIndex : public InvertedIndexInterface<T>
{
public:
    AVLTreeInvertedIndex();
    Node<T>* makeNode(vector<T>&);
    void add(vector<T>&);
    T* find(string);
    int getBalance(Node<T>*);
private:
    Node<T>* head;
};

template<class T>
AVLTreeInvertedIndex<T>::AVLTreeInvertedIndex(){
    head = nullptr;
}

template<class T>
Node<T>* AVLTreeInvertedIndex<T>::makeNode(vector<T>& entries){
    Node<T>* node = new Node<T>();
    if(entries.size()/2 == 0){
        node->data = entries[0];
        return node;
    }
    node->data = entries[entries.size() / 2];
    if(entries.size() == 2){
        node->left = new Node<T>();
        node->left->data == entries[0];
        return node;
    }
    vector<T> leftV(entries.begin(), entries.size() / 2);
    vector<T> rightV(entries.size() / 2, entries.end());
    node->left = makeNode(leftV);
    node->right = makeNode(rightV);
}

template<class T>
void AVLTreeInvertedIndex<T>::add(vector<T>& entries){
    head = makeNode(entries);
}


template<class T>
T* AVLTreeInvertedIndex<T>::find(string item){
    Node<T>* cur = head;
    while(cur->data != item){
        if(item > cur->data && cur->right != nullptr){
            cur = cur->right;
        }else if(item < cur->data && cur->left != nullptr){
            cur = cur->left;
        }else{
            return nullptr;
        }
    }
    return &cur->data;
}

#endif // AVLTREEINVERTEDINDEX_H
