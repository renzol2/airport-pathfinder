#include <iostream> 
#include "readFromFile.h"
#include "BFS.h"

int main(int argc, const char* argv[]) {
  FileReader fr;
  Graph g = fr.getAirportData();

  // auto v = g.getVertices();
  // for (const auto& vertex : v) {
  //   std::cout << vertex << std::endl;
  // }

  //Calls a BFS traversal which prints out to terminal the airports with at least 100 direct routes to another airport.
  BFS(g);

  return 0;
}