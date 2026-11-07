// General tree for the academic department hierarchy. Loads departments.txt,
// adds departments from the menu, searches by name, displays the indented hierarchy

#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <string>
#include <vector>

//One department.
struct DepartmentNode {
    std::string name;
    DepartmentNode* parent = nullptr;
    std::vector<DepartmentNode*> children;   //kept in insertion order

    explicit DepartmentNode(const std::string& n, DepartmentNode* p = nullptr)
        : name(n), parent(p) {}
};

//Accepted
struct TreeLoadSummary {
    int accepted = 0;
    int rejected = 0;
};

class DepartmentTree {
public:
    DepartmentTree() = default;
    ~DepartmentTree();

    //The tree owns its nodes, so copying is disabled.
    DepartmentTree(const DepartmentTree&) = delete;
    DepartmentTree& operator=(const DepartmentTree&) = delete;

    //TREE-2: load departments.txt. Prints warnings and a load summary, returns counts.
    TreeLoadSummary loadDepartments(const std::string& path);

    //TREE-3: add a department. If the tree is empty, parentName is ignored and the new
    //department becomes the root. Returns "" on success, otherwise the error reason.
    std::string addDepartment(const std::string& name, const std::string& parentName);

    //TREE-4: search ignoring case; prints name, parent, child count, depth.
    void searchDepartment(const std::string& name) const;

    //TREE-5: preorder, one per line, four spaces of indentation per depth.
    void displayHierarchy() const;

    //TREE-6: preorder sequence without indentation.
    void displayPreorder() const;

    //Preorder list of nodes (used by the displays above).
    std::vector<const DepartmentNode*> preorder() const;

    //Find a department ignoring case and outer whitespace. nullptr if missing.
    DepartmentNode* find(const std::string& name) const;

    //Edges from the root to node (root depth 0).
    static int depth(const DepartmentNode* node);

    bool empty() const { return root == nullptr; }
    int size() const { return count; }
    const DepartmentNode* getRoot() const { return root; }

private:
    DepartmentNode* root = nullptr;
    int count = 0;

    static DepartmentNode* findFrom(DepartmentNode* node, const std::string& name);
    static void preorderFrom(const DepartmentNode* node, std::vector<const DepartmentNode*>& out);
    static void destroy(DepartmentNode* node);
};

#endif
