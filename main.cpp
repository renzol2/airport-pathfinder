#include <iostream> 
#include "readFromFile.h"

int main(int argc, const char* argv[]) {
  FileReader fr;
  Graph g = fr.getAirportData();
  std::cout << &g << std::endl;

  return 0;
}