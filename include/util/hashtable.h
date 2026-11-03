#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

using namespace std;

class Hashtable{
    public:
    Hashtable();
    ~Hashtable();

    string* search(string key);
    void insert(string key);
    void remove(string key);

    private:

    vector<vector<string>> bucket;

    int getHashKey(string key);

    int bucketSize = 256;
};

#endif