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
  FileReader fr;
  return fr.getAirportData();
}

Vertex getAirportVertex(const Graph& airportData, const string& airportId) {
  for (const auto& v : airportData.getVertices()) {
    if (v.label == airportId) return v;
  }
  return Vertex();
}

vector<Vertex> getPath(const Graph& airportData, const vector<int>& airportIds) {
  vector<Vertex> vertices;
  for (int id : airportIds) {
    string airportId = std::to_string(id);
    Vertex v = getAirportVertex(airportData, airportId);

    // Return empty vector if path doesn't exist
    if (v == Vertex()) {
      return vector<Vertex>();
    }

    vertices.push_back(v);
  }
  return vertices;
}

/**
 * Test cases for shortest path between vertices a and b
 * - no path exists between a and b
 * - multiple shortest paths exist between a and b
 */

// Test Dijkstra's Algorithm
TEST_CASE("Test Dijkstra's") {
  // Load in airport data
  Graph airportData = getAirportTestingData();
  vector<Vertex> airports = airportData.getVertices();
  REQUIRE(airports.size() == 7698);

  SECTION("Simple graph") {
    Graph h = createSimpleGraph();
    vector<Vertex> f = getShortestPath(h, a, d);
    vector<Vertex> shortestPath1{a, b, d};
    vector<Vertex> shortestPath2{a, c, d};

    REQUIRE((f == shortestPath1 || f == shortestPath2));
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

  SECTION("Shortest path 50 -> 50 on airport data exists") {
    Vertex airport50 = getAirportVertex(airportData, "50");

    // Use A* to find shortest path between 50 and itself
    vector<Vertex> path = getShortestPath(airportData, airport50, airport50);

    REQUIRE(!path.empty());
    REQUIRE(path == vector<Vertex>{ airport50 });
  }

  SECTION("Shortest path 1 -> 5 on airport data exists") {
    Vertex airport1 = getAirportVertex(airportData, "1");
    Vertex airport5 = getAirportVertex(airportData, "5");

    // Use A* to find shortest path between 1 and 5
    vector<Vertex> path = getShortestPath(airportData, airport1, airport5);

    REQUIRE(!path.empty());
    REQUIRE(path == vector<Vertex>{ airport1, airport5 });
  }

  SECTION("Shortest path 10 -> 20 on airport data does not exist") {
    Vertex airport10 = getAirportVertex(airportData, "10");
    Vertex airport20 = getAirportVertex(airportData, "20");

    // Use A* to find shortest path between 10 and 20
    vector<Vertex> path = getShortestPath(airportData, airport10, airport20);

    REQUIRE(path.empty());
  }

  SECTION("Shortest path 1 -> 30 on airport data exists") {
    vector<int> expectedPathIds = {1, 5, 3361, 3728, 156, 30};

    Vertex airport1 = getAirportVertex(airportData, "1");
    Vertex airport30 = getAirportVertex(airportData, "30");

    // Use A* to find shortest path between 1 and 30
    vector<Vertex> path = getShortestPath(airportData, airport1, airport30);

    REQUIRE(!path.empty());

    vector<Vertex> expectedPath = getPath(airportData, expectedPathIds);
    REQUIRE(path == expectedPath);
  }

}

// Test A* Algorithm
TEST_CASE("Test A*") {
  // Load in airport data
  Graph airportData = getAirportTestingData();
  vector<Vertex> airports = airportData.getVertices();
  REQUIRE(airports.size() == 7698);

  SECTION("Simple graph") {
    Graph h = createSimpleGraph();
    vector<Vertex> f = getShortestPathAStar(h, a, d);
    vector<Vertex> shortestPath1{a, b, d};
    vector<Vertex> shortestPath2{a, c, d};

    REQUIRE((f == shortestPath1 || f == shortestPath2));
  }

  SECTION("Vertices with no path results in no shortest path") {
    // Make a graph with two vertices that have no path
    // Run Dijkstra's on the two vertices
    // Check that the resulting vector is empty
    Graph g = createUnconnectedGraph();
    vector<Vertex> f = getShortestPathAStar(g, a, d);
    vector<Vertex> shortestPath{};
    REQUIRE(f == shortestPath);
  }

  SECTION("If a == b, path should be length 1") {
    // Run Dijkstra's with source == destination
    Graph j = Graph(true, true);
    j.insertVertex(a);
    vector<Vertex> f = getShortestPathAStar(j, a, a);
    vector<Vertex> shortestPath{a};
    REQUIRE(f.size() == 1);
    REQUIRE(f == shortestPath);
  }

  SECTION("Shortest path 50 -> 50 on airport data exists") {
    Vertex airport50 = getAirportVertex(airportData, "50");

    // Use A* to find shortest path between 50 and itself
    vector<Vertex> path = getShortestPathAStar(airportData, airport50, airport50);

    REQUIRE(!path.empty());
    REQUIRE(path == vector<Vertex>{ airport50 });
  }

  SECTION("Shortest path 1 -> 5 on airport data exists") {
    Vertex airport1 = getAirportVertex(airportData, "1");
    Vertex airport5 = getAirportVertex(airportData, "5");

    // Use A* to find shortest path between 1 and 5
    vector<Vertex> path = getShortestPathAStar(airportData, airport1, airport5);

    REQUIRE(!path.empty());
    REQUIRE(path == vector<Vertex>{ airport1, airport5 });
  }

  SECTION("Shortest path 10 -> 20 on airport data does not exist") {
    Vertex airport10 = getAirportVertex(airportData, "10");
    Vertex airport20 = getAirportVertex(airportData, "20");

    // Use A* to find shortest path between 10 and 20
    vector<Vertex> path = getShortestPathAStar(airportData, airport10, airport20);

    REQUIRE(path.empty());
  }


  SECTION("Shortest path 1 -> 30 on airport data exists") {
    vector<int> expectedPathIds = {1, 5, 3361, 3728, 156, 30};

    Vertex airport1 = getAirportVertex(airportData, "1");
    Vertex airport30 = getAirportVertex(airportData, "30");

    // Use A* to find shortest path between 1 and 30
    vector<Vertex> path = getShortestPathAStar(airportData, airport1, airport30);

    REQUIRE(!path.empty());

    vector<Vertex> expectedPath = getPath(airportData, expectedPathIds);
    REQUIRE(path == expectedPath);
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
  g.insertEdge(r, y);
  g.insertEdge(q, y);
  g.insertEdge(u, v);
  g.insertEdge(s, w);
  g.insertEdge(t, x);

  vector<Vertex> output = BFS(g, 1);
  vector<Vertex> result{z, w, x, y, s, t, v, q, r, u};

  REQUIRE(output.size() == 10);
  REQUIRE(output == result);
}
