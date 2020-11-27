#include <iostream> 
#include "readFromFile.h"

int main(int argc, const char* argv[]) {
  FileReader fr;
  Graph g = fr.getAirportData();

  auto v = g.getVertices();
  for (const auto& vertex : v) {
    std::cout << vertex << std::endl;
  }

  return 0;
}