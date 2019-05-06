#ifndef AVLTREEINVERTEDINDEX_H
#define AVLTREEINVERTEDINDEX_H

#include <string>
#include <vector>
#include "invertedindexinterface.h"

using namespace std;

template<class T>
struct Node{
    Node* left = nullptr;
    Node* right = nullptr;
    T data;
    ~Node(){
        if(left) delete left;
        if(right) delete right;
    };
};

template<class T>
class AVLTreeInvertedIndex
{
public:
    AVLTreeInvertedIndex();
    ~AVLTreeInvertedIndex();
    AVLTreeInvertedIndex(vector<T>&);
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
AVLTreeInvertedIndex<T>::~AVLTreeInvertedIndex(){
    delete head;
}

template<class T>
AVLTreeInvertedIndex<T>::AVLTreeInvertedIndex(vector<T>& vec){
    head = makeNode(vec);
}

template<class T>
Node<T>* AVLTreeInvertedIndex<T>::makeNode(vector<T>& entries){
    Node<T>* node = new Node<T>();
    if(entries.size()/2 == 0){
        node->data = entries[0];
        return node;
    }else if(entries.size() == 2){
        node->data = entries[1];
        node->left = new Node<T>();
        node->left->data = entries[0];
        return node;
    }
    node->data = entries[entries.size() / 2];
    if(entries.size() % 2 == 0){
        vector<T> leftV(entries.begin(), entries.begin() + (entries.size() / 2) - 1);
        vector<T> rightV(entries.begin() + entries.size() / 2, entries.end());
        node->left = makeNode(leftV);
        node->right = makeNode(rightV);
    }else{
        vector<T> leftV(entries.begin(), entries.begin() + (entries.size() / 2));
        vector<T> rightV(entries.begin() + entries.size() / 2, entries.end());
        node->left = makeNode(leftV);
        node->right = makeNode(rightV);
    }
    return node;
}

template<class T>
void AVLTreeInvertedIndex<T>::add(vector<T>& entries){
    head = makeNode(entries);
}


template<class T>
T* AVLTreeInvertedIndex<T>::find(string item){
    Node<T>* cur = head;
    while(!(cur->data == item)){
        if(cur->data > item && !(cur->right == nullptr)){
            cur = cur->left;
        }else if(cur->data < item && cur->left != nullptr){
            cur = cur->right;
        }else{
            return nullptr;
        }
    }
    return &cur->data;
}

#endif // AVLTREEINVERTEDINDEX_H
