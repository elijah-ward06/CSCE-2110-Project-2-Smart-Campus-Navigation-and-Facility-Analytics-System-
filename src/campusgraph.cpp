// Purpose: Implementation of CampusGraph: file loading with validation, graph display,
// degree statistics, and BFS reachability.
// Author: Bradey Jacobs, Member B
#include "campusgraph.h"
#include "stringutil.h"

#include <fstream>
#include <iostream>
#include <queue>

using namespace std;
using namespace strutil;

//Find a building by name. Returns -1 if unknown.
int CampusGraph::findBuilding(const string& name) const {
    string t = trim(name);
    for (size_t i = 0; i < names.size(); i++)
        if (equalsIgnoreCase(names[i], t)) return static_cast<int>(i);
    return -1;
}

//True if an edge between a and b already exists.
bool CampusGraph::hasEdge(int a, int b) const {
    for (int n : adj[a])
        if (n == b) return true;
    return false;
}

//Load buildings.txt; reject malformed and duplicate names.
GraphLoadSummary CampusGraph::loadBuildings(const string& path) {
    GraphLoadSummary sum;
    ifstream in(path);
    if (!in) {
        cout << "ERROR: Could not open file " << path << " (treated as empty)." << endl;
        return sum;
    }
    string line;
    int lineNo = 0;
    while (getline(in, line)) {
        lineNo++;
        if (isSkippableLine(line)) continue;
        string name = trim(line);
        string reason;
        if (name.find('|') != string::npos)
            reason = "wrong field count (expected one building name)";
        else if (findBuilding(name) != -1)
            reason = "duplicate building name '" + name + "'";
 
        if (!reason.empty()) {
            cout << "WARNING: " << path << " line " << lineNo << ": " << reason << endl;
            sum.rejected++;
            continue;
        }
        names.push_back(name);
        adj.push_back(vector<int>());
        sum.accepted++;
    }
    cout << path << ": " << sum.accepted << " accepted, " << sum.rejected << " rejected" << endl;
    return sum;
}

//Load connections.txt; check order: field count, empty, unknown, self, duplicate.
GraphLoadSummary CampusGraph::loadConnections(const string& path) {
    GraphLoadSummary sum;
    ifstream in(path);
    if (!in) {
        cout << "ERROR: Could not open file " << path << " (treated as empty)." << endl;
        return sum;
    }
    string line;
    int lineNo = 0;
    while (getline(in, line)) {
        lineNo++;
        if (isSkippableLine(line)) continue;
        vector<string> f = splitFields(line);
        string reason;
        int a = -1, b = -1;
        if (f.size() != 2) {
            reason = "wrong field count (expected BuildingA|BuildingB)";
        } else if (f[0].empty() || f[1].empty()) {
            reason = "empty building name";
        } else {
            a = findBuilding(f[0]);
            b = findBuilding(f[1]);
            if (a == -1)
                reason = "unknown building '" + f[0] + "'";
            else if (b == -1)
                reason = "unknown building '" + f[1] + "'";
            else if (a == b)
                reason = "self-connection for '" + names[a] + "'";
            else if (hasEdge(a, b))
                reason = "duplicate connection " + names[a] + "|" + names[b];
        }
        if (!reason.empty()) {
            cout << "WARNING: " << path << " line " << lineNo << ": " << reason << endl;
            sum.rejected++;
            continue;
        }
        adj[a].push_back(b);
        adj[b].push_back(a);
        edgeCount++;
        sum.accepted++;
    }
    cout << path << ": " << sum.accepted << " accepted, " << sum.rejected << " rejected" << endl;
    return sum;
}

//Show every building with its neighbors.
void CampusGraph::displayGraph() const {
    if (names.empty()) {
        cout << "No buildings are loaded." << endl;
        return;
    }
    cout << "Campus graph:" << endl;
    for (size_t i = 0; i < names.size(); i++) {
        cout << names[i] << ": ";
        if (adj[i].empty()) {
            cout << "(no connections)";
        } else {
            for (size_t j = 0; j < adj[i].size(); j++) {
                if (j > 0) cout << ", ";
                cout << names[adj[i][j]];
            }
        }
        cout << endl;
    }
}

//Show totals and the degree of each building.
void CampusGraph::displayCountsAndDegrees() const {
    if (names.empty()) {
        cout << "No buildings are loaded." << endl;
        cout << "Total buildings: 0" << endl;
        cout << "Total connections: 0" << endl;
        return;
    }
    cout << "Total buildings: " << names.size() << endl;
    cout << "Total connections: " << edgeCount << endl;
    cout << "Degrees:" << endl;
    for (size_t i = 0; i < names.size(); i++)
        cout << "  " << names[i] << ": " << adj[i].size() << endl;
}

//BFS from startName using a queue; visited is marked when a building is enqueued.
void CampusGraph::bfsReachable(const string& startName) const {
    string t = trim(startName);
    if (t.empty()) {
        cout << "Error: building name cannot be blank." << endl;
        return;
    }
    int start = findBuilding(t);
    if (start == -1) {
        cout << "Error: unknown building '" << t << "'." << endl;
        return;
    }

    vector<bool> visited(names.size(), false);
    vector<int> dist(names.size(), 0);
    vector<int> order;
    queue<int> q;

    visited[start] = true;
    dist[start] = 0;
    q.push(start);
 
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
 
    cout << "Reachable buildings from " << names[start] << " (BFS order):" << endl;
    for (int idx : order)
        cout << "  " << names[idx] << " (distance " << dist[idx] << ")" << endl;
    cout << "Reachable: " << order.size() << " of " << names.size() << " buildings" << endl;
}
