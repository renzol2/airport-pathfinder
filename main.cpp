#include <iostream>

#include "BFS.h"
#include "astar.h"
#include "shortestpath.h"
#include "readFromFile.h"

using std::cout;
using std::endl;

void runBFS(Graph& g, int directRoutes) {
  // Calls a BFS traversal which prints out to terminal the airports with at
  // least 100 direct routes to another airport.
  cout << "Printing airports with at least " << directRoutes 
       << " direct routes to another airport...\n\n";

  cout << "Note that this full graph traversal may take up to 3 minutes.\n\n" << endl;
  
  auto airports = BFS(g, directRoutes);

  if (airports.empty()) {
    cout << "No airports were found with at least " << directRoutes << " outgoing routes." << endl;
    return;
  }

  cout << "Done!\nThe airports with at least " << directRoutes << " outgoing routes using a Breadth First Search traversal:\n" << endl;

  // Print id of each vertex in path
  for (const auto& v : airports) {
    cout << v.label << ": " << v.name << endl;
  }
}

void runDijkstras(Graph& g, const Vertex& src, const Vertex& dest) {
  // Check that source and dest exist in the graph
  if (!g.vertexExists(src)) {
    cout << "Source vertex " << src.label << " does not exist.\n";
    return;
  }

  if (!g.vertexExists(dest)) {
    cout << "Destination vertex " << dest.label << " does not exist.\n";
    return;
  }

  cout << "Adjacents from src: " << g.getAdjacent(src).size() << endl;
  cout << "Adjacents from dest: " << g.getAdjacent(dest).size() << endl;
  cout << "Calculating shortest path from " << src.label << " to " << dest.label << "...\n\n";

  // Run Dijkstras 
  auto path = getShortestPath(g, src, dest);

  if (path.empty()) {
    cout << "No path was found." << endl;
    return;
  }

  cout << "Done!\nShortest path from vertices " << src.label << " to " << dest.label
            << " using Dijkstra's algorithm:\n";

  // Print id of each vertex in path
  for (const auto& v : path) {
    cout << v.label << ": " << v.name << endl;
  }
}

void runAStar(Graph& g, const Vertex& src, const Vertex& dest) {
  // Check that source and dest exist in the graph
  if (!g.vertexExists(src)) {
    cout << "Source vertex " << src.label << " does not exist.\n";
    return;
  }

  if (!g.vertexExists(dest)) {
    cout << "Destination vertex " << dest.label << " does not exist.\n";
    return;
  }

  cout << "Adjacents from src: " << g.getAdjacent(src).size() << endl;
  cout << "Adjacents from dest: " << g.getAdjacent(dest).size() << endl;
  cout << "Calculating shortest path from " << src.label << " to " << dest.label << "...\n\n";

  // Run A* 
  auto path = getShortestPathAStar(g, src, dest);

  if (path.empty()) {
    cout << "No path was found." << endl;
    return;
  }

  cout << "Done!\nShortest path from vertices " << src.label << " to " << dest.label
            << " using A* search:\n";

  // Print id of each vertex in path
  for (const auto& v : path) {
    cout << v.label << ": " << v.name << endl;
  }
}

/**
 * CS 225 Final Project
 * 
 * Compilation:
 *   make
 * 
 * Running:
 *   ./main bfs { directRoutes (default=100) }
 *   ./main astar { sourceID (required) } { destinationID (required) }
 */
int main(int argc, const char* argv[]) {
  if (argc == 1) {
    cout << "! Please specify whether you'd like to use 'bfs', 'dj' or 'astar'" << endl;
    return 0;
  } else if (argc > 1) {
    FileReader fr;
    Graph g = fr.getAirportData();
    auto vertices = g.getVertices();

    cout << "Data imported successfully." << endl;
    cout << "Total vertices: " << vertices.size() << endl;
    cout << "Total edges: " << g.getEdges().size() << '\n' << endl;

    string algo = string(argv[1]);
    cout << "algo: " << algo << endl;

    // Determine which algorithm to run
    if (algo == "bfs") {
      cout << "Running BFS...\n";

      // Get arguments
      int directRoutes;
      const int DefaultDirectRoutes = 100;

      if (argc > 2) {
        string directRoutesArg = argv[2];
        directRoutes = std::stoi(directRoutesArg);
      } else {
        directRoutes = DefaultDirectRoutes;
      }

      // Run BFS on Graph
      runBFS(g, directRoutes);
    } 
    else if (algo == "astar") {
      cout << "Running A*...\n";

      // Get arguments
      string sourceId = argv[2];
      string destId = argv[3];

      // Find vertices from arguments
      Vertex src;
      Vertex dest;
      for (const auto& v : vertices) {
        if (v.label == sourceId) src = v;
        if (v.label == destId) dest = v;
      }

      // Run A*
      runAStar(g, src, dest);
    }
    else if (algo == "dj") {
      cout << "Running Dijkstra's...\n";

      // Get arguments
      string sourceId = argv[2];
      string destId = argv[3];

      // Find vertices from arguments
      Vertex src;
      Vertex dest;
      for (const auto& v : vertices) {
        if (v.label == sourceId) src = v;
        if (v.label == destId) dest = v;
      }

      // Run Dijkstra's
      runDijkstras(g, src, dest);
    }
    else {
      cout << "Invalid algorithm. Choose 'bfs', 'dj', or 'astar'" << endl;
    }
  }

  return 0;
}
