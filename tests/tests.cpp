#include "../astar.h"
#include "../catch/catch.hpp"
#include "../graph.h"
#include "../readFromFile.h"
#include "../shortestpath.h"
#include "../BFS.h"

using namespace std;

const Vertex a = Vertex("a");
const Vertex b = Vertex("b");
const Vertex c = Vertex("c");
const Vertex d = Vertex("d");

/**
 * Creates graph as follows:
 * 
 * A --> B
 * |     |
 * v     v
 * C --> D
 */
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
    Graph h = createSimpleGraph();
    vector<Vertex> f = getShortestPath(h, a, d);
    vector<Vertex> shortestPath1{a, b, d};
    vector<Vertex> shortestPath2{a, c, d};

    REQUIRE((f == shortestPath1 || f == shortestPath2));
  }

  SECTION("Vertices with no path results in no shortest path") {

  }

  SECTION("Multiple shortest paths returns the first shortest path") {

  }

  SECTION("Shortest path on airport subset works") {
    
  }

}

// Test A* Algorithm
TEST_CASE("Test A*") {
  SECTION("Simple graph") {
    Graph h = createSimpleGraph();
    vector<Vertex> f = getShortestPathAStar(h, a, d);
    vector<Vertex> shortestPath1{a, b, d};
    vector<Vertex> shortestPath2{a, c, d};

    REQUIRE((f == shortestPath1 || f == shortestPath2));
  }

  SECTION("Vertices with no path results in no shortest path") {

  }

  SECTION("Multiple shortest paths returns the first shortest path") {

  }

  SECTION("Shortest path on airport subset works") {
  }
}

TEST_CASE("Test BFS") {
  Graph g = Graph(true, true);
  
  Vertex z = Vertex("z");
  Vertex y = Vertex("y");
  Vertex x = Vertex("x");
  Vertex w = Vertex("w");
  Vertex v = Vertex("v");
  Vertex u = Vertex("u");
  Vertex t = Vertex("t");
  Vertex s = Vertex("s");
  Vertex r = Vertex("r");
  Vertex q = Vertex("q");
  g.insertVertex(z);
  g.insertVertex(y);
  g.insertVertex(x);
  g.insertVertex(w);
  g.insertVertex(v);
  g.insertVertex(u);
  g.insertVertex(t);
  g.insertVertex(s);
  g.insertVertex(r);
  g.insertVertex(q);

  g.insertEdge(z, y);
  g.insertEdge(z, w);
  g.insertEdge(z, x);
  g.insertEdge(y, r);
  g.insertEdge(y, q);
  g.insertEdge(y, v);
  g.insertEdge(v, u);
  g.insertEdge(x, t);
  g.insertEdge(w, s);
  //
  g.insertEdge(r, y);
  g.insertEdge(q, y);
  g.insertEdge(u, v);
  g.insertEdge(s, w);
  g.insertEdge(t, x);

  vector<Vertex> output = BFS(g, 1);
  vector<Vertex> result{z, w, x, y, s, t, v, q, r, u};
  
  // for (auto & v : output) {
  //   cout << v.label << endl;
  // }

  REQUIRE(output.size() == 10);
  REQUIRE(output == result);
}