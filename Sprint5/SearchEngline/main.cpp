#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <string.h>
#include <dirent.h>
#include <json.hpp>
#include <regex>
#include <vector>
#include "porter2_stemmer.h"

using namespace std;
using json = nlohmann::json;

void eraseAllSubStr(string&, const string&);
void parseFiles(string);

int main()
{
    parseFiles("/home/student/Downloads/scotus");
    cout << "Hello World!" << endl;
    return 0;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void parseFiles(string dirName){
    vector<string> strList;
    ifstream stopWords;

    stopWords.open("./stop_words");
    string temp;
    while(stopWords >> temp){
        strList.push_back(temp);
    }
    string extn = "json";
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(dirName.c_str())) != NULL) {
        int sum = 0;
        while((ent = readdir(dir)) != NULL && sum <= 5){
            int len = strlen(ent->d_name);
            if(ent->d_type == DT_REG && len > extn.length() && strcmp(ent->d_name + len - extn.length(), extn.c_str()) == 0){
                sum++;
                ifstream infile;
                infile.open(dirName + "/" + ent->d_name);
                json file = json::parse(infile);
                string document;
                if(file.at("plain_text") != ""){
                    document = file.at("plain_text");
                }else{
                    document = file.at("html");
                    regex reg("\\<[^\\>]*\\>");
                    document = regex_replace(document, reg, "");
                }
                document.erase(remove_if(document.begin(), document.end(), [](char c) {return (!isalpha(c) && !isspace(c)) ;} ), document.end());
                transform(document.begin(), document.end(), document.begin(), ::tolower);

                stringstream data(document);
                string str;
                while(getline(data, str, ' ')){
                    if(str != "\n" && str != ""){
                        if(find(strList.begin(), strList.end(), str) == strList.end() && str.length() > 2){
                            if(str[str.length() - 1] == '\n'){
                                str.erase(str.length() - 1, str.length() - 1);
                            }
                            Porter2Stemmer::stem(str);
                            //Add str and file driectory (dirName + "/" + ent->d_name) to hash table
                        }
                    }
                }
            }
        }
        closedir(dir);
    }
}

