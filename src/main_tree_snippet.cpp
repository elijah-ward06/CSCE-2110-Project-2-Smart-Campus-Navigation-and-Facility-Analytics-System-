
#include "departmenttree.h"

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

//  In main(), load LAST.
    DepartmentTree tree;
    tree.loadDepartments(dataDir + "/departments.txt");

// ---- Inside the menu switch ----
        case 6: runAddDepartment(tree); break;
        case 7: runSearchDepartment(tree); break;
        case 8: tree.displayHierarchy(); break;
        case 9: tree.displayPreorder(); break;

// These helpers read with getline.
