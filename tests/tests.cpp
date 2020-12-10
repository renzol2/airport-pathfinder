#include "../astar.h"
#include "../catch/catch.hpp"
#include "../graph.h"
#include "../readFromFile.h"
#include "../shortestpath.h"

#include <iostream>

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

Graph createUnconnectedGraph() {
  Graph h = Graph(true, true);
  h.insertVertex(a);
  h.insertVertex(b);
  h.insertVertex(c);
  h.insertVertex(d);
  return h;
}

Graph createSquareGraph() {
  Graph h = Graph(true, true);
  h.insertVertex(a);
  h.insertVertex(b);
  h.insertVertex(c);
  h.insertVertex(d);
  h.insertEdge(a, c);
  h.setEdgeWeight(a, c, 1);
  h.insertEdge(a, b);
  h.setEdgeWeight(a, b, 1);
  h.insertEdge(b, d);
  h.setEdgeWeight(b, d, 1);
  h.insertEdge(c, d);
  h.setEdgeWeight(c, d, 1);
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
    Graph h = createSimpleGraph();
    vector<Vertex> f = getShortestPath(h, a, d);
    vector<Vertex> shortestPath{a, c, d};
    REQUIRE(f == shortestPath);
  }

  SECTION("Vertices with no path results in no shortest path") {
    // Make a graph with two vertices that have no path
    // Run Dijkstra's on the two vertices
    // Check that the resulting vector is empty
    Graph g = createUnconnectedGraph();
    vector<Vertex> f = getShortestPath(g, a, d);
    vector<Vertex> shortestPath{};
    REQUIRE(f == shortestPath);
  }

  SECTION("If a == b, path should be length 1") {
    // Run Dijkstra's with source == destination
    Graph j = Graph(true, true);
    j.insertVertex(a);
    vector<Vertex> f = getShortestPath(j, a, a);
    vector<Vertex> shortestPath{a};
    REQUIRE(f.size() == 1);
    REQUIRE(f == shortestPath);
  }

  // SECTION("Multiple shortest paths returns the first shortest path") {
  //   // Make a graph with two shortest paths
  //   Graph k = createSquareGraph();
  //   vector<Vertex> f = getShortestPath(k, a, d);
  //   vector<Vertex> shortestPath{a, c, d};
  //   REQUIRE(f == shortestPath);
  // }

  SECTION("Path between an airport and itself exists") {
  }

  SECTION("Path between airports 1 and 2 exists") {
  }

  SECTION("Path between airports 1 and 5 exists") {
  }

  SECTION("Path between airports 4 and 12 does not exist") {
  }

  SECTION("Path of airport a and b is same as path between b and a") {

  }
  
}

// Test A* Algorithm
TEST_CASE("Test A*") {
  // Test A* Algorithm
  SECTION("Simple graph") {
    Graph h = createSimpleGraph();
    vector<Vertex> f = getShortestPathAStar(h, a, d);
    vector<Vertex> shortestPath{a, c, d};
    REQUIRE(f == shortestPath);
  }

  SECTION("Vertices with no path results in no shortest path") {
    // Make a graph with two vertices that have no path
    // Run A* on the two vertices
    // Check that the resulting vector is empty
  }

  SECTION("If a == b, path should be length 1") {
    // Run A* with source == destinatino
  }

  SECTION("Multiple shortest paths returns the first shortest path") {
    // Make a graph with two shortest paths
  }

  SECTION("Path between an airport and itself exists") {
  }

  SECTION("Path between airports 1 and 2 exists") {
  }

  SECTION("Path between airports 1 and 5 exists") {
  }

  SECTION("Path between airports 4 and 12 does not exist") {
  }

  SECTION("Path of airport a and b is same as path between b and a") {

  }
  
}

TEST_CASE("Test BFS") {
  Graph h = createSimpleGraph();
}