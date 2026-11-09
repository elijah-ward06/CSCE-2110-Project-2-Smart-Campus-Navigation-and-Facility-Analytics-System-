Files (graph): include/campusgraph.h, src/campusgraph.cpp, include/stringutil.h
Test driver (not part of the build): tests/graph_test_main.cpp
  g++ -I./include tests/graph_test_main.cpp src/campusgraph.cpp -o graph_test && ./graph_test data
Own test data: testdata/graph_edge_cases/ (run with: ./Program testdata/graph_edge_cases)

CSCE 2110 - Project 2: Smart Campus Navigation and Facility Analytics System
[MILESTONE 1]

Team
-----
Elijah Ward - Member A: Facilities, Hash Table, ID Search
Bradey Jacobs - Member B: Campus Graph, BFS Reachability
Anthony Wink - Member C: Department Tree, Preorder Traversal

Purpose
--------
A console porgram that loads campus data from text files and
lets the user view and search facilities (by ID using a custom hash table),
explore building connections (undirected graph by BFS), and browse the acedmic
department hierachy (general tree)

Building
--------
From the project root:

    g++ -std=c++11 -Wall -I./include src/*.cpp -o Program

OR run

  ./compile.sh

Running
-------
./Program             Automatically sets the data folder to 'data/'
./Program <folder>    Loads data from <folder>

Arguements are optional, files are loaded in order:
  - buildings.txt
  - connections.txt
  - facilities.txt
  - depratments.txt

Warnings for rejected records and a load summary
for each file are printed before the menu appears.

Menu (Milestone 1)
-------
1. View all facilities
2. Search facility by ID
3. View campus graph
4. Display graph counts and degrees
5. Find reachable buildings (BFS)
6. Add department
7. Search department
8. Display department hierarchy
9. Run preorder traversal
0. Exit

Directory Layout
----------------
include/            Header files (Facility.h, FacilityDatabase.h, hashtable.h, campusgraph.h, departmenttree.h, stringutil.h)
src/                Source files, including main.cpp
data/               The four instructor-provided input files (unchanged)
testdata/           Our own test data folders:
  hash_edge_cases/          facility IDs that collide in the hash table
  graph_edge_cases/     duplicate/reversed connections, CRLF, etc.
  graph_edge_cases/tree_edge_cases/    department rejection cases
  graph_edge_cases/tree_root_only/     root-only department tree
tests/              Standalone module test drivers (not part of the main build)
README.txt          This file
design_document.txt Hash function, collision strategy, graph and tree design
test_results.txt    Recorded test cases and results
CONTRIBUTIONS.txt   Member responsibilities
compile.sh          Build script
.gitignore
