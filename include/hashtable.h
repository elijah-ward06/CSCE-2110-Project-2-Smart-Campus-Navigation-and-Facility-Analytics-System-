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

    //HASH-1
    Facility* search(string key);
    bool insert(Facility key);
    bool remove(string key);

    int getCapacity() { return bucketSize; }
    int getCollisions() { return collisions; }
    int getEntries() { return entries; }

    private:

    //HASH-3 separate chaining
    vector<vector<Facility>> bucket;

    //HASH-2
    int getHashKey(string key);

    int entries = 0;

    int collisions = 0;

    int bucketSize = 256;
};

#endif