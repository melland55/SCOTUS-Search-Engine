#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <string>
#include <hashtableinvertedindex.h>


class JsonParser
{
public:
    JsonParser();
    int parseFiles(string, HashTableInvertedIndex<string, string>&);
};


#endif // JSONPARSER_H
