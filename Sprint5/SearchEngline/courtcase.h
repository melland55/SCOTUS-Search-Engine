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
    CourtCase(int, int, int, string, string, string, string);
    int getCount(string);
    string toString();
private:
    int year;
    int volumeNum;
    int pageNum;
    string bookWithOpinion;
    string petitioner;
    string respondent;
    string majorityOpinionAuthor;
    string location;
    vector<tuple<string, int>> workCountFrequency;
};

#endif // COURTCASE_H
