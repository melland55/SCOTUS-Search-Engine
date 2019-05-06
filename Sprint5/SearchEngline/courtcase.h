/*Owner: Jack Rosenblatt
 *History:
    1. major change was a change in what we were storing for each court case in order for a better search functionality
    2. converted all int variables to be unsigned int
    3. changed which variables are stored due to difficulty parsing data from html for specific data
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
    CourtCase(string, string, string);
    CourtCase(const CourtCase&);
    void print();
    CourtCase* operator=(const CourtCase&);
private:
    string year;
    string id;
    string location;
};

#endif // COURTCASE_H
