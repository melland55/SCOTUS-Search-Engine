#include <fstream>
#include <iostream>
#include <string>
#include <userinterface.h>

#include <regex>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <json.hpp>
#include <stdexcept>
#include <cstring>
#include "jsonparser.h"
#include "porter2_stemmer.h"
#include "hashtableinvertedindex.h"
#include "index.h"

using namespace std;

using json = nlohmann::json;

int main(int argc,char *argv[])
{
    UserInterface interface;
    interface.run();
    return 0;
}

