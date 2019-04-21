#include "courtcase.h"

CourtCase::CourtCase(){
    year = volumeNum = pageNum = 0;
    bookWithOpinion = petitioner = respondent = majorityOpinionAuthor = "";
    wordCountFrequency = new vector<tuple<string, unsigned int>>;
}

CourtCase::CourtCase(unsigned int year, unsigned int volumeNum, unsigned int pageNum, string bookWithOpinion, string petitioner, string respondent, string majorityOpinionAuthor, string judgementDecision, vector<tuple<string, unsigned int>>* wordCountFrequency){
    this->year = year;
    this->volumeNum = volumeNum;
    this->pageNum = pageNum;
    this->bookWithOpinion = bookWithOpinion;
    this->petitioner = petitioner;
    this->respondent = respondent;
    this->majorityOpinionAuthor = majorityOpinionAuthor;
    this->judgementDecision = judgementDecision;
    *(this->wordCountFrequency) = *wordCountFrequency;
}

unsigned int CourtCase::getCount(string word){
    for(unsigned int k = 0; k < wordCountFrequency->size(); k++){
        if(get<0>(wordCountFrequency->at(k)) == word){
            return get<1>(this->wordCountFrequency->at(k));
        }
    }
    return 0;
}

string CourtCase::toString(){
    string str;

    str += petitioner + " v. " + respondent + "(" + to_string(year) + ")\n";
    str += "majority opinion was " +judgementDecision + " and was written by " + majorityOpinionAuthor;
    str += "\nopinion can be found in " + bookWithOpinion + " vol. " +to_string(volumeNum) + " on p." + to_string(pageNum);

    return str;
}
