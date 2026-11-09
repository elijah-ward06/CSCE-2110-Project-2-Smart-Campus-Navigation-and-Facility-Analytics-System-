#ifndef FACILITYDATABASE_H
#define FACILITYDATABASE_H

#include <string>
#include <vector>
#include "Facility.h"
#include "hashtable.h"
#include "campusgraph.h"

struct FacilityLoadSummary {
    int accepted = 0;
    int rejected = 0;
};

class FacilityDatabase {
public:

FacilityDatabase(CampusGraph* g);
~FacilityDatabase();

FacilityLoadSummary loadFacilities(const string& path);

Facility* findById(string id);

void displayAll();

int count() { return Facilities.size(); }

private:

    void addFacility(string id, string name,
    string building, string category);

    vector<Facility> Facilities;
    Hashtable table;

    CampusGraph* graph;

};

#endif