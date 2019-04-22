#include <fstream>
#include <iostream>
#include <string>
#include <userinterface.h>

using namespace std;


int main(int argc,char *argv[])
{
    HashTableInvertedIndex<string, string> hashTable;
    UserInterface interface;
    interface.run(hashTable);
    return 0;
}

