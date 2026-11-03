#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

using namespace std;

class Hashtable{
    public:
    Hashtable(string in);
    ~Hashtable();

    string search();
    string insert();

    private:

    vector<vector<string>> bucket;

    int getHashKey(string key);


};

#endif