#ifndef DATA_UTILS_H
#define DATA_UTILS_H

#include <string>

using namespace std;

class Data{
    public:

    Data(string override = "data");
    ~Data();

    private:

    string datalocation;

    string inputBuildings;
    string inputConnections;
    string inputDepartments;
    string inputFacilities;
};

#endif