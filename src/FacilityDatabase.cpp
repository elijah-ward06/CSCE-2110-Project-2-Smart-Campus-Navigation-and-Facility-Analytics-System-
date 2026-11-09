// Purpose: Implementation of FacilityDatabase: Storage of data
// 
// Author: Elijah Ward, Member A
#include "Facility.h"
#include "FacilityDatabase.h"
#include "stringutil.h"
#include "campusgraph.h"

#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <fstream>

using namespace std;
using namespace strutil;

FacilityDatabase::FacilityDatabase(CampusGraph* g){
    graph = g;
}

FacilityDatabase::~FacilityDatabase(){
    
}

//Load facilities.txt; check order: field count, empty, ID Format, unknown, duplicate.
FacilityLoadSummary FacilityDatabase::loadFacilities(const string& path) {
    ifstream in(path);
    FacilityLoadSummary sum;

    if (!in) {
        cout << "ERROR: Could not open file " << path << " (treated as empty)." << endl;
        cout << path << ": 0 accepted, 0 rejected" << endl;
        return sum;
    }

    string line;
    int lineNo = 0;
    while (getline(in, line)) {
        lineNo++;
        if (isSkippableLine(line)) continue;
        vector<string> f = splitFields(line);
        string reason;
        int bIndex = -1;

        if (!f[0].empty()){
            f[0][0] = toupper(f[0][0]);
        }

        //Check input format
        if (f.size() != 4){
            reason = "wrong field count (expected FacilityID|FacilityName|BuildingName|Category)";
        }
        //Check if all inputs are full
        else if (f[0].empty() || f[1].empty() || f[2].empty() || f[3].empty()){
            reason = "empty field on line.";
        }
        else if (!isValidID(f[0])){
            reason = "invalid ID, must be F followed by three digits";
        }
        else if((bIndex = graph->findBuilding(f[2])) == -1){
            reason = "Building is unknown.";
        }
        else if(table.search(f[0])){
            reason = "Duplicate ID";
        }
        if (!reason.empty()) {
            cout << "WARNING: " << path << " line " << lineNo << ": " << reason << endl;
            sum.rejected++;
            continue;
        }

        Facility fac;

        fac.id = f[0];
        fac.name = f[1];
        fac.building = graph->buildingName(bIndex);
        fac.catagory = f[3];

        if (table.insert(fac)){
            Facilities.push_back(fac);
            sum.accepted++;
        }
        else{
            sum.rejected++;
            cout << "WARNING: " << path << " line " << lineNo << ": " << "Could not insert into hash table." << endl;
        }
        
    }

    cout << path << ": " << sum.accepted << " accepted, " << sum.rejected << " rejected" 
    << " ( Hash Capacity: " << table.getCapacity() << ", Entries: " << table.getEntries() << ", Collisions: " << table.getCollisions() << " )" << endl;
    return sum;

}

Facility* FacilityDatabase::findById(string id){

    id = trim(id);

    if(id.empty()){
        cout << "Error: facility ID cannot be blank." << endl;
        return nullptr;
    }

    id[0] = toupper(id[0]);

    if (!isValidID(id)){
        cout << "invalid ID, must be F followed by three digits." << endl;
        return nullptr;
    }

    Facility* search = table.search(id);

    if (search == nullptr){
        cout << "Not found: no facility with ID " << id << "." << endl;
        return nullptr;
    }

    return search;
}

//NFR-3, Print every facility in file order with the total, or a message if none are loaded.
void FacilityDatabase::displayAll(){

    if (Facilities.empty()){
        cout << "No facilities are loaded." << endl;
        return;
    }

    cout << "Facilities: " << endl;

    for (const auto& fac : Facilities) {
        cout << fac.id << " | " << fac.name << " | " << fac.building << " | " << fac.catagory << endl;
    }

    cout << "Total Facilities: " << Facilities.size() << endl;


}
