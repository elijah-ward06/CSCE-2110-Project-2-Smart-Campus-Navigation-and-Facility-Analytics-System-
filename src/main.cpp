
#include "util/hashtable.h"
#include <iostream>

int main(){

    Hashtable h;

    h.insert("H400");
    h.insert("G569");
    h.insert("Poison");
    h.remove("H400");

    cout << h.search("G569") << endl;

    return 0;
}