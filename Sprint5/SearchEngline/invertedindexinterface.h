/*Owner: Jack Rosenblatt
 *History:
    1.
    2. converted all int variables to be unsigned int
*/

#ifndef INVERTEDINDEXINTERFACE_H
#define INVERTEDINDEXINTERFACE_H

#include "index.h"

template <typename J>
class InvertedIndexInterface
{
public:
    virtual unsigned int getNumWords() = 0;
    virtual J* find(string) = 0;
protected:
    unsigned int entries;
};

#endif // INVERTEDINDEXINTERFACE_H
