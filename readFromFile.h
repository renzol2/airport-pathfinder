#pragma once

#include "graph.h"

class FileReader {
  public:
    FileReader();
    Graph getAirportData();
    Graph getAirportData(const string& filename, int lines);
};
