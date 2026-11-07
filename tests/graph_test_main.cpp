// Purpose: Standalone driver to test CampusGraph by itself (not part of the main build).
// Author:  Bradey Jacobs, Member B
#include "campusgraph.h"
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char** argv) {
    string dir = (argc > 1) ? argv[1] : "data";
    CampusGraph g;
    g.loadBuildings(dir + "/buildings.txt");
    g.loadConnections(dir + "/connections.txt");
    string line;
    while (true) {
        cout << "\n1 graph | 2 counts | 3 BFS | 0 exit: ";
        if (!getline(cin, line)) break;
        if (line == "0") break;
        if (line == "1") g.displayGraph();
        else if (line == "2") g.displayCountsAndDegrees();
        else if (line == "3") { cout << "Start building: "; getline(cin, line); g.bfsReachable(line); }
        else cout << "Invalid option." << endl;
    }
}
