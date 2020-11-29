#include <iostream>

#include "BFS.h"
#include "astar.h"
#include "readFromFile.h"

int main(int argc, const char* argv[]) {
  FileReader fr;
  Graph g = fr.getAirportData();

  // Calls a BFS traversal which prints out to terminal the airports with at
  // least 100 direct routes to another airport.
  BFS(g);

  // Finds the shortest path between vertices a and b using A*
  Vertex a = "7504";
  Vertex b = "246";
  auto path = getShortestPath(g, a, b);

  std::cout << "Shortest path from vertices " << a << " to " << b
            << " using A* search:\n";

  for (const auto& v : path) {
    std::cout << v << std::endl;
  }

  return 0;
}