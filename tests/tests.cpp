#include "../astar.h"
#include "../catch/catch.hpp"
#include "../graph.h"
#include "../readFromFile.h"
#include "../shortestpath.h"

using namespace std;

Vertex a = Vertex("a");
Vertex b = Vertex("b");
Vertex c = Vertex("c");
Vertex d = Vertex("d");

Graph createSimpleGraph() {
  Graph h = Graph(true, true);
  h.insertVertex(a);
  h.insertVertex(b);
  h.insertVertex(c);
  h.insertVertex(d);
  h.insertEdge(a, c);
  h.setEdgeWeight(a, c, 1/3);
  h.insertEdge(a, b);
  h.setEdgeWeight(a, b, 1/4);
  h.insertEdge(b, d);
  h.setEdgeWeight(b, d, 1);
  h.insertEdge(c, d);
  h.setEdgeWeight(c, d, 1/5);
  return h;
}

Graph getAirportTestingData() {
  int NUMBER_LINES = 100;
  FileReader fr;
  return fr.getAirportData("100airports.dat.txt", NUMBER_LINES);
}

/**
 * Test cases for shortest path between vertices a and b
 * - no path exists between a and b
 * - multiple shortest paths exist between a and b
 */

TEST_CASE("Test Dijkstra's") {
  // Test Dijkstra's Algorithm
  SECTION("Simple graph") {

  }

  SECTION("Vertices with no path results in no shortest path") {

  }

  SECTION("Multiple shortest paths returns the first shortest path") {

  }

  SECTION("Shortest path on airport subset works") {
    
  }
  Graph h = createSimpleGraph();
  vector<Vertex> f = getShortestPath(h, a, d);
  vector<Vertex> shortestPath{a, b, d};
  REQUIRE(f == shortestPath);
}

// Test A* Algorithm
TEST_CASE("Test A*") {
  SECTION("Simple graph") {
    Graph h = createSimpleGraph();
    vector<Vertex> f = getShortestPathAStar(h, a, d);
    vector<Vertex> shortestPath{a, b, d};
    REQUIRE(f == shortestPath);
  }

  SECTION("Vertices with no path results in no shortest path") {

  }

  SECTION("Multiple shortest paths returns the first shortest path") {

  }

  SECTION("Shortest path on airport subset works") {
  }
}

TEST_CASE("Test BFS") {
  Graph h = createSimpleGraph();
}