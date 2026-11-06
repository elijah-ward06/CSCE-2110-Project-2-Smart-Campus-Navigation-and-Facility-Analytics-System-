#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include "Facility.h"

using namespace std;

class Hashtable{
    public:
    Hashtable();
    ~Hashtable();

    Facility* search(string key);
    bool insert(Facility key);
    bool remove(string key);

    private:

    vector<vector<Facility>> bucket;

    int getHashKey(string key);

    int bucketSize = 256;
};

#endif