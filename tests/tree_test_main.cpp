// Standalone driver to test DepartmentTree by itself
#include "departmenttree.h"
#include "stringutil.h"
#include <iostream>
#include <string>
using namespace std;

//Menu option 6: add a department. No parent prompt when the tree is empty.
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

//Menu option 7: search a department (spaces allowed).
void runSearchDepartment(const DepartmentTree& tree) {
    cout << "Department name: ";
    string name;
    getline(cin, name);
    tree.searchDepartment(name);
}

int main(int argc, char** argv) {
    string dir = (argc > 1) ? argv[1] : "data";
    DepartmentTree t;
    t.loadDepartments(dir + "/departments.txt");
    string line;
    while (true) {
        cout << "\n6 add | 7 search | 8 hierarchy | 9 preorder | 0 exit: ";
        if (!getline(cin, line)) break;
        line = strutil::trim(line);
        if (line == "0") break;
        if (line == "6") runAddDepartment(t);
        else if (line == "7") runSearchDepartment(t);
        else if (line == "8") t.displayHierarchy();
        else if (line == "9") t.displayPreorder();
        else cout << "Invalid option." << endl;
    }
}
