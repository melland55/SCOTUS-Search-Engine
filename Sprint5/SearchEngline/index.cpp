#include "index.h"

Index::Index()
{
    ifstream infile("./index");
    string temp;
    while(getline(infile, temp)){
        stringstream stream(temp);
        string word;
        vector<tuple<string, int>> locations;
        stream >> word;
        string fileName;
        int frequency;
        while(stream >> fileName >> frequency){
            locations.push_back(make_tuple(fileName, frequency));
        }
        index.push_back(make_tuple(word, locations));
    }
}

Index::~Index()
{
    ofstream outfile;
    outfile.open("./index", ofstream::out | ofstream::trunc);
    for(int i = 0; i < index.size(); i++){
        outfile << get<0>(index[i]) << " ";
        for(int j = 0; j < get<1>(index[i]).size(); j++){
            outfile << get<0>(get<1>(index[i])[j]) << " " << get<1>(get<1>(index[i])[j]) << " ";
        }
        outfile << endl;
    }
    outfile.close();
}

void Index::clear(){
    ofstream outfile;
    outfile.open("./index", ofstream::out | ofstream::trunc);
    outfile.close();
    index.clear();
}

void Index::add(string word, string fileName){
    for(int i = 0; i < index.size(); i++){
        if(get<0>(index[i]) == word){
            for(int j = 0; j < get<1>(index[i]).size(); j++){
                if(get<0>(get<1>(index[i])[j]) == fileName){
                    get<1>(get<1>(index[i])[j])++;
                    return;
                }
            }
            get<1>(index[i]).push_back(make_tuple(fileName, 1));
            return;
        }
    }
    vector<tuple<string, int>> temp;
    temp.push_back(make_tuple(fileName, 1));
    for(int i = 0; i < index.size(); i++){
        if(word < get<0>(index[i])){
            index.insert(index.begin() + i, make_tuple(word, temp));
            return;
        }
    }
    index.push_back(make_tuple(word, temp));
    return;
}

vector<tuple<string, vector<tuple<string, int>>>>* Index::getIndex(){
    return &index;
}
