/*Owner: Jack Rosenblatt
 *History:
    1. major change was a change in what we were storing for each court case in order for a better search functionality
    2. converted all int variables  to be unsigned int
*/

#ifndef COURTCASE_H
#define COURTCASE_H

//Include needed libraries for the court case class
#include <string>
#include <vector>
#include <tuple>

//allows for strings, vectors, and tuples to be used without typying std:: every time
using namespace std;

class CourtCase
{
public:
    CourtCase();
    CourtCase(unsigned int, unsigned int, unsigned int, string, string, string, string, string, vector<tuple<string, unsigned int>>*);
    CourtCase(const CourtCase&);
    unsigned int getCount(string);
    string toString();
    CourtCase* operator=(const CourtCase&);
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
