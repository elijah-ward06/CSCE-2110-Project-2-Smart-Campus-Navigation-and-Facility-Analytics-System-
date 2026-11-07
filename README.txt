Files (graph): include/campusgraph.h, src/campusgraph.cpp, include/stringutil.h
Test driver (not part of the build): tests/graph_test_main.cpp
  g++ -I./include tests/graph_test_main.cpp src/campusgraph.cpp -o graph_test && ./graph_test data
Own test data: testdata/graph_edge_cases/ (run with: ./Program testdata/graph_edge_cases)
