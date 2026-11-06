#include "Facility.h"
#include "FacilityDatabase.h"

#include <string>
#include <vector>

using namespace std;

FacilityDatabase::FacilityDatabase(){

}

FacilityDatabase::~FacilityDatabase(){
    
}

void FacilityDatabase::addFacility(string id, string name,
string building, string category){
    Facility f;
    f.id = id;
    f.name = name;
    f.building = building;
    f.catagory = category;
}

Facility* FacilityDatabase::findById(string id){
    return table.search(id);
}

