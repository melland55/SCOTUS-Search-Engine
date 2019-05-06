#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <json.hpp>
#include "jsonparser.h"
#include "porter2_stemmer.h"
#include "hashtableinvertedindex.h"

using namespace std;
using json = nlohmann::json;

JsonParser::JsonParser(){

}

int JsonParser::parseFiles(string dirName, Index& index){
    //Loads all stop word strings into a vector of strings
    vector<string> strList;
    ifstream stopWords("./stop_words");
    string temp;
    while(stopWords >> temp){
        strList.push_back(temp);
    }

    string extn = "json";
    DIR *dir;
    struct dirent *ent;

    //Checks if there are any Files in Directory dirName
    if((dir = opendir(dirName.c_str())) != NULL) {
        int sum = 0;

        //Loop through every File in Directory dirName and parses
        while((ent = readdir(dir)) != NULL && sum < 10){
            unsigned int len = strlen(ent->d_name);
            if(ent->d_type == DT_REG && len > extn.length() && strcmp(ent->d_name + len - extn.length(), extn.c_str()) == 0){
                sum++;
                ifstream infile;
                infile.open(dirName + "/" + ent->d_name);

                //Parses .json file into JSon obeject
                json file = json::parse(infile);
                string document;

                //Parses plain_text data if present otherwise Parse html
                if(file.at("plain_text") != ""){
                    document = file.at("plain_text");
                }else{
                    document = file.at("html");
                    regex reg("\\<[^\\>]*\\>");
                    //Removes all tags and nested tags using regex_replace
                    document = regex_replace(document, reg, "");
                }

                //Remove all non alpha and non space characters from string document
                document.erase(remove_if(document.begin(), document.end(), [](char c) {return (!isalpha(c) && !isspace(c)) ;} ), document.end());

                //Makes all characters in doucement lowercase
                transform(document.begin(), document.end(), document.begin(), ::tolower);

                //Creates stringstream for string document
                stringstream data(document);
                string str;

                //Loops through document separating all words and removing whitespace
                while(getline(data, str, ' ')){

                    //Adds all words from document to index
                    if(str != "\n" && str != ""){

                        //Only adds word if current word str is not a stop word
                        if(find(strList.begin(), strList.end(), str) == strList.end() && str.length() > 2){

                            //Removes \n from end of all words that contain it
                            if(str[str.length() - 1] == '\n'){
                                str.erase(str.length() - 1, str.length() - 1);
                            }

                            //Stems current words str
                            Porter2Stemmer::stem(str);

                            //Adds current word str to the index
                            index.add(str, (dirName + "/" + ent->d_name));
                        }
                    }
                }
            }
        }
        closedir(dir);
        return sum;
    }
    return 0;
}
