#include "util/data.h"

#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>

using namespace std;

Data::Data(string override){
    std::stringstream buffer;

    ifstream data(override+"/buildings.txt");
    buffer << data.rdbuf();
    inputBuildings = buffer.str();
    buffer.str("");
    buffer.clear();
    data.close();

    data.open(override+"/connections.txt");
    buffer << data.rdbuf();
    inputConnections = buffer.str();
    buffer.str("");
    buffer.clear();
    data.close();

    data.open(override+"/departments.txt");
    buffer << data.rdbuf();
    inputDepartments = buffer.str();
    buffer.str("");
    buffer.clear();
    data.close();

    data.open(override+"/facilities.txt");
    buffer << data.rdbuf();
    inputFacilities = buffer.str();
    buffer.str("");
    buffer.clear();
    data.close();

    return;
}

Data::~Data(){
    return;
}