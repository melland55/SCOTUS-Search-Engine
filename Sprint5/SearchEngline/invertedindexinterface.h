/*Owner: Jack Rosenblatt
 *History:
    1. moved entries to be a protected variable for use by child classes
    2. converted all int variables to be unsigned int
    3. removed constructors due to being an abstract class
*/

#ifndef INVERTEDINDEXINTERFACE_H
#define INVERTEDINDEXINTERFACE_H

#include "index.h"

template <typename J>
class InvertedIndexInterface
{
public:
    //methods to be overwritten in child classes
    virtual J* find(string) = 0;
protected:
    unsigned int entries;
};

#endif // INVERTEDINDEXINTERFACE_H
