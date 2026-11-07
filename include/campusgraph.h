// Purpose: Undirected, unweighted campus graph (adjacency list). Loads buildings.txt
// and connections.txt, displays the graph and statistics, and runs BFS reachability.
// Author:  Bradey Jacobs, Member B
#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>

//Accepted / rejected record counts reported after each file load.
struct GraphLoadSummary {
    int accepted = 0;
    int rejected = 0;
};

class CampusGraph {
public:
    //Load buildings.txt. Prints warnings and returns counts.
    GraphLoadSummary loadBuildings(const std::string& path);
 
    //Load connections.txt. Buildings must already be loaded.
    GraphLoadSummary loadConnections(const std::string& path);
 
    //GRAPH 3: buildings in insertion order, neighbors in insertion order.
    void displayGraph() const;
 
    //GRAPH 4: total buildings, total connections, degree of every building.
    void displayCountsAndDegrees() const;
 
    void bfsReachable(const std::string& startName) const;
 
    int findBuilding(const std::string& name) const;
    int buildingCount() const { return static_cast<int>(names.size()); }
    int connectionCount() const { return edgeCount; }
    int degree(int index) const { return static_cast<int>(adj[index].size()); }
    const std::string& buildingName(int index) const { return names[index]; }
    const std::vector<int>& neighbors(int index) const { return adj[index]; }

private:
    std::vector<std::string> names;
    std::vector<std::vector<int>> adj;
    int edgeCount = 0;

    bool hasEdge(int a, int b) const;
};

#endif
