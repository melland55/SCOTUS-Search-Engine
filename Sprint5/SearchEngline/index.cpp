#include "index.h"

//Opens the file and writes all persistant data to index
Index::Index()
{
    //Opens the Persistant Index File
    ifstream infile("./index");
    string temp;

    //Loops through every line in file
    while(getline(infile, temp)){
        //Creates StringStream for each line
        stringstream stream(temp);
        Entry entry;
        string fileName;
        int frequency;

        //Puts unique word into entry
        stream >> entry.entry;
        //Loops through every file containing word and its frequency and stores it into entry
        while(stream >> fileName >> frequency){
            entry.occurrences.push_back(make_tuple(fileName, frequency));
        }
        //Adds entry to index
        index.push_back(entry);
    }
}

//Writes all data from index to persistant index
Index::~Index()
{
    //Opens the persistant file and deletes all data
    ofstream outfile;
    outfile.open("./index", ofstream::out | ofstream::trunc);

    //Loops through index writing all entries onto the persistant file
    for(unsigned int i = 0; i < index.size(); i++){
        outfile << index[i].entry << " ";
        for(unsigned int j = 0; j < index[i].occurrences.size(); j++){
            outfile << get<0>(index[i].occurrences[j]) << " " << get<1>(index[i].occurrences[j]) << " ";
        }
        outfile << endl;
    }
    outfile.close();
}

//Clears  the index and persistant index
void Index::clear(){
    //Opens the persistant file and deletes all data
    ofstream outfile;
    outfile.open("./index", ofstream::out | ofstream::trunc);
    outfile.close();
    //Clears all entries inside of index
    index.clear();
}

//Adds an entry to index
void Index::add(string word, string fileName){
    //Loops through every instance inside of index
    for(unsigned int i = 0; i < index.size(); i++){
        //Checks if current entry inside index has the same key word
        if(index[i].entry == word){
            //Checks if fileName is already stored in occurences
            for(unsigned int j = 0; j < index[i].occurrences.size(); j++){
                //If fileName is in occurences, increase its frequency
                if(get<0>(index[i].occurrences[j]) == fileName){
                    get<1>(index[i].occurrences[j])++;
                    return;
                }
            }
            //If fileName is not in occurences, add new occurence
            index[i].occurrences.push_back(make_tuple(fileName, 1));
            return;
        }
    }
    //If Word is not inside of index, create a new entry
    Entry temp;
    temp.entry = word;
    temp.occurrences.push_back(make_tuple(fileName, 1));

    //Inserts the entry in alphabetiical order of words
    for(unsigned int i = 0; i < index.size(); i++){
        if(word < index[i].entry){
            index.insert(index.begin() + i, temp);
            return;
        }
    }
    index.push_back(temp);
    return;
}

//Returns the index
vector<Entry>* Index::getIndex(){
    return &index;
}
