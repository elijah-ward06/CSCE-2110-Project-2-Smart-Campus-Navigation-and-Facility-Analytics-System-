// Purpose: Program entry point. Reads the optional data directory, loads the data files
// in the required order, and runs the repeating Milestone 1 menu.
// Author: Members A, B and C

#include "campusgraph.h"
#include "departmenttree.h"
#include "FacilityDatabase.h"
#include "stringutil.h"

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Prompt for a start building (spaces allowed) and run BFS reachability.
void runBfs(const CampusGraph& graph) {
    cout << "Start building: ";
    string name;
    getline(cin, name);
    graph.bfsReachable(name);
}

// Menu option 6: add a department. No parent prompt when the tree is empty.
void runAddDepartment(DepartmentTree& tree) {
    cout << "Department name: ";
    string name;
    getline(cin, name);
    if (strutil::trim(name).empty()) {
        cout << "Error: department name cannot be blank." << endl;
        return;
    }
    string parent;
    if (!tree.empty()) {
        cout << "Parent department: ";
        getline(cin, parent);
        if (strutil::trim(parent).empty()) {
            cout << "Error: parent name cannot be blank." << endl;
            return;
        }
    }
    string err = tree.addDepartment(name, parent);
    if (err.empty()) cout << "Department '" << strutil::trim(name) << "' added." << endl;
    else cout << "Error: " << err << ". Tree unchanged." << endl;
}

// Menu option 7: search a department (spaces allowed).
void runSearchDepartment(const DepartmentTree& tree) {
    cout << "Department name: ";
    string name;
    getline(cin, name);
    tree.searchDepartment(name);
}

//Menu option 2: Search for a facility.
void runSearchFacilities(FacilityDatabase& f){
    cout << "Facility ID: ";
    string id;
    getline(cin, id);
    Facility* search = f.findById(id);

    if (search != nullptr){
        cout << search->id << " | " << search->name << " | " << search->building << " | " << search->catagory << endl;
    }
}


int main(int argc, char* argv[]) {

    string dataDir;

    if (argc > 1){
        dataDir = argv[1];
    }
    else{
        dataDir = "data";
    }
    
    //After reading the optional data directory (argv[1], default "data"):
    CampusGraph graph;
    graph.loadBuildings(dataDir + "/buildings.txt");
    graph.loadConnections(dataDir + "/connections.txt");
    FacilityDatabase facilities(&graph);
    facilities.loadFacilities(dataDir + "/facilities.txt");
    DepartmentTree tree;
    tree.loadDepartments(dataDir + "/departments.txt");

    string selection = "-1";

    while(stoi(selection) != 0){

        cout << " Menu " << endl << "----------------------" << endl << 
        "1. View all facilities" << endl <<
        "2. Search facility by ID" << endl <<
        "3. View campus graph" << endl <<
        "4. Display graph counts and degrees" << endl <<
        "5. Find reachable buildings (BFS)" << endl <<
        "6. Add department" << endl <<
        "7. Search department" << endl <<
        "8. Display department hierarchy" << endl <<
        "9. Run preorder traversal" << endl <<
        "0. Exit" << endl << endl <<
        "Enter choice: ";

        if (!getline(cin, selection)) {
            break;
        }

        selection = strutil::trim(selection);

        if (selection.size() != 1){
            cout << "Invalid input: enter a number from 0 to 9." << endl;
            selection = "-1";
            continue;
        }
        else if (!isdigit(selection[0])){
            cout << "Invalid input: enter a number from 0 to 9." << endl;
            selection = "-1";
            continue;
        }

        //Menu Loop
        switch(stoi(selection)){
            //Goes inside menu loop vvv
            case 1: facilities.displayAll(); break;
            case 2: runSearchFacilities(facilities); break;
            case 3: graph.displayGraph(); break;
            case 4: graph.displayCountsAndDegrees(); break;
            case 5: runBfs(graph); break;
            case 6: runAddDepartment(tree); break;
            case 7: runSearchDepartment(tree); break;
            case 8: tree.displayHierarchy(); break;
            case 9: tree.displayPreorder(); break;
            case 0: break;
            default: cout << "Error: nonvalid selection"; break;
            //Goes inside menu loop ^^^
        }

    }

    cout << "Goodbye!" << endl;
    
}
