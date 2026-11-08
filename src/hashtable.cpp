// Purpose: Implementation of Hashtable: Data Storage 
// Search, Remove and Insert
// Author: Elijah Ward, Member A
#include "hashtable.h"
#include "Facility.h"

#include <string>

using namespace std;

Hashtable::Hashtable(){
    bucket.resize(bucketSize);
}

Hashtable::~Hashtable(){

}

Facility* Hashtable::search(string key){
   int loc = getHashKey(key);

    if (loc < 0 || loc >= bucket.size()){
        return nullptr;
    }

    vector<Facility>& selection = bucket[loc];

    for (Facility& i : selection) {
        if (i.id == key){
            return &i;
        }
    }

    return nullptr;
}

bool Hashtable::remove(string key){
    int loc = getHashKey(key);

    if (loc < 0 || loc >= bucket.size()){
        return false;
    }

    vector<Facility>& selection = bucket[loc];

    for (int i = 0; i < selection.size(); ++i) {
       if (selection[i].id == key){
            selection.erase(selection.begin() + i);
            return true;
       }
    }

    

    return false;

}

bool Hashtable::insert(Facility key){
    int loc = getHashKey(key.id);

    if (loc < 0 || loc >= bucket.size()){
        return false;
    }

    //Prevent duplicates
    if (search(key.id) != nullptr){
        return false;
    }

    bucket[loc].push_back(key);
    return true;
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