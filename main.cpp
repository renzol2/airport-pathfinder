#include <iostream>

#include "BFS.h"
#include "astar.h"
#include "readFromFile.h"

using std::cout;
using std::endl;

void runBFS(Graph& g) {
  // Calls a BFS traversal which prints out to terminal the airports with at
  // least 100 direct routes to another airport.
  BFS(g);
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

  cout << "Calculating shortest path from " << src.label << " to " << dest.label << "...\n\n";

  // Run A* 
  auto path = getShortestPath(g, src, dest);

  if (path.empty()) {
    cout << "No path was found." << endl;
    return;
  }

  cout << "Done!\nShortest path from vertices " << src.label << " to " << dest.label
            << " using A* search:\n";

  // Print id of each vertex in path
  for (const auto& v : path) {
    cout << v.label << endl;
  }
}

/**
 * CS 225 Final Project
 * 
 * Compilation:
 *   make main
 * 
 * Running:
 *   ./main bfs
 *   ./main astar {source} {destination}
 */
int main(int argc, const char* argv[]) {
  if (argc == 1) {
    cout << "! Please specify whether you'd like to use 'bfs' or 'astar'" << endl;
    return 0;
  } else if (argc > 1) {
    FileReader fr;
    string algo = string(argv[1]);

    if (algo == "bfs") {
      cout << "Running BFS...\n";
      Graph g = fr.getAirportData();
      runBFS(g);
    } else if (algo == "astar") {
      cout << "Running A*...\n";
      Graph g = fr.getAirportData();
      Vertex src(argv[2]);
      Vertex dest(argv[3]);
      runAStar(g, src, dest);
    } else {
      cout << "Invalid algorithm. Choose 'bfs' or 'astar'" << endl;
    }
  }

  return 0;
}
