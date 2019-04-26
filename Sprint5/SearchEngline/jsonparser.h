#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <string>
#include <index.h>


class JsonParser
{
public:
    JsonParser();
    static int parseFiles(string, Index&);
};


#endif // JSONPARSER_H
