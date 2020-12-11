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
 * Testing helper methods
 */

/**
 * Creates graph as follows:
 * 
 * A --> B
 * |     |
 * v     v
 * C --> D
 * 
 * Each edge has a different weight
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

/**
 * Creates graph as follows:
 * 
 * A B C D
 * 
 */
Graph createUnconnectedGraph() {
  Graph h = Graph(true, true);
  h.insertVertex(a);
  h.insertVertex(b);
  h.insertVertex(c);
  h.insertVertex(d);
  return h;
}

/**
 * Creates graph as follows:
 * 
 * A --> B
 * |     |
 * v     v
 * C --> D
 * 
 * Each edge has the same weight (1)
 */
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

/**
 * Parses airport data into graph for testing
 */
Graph getAirportTestingData() {
  FileReader fr;
  return fr.getAirportData();
}

/**
 * Finds an airport vertex based on its id
 */
Vertex getAirportVertex(const Graph& airportData, const string& airportId) {
  for (const auto& v : airportData.getVertices()) {
    if (v.label == airportId) return v;
  }
  return Vertex();
}

/**
 * Converts a vector of airport IDs as integers into a vector of Vertices
 * from the given airport data
 */
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
 * Test cases
 */

// Test Dijkstra's Algorithm
TEST_CASE("Test Dijkstra's") {
  // Load in airport data
  Graph airportData = getAirportTestingData();
  vector<Vertex> airports = airportData.getVertices();
  REQUIRE(airports.size() == 7698);

  SECTION("Shortest path works on simple graph") {
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
    vector<int> expectedPathIds1 = {1, 5, 3361, 3728, 156, 30};
    vector<int> expectedPathIds2 = {1, 5, 3320, 3484, 156, 30};

    Vertex airport1 = getAirportVertex(airportData, "1");
    Vertex airport30 = getAirportVertex(airportData, "30");

    // Use A* to find shortest path between 1 and 30
    vector<Vertex> path = getShortestPath(airportData, airport1, airport30);

    REQUIRE(!path.empty());

    vector<Vertex> expectedPath1 = getPath(airportData, expectedPathIds1);
    vector<Vertex> expectedPath2 = getPath(airportData, expectedPathIds2);
    REQUIRE((path == expectedPath1 || path == expectedPath2));
  }

}

// Test A* Algorithm
TEST_CASE("Test A*") {
  // Load in airport data
  Graph airportData = getAirportTestingData();
  vector<Vertex> airports = airportData.getVertices();
  REQUIRE(airports.size() == 7698);

  SECTION("Shortest path works on simple graph") {
    Graph h = createSimpleGraph();
    vector<Vertex> f = getShortestPathAStar(h, a, d);
    vector<Vertex> shortestPath1{a, b, d};
    vector<Vertex> shortestPath2{a, c, d};

    REQUIRE((f == shortestPath1 || f == shortestPath2));
  }

  SECTION("Vertices with no path results in no shortest path") {
    // Make a graph with two vertices that have no path
    // Run A* on the two vertices
    // Check that the resulting vector is empty
    Graph g = createUnconnectedGraph();
    vector<Vertex> f = getShortestPathAStar(g, a, d);
    vector<Vertex> shortestPath{};
    REQUIRE(f == shortestPath);
  }

  SECTION("If a == b, path should be length 1") {
    // Run A* with source == destination
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
    vector<int> expectedPathIds1 = {1, 5, 3361, 3728, 156, 30};
    vector<int> expectedPathIds2 = {1, 5, 3320, 3484, 156, 30};

    Vertex airport1 = getAirportVertex(airportData, "1");
    Vertex airport30 = getAirportVertex(airportData, "30");

    // Use A* to find shortest path between 1 and 30
    vector<Vertex> path = getShortestPathAStar(airportData, airport1, airport30);

    REQUIRE(!path.empty());

    vector<Vertex> expectedPath1 = getPath(airportData, expectedPathIds1);
    vector<Vertex> expectedPath2 = getPath(airportData, expectedPathIds2);
    REQUIRE((path == expectedPath1 || path == expectedPath2));
  }
}

// For each pair of airports i, j with i and j in [0, n],
// check that Dijkstra's and A* reach the same output
TEST_CASE("Verify correctness of shortest path algorithms") {
  // Load in airport data
  Graph airportData = getAirportTestingData();
  vector<Vertex> airports = airportData.getVertices();
  REQUIRE(airports.size() == 7698);

  // # of airports to test on
  // Note this is an O(n^2) operation:
  // - 20 airports  = ~9s local runtime
  // - 50 airports  = ~54s local runtime
  // - 100 airports = ~3m52s local runtime
  const int NUM_AIRPORTS = 10;

  for (int i = 0; i < NUM_AIRPORTS; i++) {
    for (int j = 0; j < NUM_AIRPORTS; j++) {
      const Vertex& airport1 = airports[i];
      const Vertex& airport2 = airports[j];

      // Get the same path with Dijkstra's and A*
      auto path_dj = getShortestPath(airportData, airport1, airport2);
      auto path_astar = getShortestPathAStar(airportData, airport1, airport2);

      // Verify that both paths are the same length
      REQUIRE(path_dj.size() == path_astar.size());
    }
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
