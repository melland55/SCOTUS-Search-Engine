#ifndef INVERTEDINDEXINTERFACE_H
#define INVERTEDINDEXINTERFACE_H

#include "index.h"

template <typename J>
class InvertedIndexInterface
{
public:
    InvertedIndexInterface();
    InvertedIndexInterface(vector<J>);
    int getNumWords();
    J* find(string);
protected:
    int entries;
};

#endif // INVERTEDINDEXINTERFACE_H
