// Implementation of DepartmentTree: departments.txt loading with validation,
// adding departments, case-insensitive search, indented hierarchy, and preorder traversal.

#include "departmenttree.h"
#include "stringutil.h"

#include <fstream>
#include <iostream>

using namespace std;
using namespace strutil;

//Release every node
DepartmentTree::~DepartmentTree() {
    destroy(root);
    root = nullptr;
}

//Recursively delete node and all of its descendants.
void DepartmentTree::destroy(DepartmentNode* node) {
    if (node == nullptr) return;
    for (DepartmentNode* child : node->children)
        destroy(child);
    delete node;
}

//Depth-first search below node for a name, ignoring case.
DepartmentNode* DepartmentTree::findFrom(DepartmentNode* node, const string& name) {
    if (node == nullptr) return nullptr;
    if (equalsIgnoreCase(node->name, name)) return node;
    for (DepartmentNode* child : node->children) {
        DepartmentNode* hit = findFrom(child, name);
        if (hit != nullptr) return hit;
    }
    return nullptr;
}

//Find a department by name (trimmed, case-insensitive).
DepartmentNode* DepartmentTree::find(const string& name) const {
    return findFrom(root, trim(name));
}

//Count parent links up to the root.
int DepartmentTree::depth(const DepartmentNode* node) {
    int d = 0;
    while (node != nullptr && node->parent != nullptr) {
        node = node->parent;
        d++;
    }
    return d;
}

//Add a department. Empty tree: becomes the root (parent ignored).
//Otherwise the parent must exist and the name must be new. Returns "" on success.
string DepartmentTree::addDepartment(const string& rawName, const string& rawParent) {
    string name = trim(rawName);
    if (name.empty())
        return "department name cannot be blank";

    if (root == nullptr) {
        root = new DepartmentNode(name);
        count = 1;
        return "";
    }

    string parentName = trim(rawParent);
    if (parentName.empty())
        return "parent name cannot be blank";

    DepartmentNode* parent = find(parentName);
    if (parent == nullptr)
        return "unknown parent '" + parentName + "'";
    if (find(name) != nullptr)
        return "duplicate department name '" + name + "'";

    parent->children.push_back(new DepartmentNode(name, parent));
    count++;
    return "";
}

//Load departments.txt. Check order: field count, empty fields, root/NONE rule,
//unknown parent, duplicate name.
TreeLoadSummary DepartmentTree::loadDepartments(const string& path) {
    TreeLoadSummary sum;
    ifstream in(path);
    if (!in) {
        cout << "ERROR: Could not open file " << path << " (treated as empty)." << endl;
        cout << path << ": 0 accepted, 0 rejected" << endl;
        return sum;
    }
    string line;
    int lineNo = 0;
    while (getline(in, line)) {
        lineNo++;
        if (isSkippableLine(line)) continue;
        vector<string> f = splitFields(line);
        string reason;
        if (f.size() != 2) {
            reason = "wrong field count (expected DepartmentName|ParentName)";
        } else if (f[0].empty() || f[1].empty()) {
            reason = "empty department or parent name";
        } else {
            bool parentIsNone = equalsIgnoreCase(f[1], "NONE");
            if (root == nullptr && !parentIsNone)
                reason = "first department must use NONE as parent (unknown parent '" + f[1] + "')";
            else if (root != nullptr && parentIsNone)
                reason = "root already exists; only the first department may use NONE";
            else if (root != nullptr && find(f[1]) == nullptr)
                reason = "unknown parent '" + f[1] + "'";
            else if (find(f[0]) != nullptr)
                reason = "duplicate department name '" + f[0] + "'";
            else
                reason = addDepartment(f[0], f[1]);   //"" on success
        }
        if (!reason.empty()) {
            cout << "WARNING: " << path << " line " << lineNo << ": " << reason << endl;
            sum.rejected++;
            continue;
        }
        sum.accepted++;
    }
    cout << path << ": " << sum.accepted << " accepted, " << sum.rejected << " rejected" << endl;
    return sum;
}

//Print name, parent (None for root), direct-child count, and depth.
void DepartmentTree::searchDepartment(const string& rawName) const {
    string name = trim(rawName);
    if (name.empty()) {
        cout << "Error: department name cannot be blank." << endl;
        return;
    }
    if (root == nullptr) {
        cout << "No departments are loaded." << endl;
        return;
    }
    const DepartmentNode* node = find(name);
    if (node == nullptr) {
        cout << "Department '" << name << "' not found." << endl;
        return;
    }
    cout << "Name: " << node->name << endl;
    cout << "Parent: " << (node->parent ? node->parent->name : "None") << endl;
    cout << "Children: " << node->children.size() << endl;
    cout << "Depth: " << depth(node) << endl;
}

//Recursive preorder: visit node, then each child in insertion order.
void DepartmentTree::preorderFrom(const DepartmentNode* node, vector<const DepartmentNode*>& out) {
    if (node == nullptr) return;
    out.push_back(node);
    for (const DepartmentNode* child : node->children)
        preorderFrom(child, out);
}

//Preorder list of all departments.
vector<const DepartmentNode*> DepartmentTree::preorder() const {
    vector<const DepartmentNode*> out;
    preorderFrom(root, out);
    return out;
}

//Indented hierarchy: four spaces per depth level.
void DepartmentTree::displayHierarchy() const {
    if (root == nullptr) {
        cout << "No departments are loaded." << endl;
        return;
    }
    cout << "Department hierarchy:" << endl;
    for (const DepartmentNode* node : preorder())
        cout << string(4 * depth(node), ' ') << node->name << endl;
}

//Preorder sequence with no indentation.
void DepartmentTree::displayPreorder() const {
    if (root == nullptr) {
        cout << "No departments are loaded." << endl;
        return;
    }
    cout << "Preorder traversal:" << endl;
    for (const DepartmentNode* node : preorder())
        cout << node->name << endl;
}
