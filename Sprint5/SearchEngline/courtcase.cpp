#include "courtcase.h"

//Default CourtCase constructor sets all variables to empty or 0
CourtCase::CourtCase(){
    year = volumeNum = pageNum = 0;
    bookWithOpinion = petitioner = respondent = majorityOpinionAuthor = "";
    wordCountFrequency = new vector<tuple<string, unsigned int>>;
}

//Overloaded CourtCase constructor sets all variables equal to the passed in parameters
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

//Copy CourtCase constructor sets all variables equal to the parameters of the passed in CourtCase
CourtCase::CourtCase(const CourtCase& courtCase){
    this->year = courtCase.year;
    this->volumeNum = courtCase.volumeNum;
    this->pageNum = courtCase.pageNum;
    this->bookWithOpinion = courtCase.bookWithOpinion;
    this->petitioner = courtCase.petitioner;
    this->respondent = courtCase.respondent;
    this->majorityOpinionAuthor = courtCase.majorityOpinionAuthor;
    this->judgementDecision = courtCase.judgementDecision;
    *(this->wordCountFrequency) = *courtCase.wordCountFrequency;
}

//Returns the number of times a word resides in a courtCase
unsigned int CourtCase::getCount(string word){
    for(unsigned int k = 0; k < wordCountFrequency->size(); k++){
        if(get<0>(wordCountFrequency->at(k)) == word){
            return get<1>(this->wordCountFrequency->at(k));
        }
    }
    return 0;
}

//Returns a string version of the courtCase class
string CourtCase::toString(){
    string str;

    str += petitioner + " v. " + respondent + "(" + to_string(year) + ")\n";
    str += "majority opinion was " +judgementDecision + " and was written by " + majorityOpinionAuthor;
    str += "\nopinion can be found in " + bookWithOpinion + " vol. " +to_string(volumeNum) + " on p." + to_string(pageNum);

    return str;
}

//Allows for one court case to be set to another courtCase
CourtCase* CourtCase::operator=(const CourtCase& courtCase){
    this->year = courtCase.year;
    this->volumeNum = courtCase.volumeNum;
    this->pageNum = courtCase.pageNum;
    this->bookWithOpinion = courtCase.bookWithOpinion;
    this->petitioner = courtCase.petitioner;
    this->respondent = courtCase.respondent;
    this->majorityOpinionAuthor = courtCase.majorityOpinionAuthor;
    this->judgementDecision = courtCase.judgementDecision;
    *(this->wordCountFrequency) = *courtCase.wordCountFrequency;

    return this;
}
