#ifndef COURTCASE_H
#define COURTCASE_H

#include <string>
#include <vector>
#include <tuple>

using namespace std;

class CourtCase
{
public:
    CourtCase();
    CourtCase(unsigned int, unsigned int, unsigned int, string, string, string, string, string, vector<tuple<string, unsigned int>>*);
    unsigned int getCount(string);
    string toString();
private:
    unsigned int year;
    unsigned int volumeNum;
    unsigned int pageNum;
    string bookWithOpinion;
    string petitioner;
    string respondent;
    string majorityOpinionAuthor;
    string judgementDecision;
    vector<tuple<string, unsigned int>>* wordCountFrequency;
};

#endif // COURTCASE_H
