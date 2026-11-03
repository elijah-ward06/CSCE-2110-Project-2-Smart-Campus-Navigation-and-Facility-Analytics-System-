#include "util/hashtable.h"

#include <string>

using namespace std;

Hashtable::Hashtable(){
    bucket.resize(bucketSize);
}

Hashtable::~Hashtable(){

}

string* Hashtable::search(string key){
   int loc = getHashKey(key);

    if (loc < 0 || loc >= bucket.size()){
        return nullptr;
    }

    vector<string>& selection = bucket[loc];

    for (string& i : selection) {
        if (i == key){
            return &i;
        }
    }

    return nullptr;
}

void Hashtable::remove(string key){
    int loc = getHashKey(key);

    if (loc < 0 || loc >= bucket.size()){
        return;
    }

    vector<string>& selection = bucket[loc];

    for (auto it = selection.begin(); it != selection.end(); it++) {
        if (*it == key){
            selection.erase(it);
            return;
        }
    }

}

void Hashtable::insert(string key){
    int loc = getHashKey(key);

    if (loc < 0 || loc >= bucket.size()){
        return;
    }

    //Prevent duplicates
    if (search(key) != nullptr){
        return;
    }

    bucket[loc].push_back(key);
}

int Hashtable::getHashKey(string key){
    char letter = '\0';
    string num;

    //Should be no larger or smaller than 4 in size
    if (key.size() != 4){
        return -1;
    }
    
    //Sort string into assets
    for (char l : key){
        int charnum = static_cast<int>(l);

        //Check if char is a capital letter
        if (charnum >= 'A' && charnum <= 'Z'){
            //This shouldn't be previously filled
            if (letter != '\0'){
                return -1;
            }
            letter = l;
        }
        //Check if char is a number
        else if (charnum >= '0' && charnum <= '9'){
            //Numbers should be no longer than 3
            if (num.length() >= 3){
                return -1;
            }

            num += l;
        }
        else{
            //Shouldn't be anything else, invalid key
            return -1;
        }
    }

    if (letter == '\0' || num.empty()){
    return -1;
    }

    int letterValue = letter - 'A';
    int numberValue = stoi(num);

    return ((letterValue * 1000) + numberValue) % bucketSize;

}