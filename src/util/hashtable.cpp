#include "hashtable.h"

#include <string>

using namespace std;

Hashtable::Hashtable(string in){

}

Hashtable::~Hashtable(){

}

string Hashtable::search(){

}

string Hashtable::insert(){

}

int Hashtable::getHashKey(string key){
    char letter = '\0';
    string num;

    //Should be no larger or smaller than 4 in size
    if (key.size() != 4){
        return 0;
    }
    
    //Sort string into assets
    for (char l : key){
        int charnum = static_cast<int>(l);

        //Check if char is a capital letter
        if (charnum >= 'A' && charnum <= 'Z'){
            //This shouldn't be previously filled
            if (letter != '\0'){
                return -2;
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
            return 0;
        }
    }

    int letterValue = letter - 'A';
    int numberValue = stoi(num);

    return (letterValue * 1000) + numberValue;

}