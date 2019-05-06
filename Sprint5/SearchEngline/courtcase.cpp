#include "courtcase.h"

//Default CourtCase constructor sets all variables to empty or 0
CourtCase::CourtCase(){

}

//Overloaded CourtCase constructor sets all variables equal to the passed in parameters
CourtCase::CourtCase(string year, string id, string loc){
    this->id = id;
    this->year = year;
    location = loc;
}

//Copy CourtCase constructor sets all variables equal to the parameters of the passed in CourtCase
CourtCase::CourtCase(const CourtCase& courtCase){
    this->id = courtCase.id;
    this->year = courtCase.year;
    this->location = courtCase.location;
}

//Returns a string version of the courtCase class
void CourtCase::print(){

}

//Allows for one court case to be set to another courtCase
CourtCase* CourtCase::operator=(const CourtCase& courtCase){
    this->id = courtCase.id;
    this->year = courtCase.year;
    this->location = courtCase.location;
    return this;
}
