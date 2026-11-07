// Purpose: Program entry point. Reads the optional data directory, loads the data files
// in the required order, and runs the repeating Milestone 1 menu.

#include "hashtable.h"
#include "campusgraph.h"
#include "stringutil.h"

#include <iostream>
#include <string>

using namespace std;

// Prompt for a start building (spaces allowed) and run BFS reachability.
void runBfs(const CampusGraph& graph) {
    cout << "Start building: ";
    string name;
    getline(cin, name);
    graph.bfsReachable(name);
}

int main(int argc, char* argv[]) {


    //After reading the optional data directory (argv[1], default "data"):
    CampusGraph graph;
    graph.loadBuildings(dataDir + "/buildings.txt");
    graph.loadConnections(dataDir + "/connections.txt");

    //Menu Loop
        //Goes inside menu loop vvv
        case 3: graph.displayGraph(); break;
        case 4: graph.displayCountsAndDegrees(); break;
        case 5: runBfs(graph); break;
        //Goes inside menu loop ^^^
}
