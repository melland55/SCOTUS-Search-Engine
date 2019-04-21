#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <dirent.h>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

void parseFiles(string);

int main()
{
    parseFiles("/home/student/Downloads/scotus");
    cout << "Hello World!" << endl;
    return 0;
}

void parseFiles(string dirName){
    string extn = "json";
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(dirName.c_str())) != NULL) {
        int sum = 0;
        while((ent = readdir(dir)) != NULL && sum <= 10){
            sum++;
            int len = strlen(ent->d_name);
            if(ent->d_type == DT_REG && len > extn.length() && strcmp(ent->d_name + len - extn.length(), extn.c_str()) == 0){
                ifstream infile;
                infile.open(dirName + "/" + ent->d_name);
                json file = json::parse(infile);
                if(file.at("plain_text").size() <= 10){

                }else{

                }
            }
        }
        closedir(dir);
    }
}
