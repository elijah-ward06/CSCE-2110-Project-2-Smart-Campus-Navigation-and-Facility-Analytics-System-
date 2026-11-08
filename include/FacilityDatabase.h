#ifndef FACILITYDATABASE_H
#define FACILITYDATABASE_H

#include <string>
#include <vector>
#include "Facility.h"
#include "hashtable.h"

class FacilityDatabase {
public:

FacilityDatabase();
~FacilityDatabase();

void addFacility(string id, string name,
string building, string category);

Facility* findById(string id);

void displayAll();
void displayFacility();

int count() { return Facilities.size(); }

private:
    vector<Facility> Facilities;
    Hashtable table;

};

#endif