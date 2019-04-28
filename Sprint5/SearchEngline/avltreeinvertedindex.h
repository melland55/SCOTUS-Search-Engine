#ifndef AVLTREEINVERTEDINDEX_H
#define AVLTREEINVERTEDINDEX_H

#include <string>
#include <vector>

using namespace std;

template<class T>
struct node{
    node* parent;
    node* left;
    node* right;
    T data;
};

template<class T>
class AVLTreeInvertedIndex
{
public:
    AVLTreeInvertedIndex();
    void add(vector<T>);
    node<T>* find(T);
    int getBalance(node<T>*);
private:
    node<T>* head;
};

template<class T>
AVLTreeInvertedIndex::AVLTreeInvertedIndex(){
    head = nullptr;
}

template<class T>
node<T>* AVLTreeInvertedIndex::makeNode(vector<T>& entries){

}

template<class T>
void AVLTreeInvertedIndex::add(vector<T>& entries){
    head = makeNode(entries);
}


template<class T>
node<T>* AVLTreeInvertedIndex::find(T){
    node<T>* cur = head;
    while(cur->data != T){
        if(T > cur->data && cur->right != nullptr){
            cur = cur->right;
        }else if(T < cur->data && cur->left != nullptr){
            cur = cur->left;
        }else{
            return nullptr;
        }
    }
    return cur;
}

#endif // AVLTREEINVERTEDINDEX_H
