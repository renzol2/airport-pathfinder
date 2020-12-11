#include <iostream>
#include <cstdlib>
#include <ctime>

#include "BFS.h"
#include "astar.h"
#include "shortestpath.h"
#include "readFromFile.h"

using std::cout;
using std::endl;

// Constants
const int DEFAULT_DIRECT_ROUTES = 100;
const string BFS_ARG = "bfs";

const string DEFAULT_SOURCE = "1";
const string HARTSFIELD_JACKSON_AIRPORT_ID = "3682";
const string DEFAULT_DEST = HARTSFIELD_JACKSON_AIRPORT_ID;
const string DIJKSTRAS_ARG = "dj";
const string ASTAR_ARG = "astar";

const int DEFAULT_PATHS_RANGE = 10;
const string PATHS_ARG = "paths";

/**
 * Prints the label and name of all airports
 */
void printAirports(const vector<Vertex>& airports) {
  for (const auto& v : airports) {
    cout << ' ' << v.label << ": " << v.name.substr(1, v.name.size() - 2) << endl;
  }
}

/**
 * Runs Breadth First Search on graph
 */
void runBFS(Graph& g, int directRoutes) {
  // Calls a BFS traversal which prints out to terminal the airports with at
  // least n direct routes to another airport.
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
  printAirports(airports);
}

/**
 * Runs a shortest path algorithm on the graph
 */
void runShortestPath(const string& arg, Graph& g, const string& sourceId, const string& destId) {
  if (arg != DIJKSTRAS_ARG && arg != ASTAR_ARG) {
    cout << "Please select either 'dj' (Dijkstra's) or 'astar' (A*) for shortest path" << endl;
    return;
  }

  // Set appropriate string for terminal output
  string algorithm = arg == DIJKSTRAS_ARG ? "Dijkstra's" : "A*";

  // Find vertices from arguments
  auto vertices = g.getVertices();
  Vertex src;
  Vertex dest;
  for (const auto& v : vertices) {
    if (v.label == sourceId) src = v;
    if (v.label == destId) dest = v;
  }

  // Check that source and dest exist in the graph
  if (!g.vertexExists(src)) {
    cout << "Source vertex " << src.label << " does not exist." << endl;
    return;
  }

  if (!g.vertexExists(dest)) {
    cout << "Destination vertex " << dest.label << " does not exist." << endl;
    return;
  }

  cout << "Algorithm: " << algorithm << endl;
  cout << "Adjacent vertices from source: " << g.getAdjacent(src).size() << endl;
  cout << "Adjacent vertices from destination: " << g.getAdjacent(dest).size() << endl;
  cout << "Calculating shortest path from " << src.label << " to " << dest.label << "...\n\n";

  vector<Vertex> path;
  if (arg == DIJKSTRAS_ARG) {
    path = getShortestPath(g, src, dest);
  } else {
    path = getShortestPathAStar(g, src, dest);
  }

  if (path.empty()) {
    cout << "No path was found." << endl;
    return;
  }

  cout << "Done!\nShortest path from vertices " << src.label << " to " << dest.label
            << " using " << algorithm << ":" << endl;

  printAirports(path);
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

void runCalculatePaths(Graph& g, const string& algo, int range) {
  if (algo != DIJKSTRAS_ARG && algo != ASTAR_ARG) {
    cout << "Please select either 'dj' (Dijkstra's) or 'astar' (A*) for calcluating paths" << endl;
    return;
  }

  auto airportVertices = g.getVertices();

  // Set source to Hartsfield-Jackson Atlanta International Airport (ID 3682)
  Vertex source = getAirportVertex(g, HARTSFIELD_JACKSON_AIRPORT_ID);

  cout << "Finding " << range << " shortest paths between Hartsfield-Jackson and a random airport: " << endl;
  for (int i = 0; i < range; i++) {
    const Vertex& destination = airportVertices[rand() % airportVertices.size()];

    // Get the path with either Dijkstra's or A*
    vector<Vertex> path;
    if (algo == DIJKSTRAS_ARG) {
      path = getShortestPath(g, source, destination);
    } else {
      path = getShortestPathAStar(g, source, destination);
    }

    cout << " Shortest path length from Hartsfield-Jackson -> " 
          << destination.name.substr(1, destination.name.size() - 2) 
          << ": " << path.size() << '\n';
  }

  cout << "Finished." << endl;
  cout << "Run with command `time` and compare between Dijkstra's and A*." << endl;
}

/**
 * CS 225 Final Project
 * 
 * Compilation:
 *   make
 * 
 * Running:
 *   ./main bfs DIRECT_ROUTES
 *   ./main dj SOURCE_ID DESTINATION_ID
 *   ./main astar SOURCE_ID DESTINATION_ID
 *   ./main paths dj RANGE
 *   ./main paths astar RANGE
 */
int main(int argc, const char* argv[]) {
  // Set random seed for paths
  srand(time(NULL));

  if (argc == 1) {
    cout << "! Please specify whether you'd like to use 'bfs', 'dj' or 'astar'" << endl;
    return 0;
  } else if (argc > 1) {
    FileReader fr;
    Graph g = fr.getAirportData();

    cout << "Data imported successfully." << endl;
    cout << "Total vertices: " << g.getVertices().size() << endl;
    cout << "Total edges: " << g.getEdges().size() << '\n' << endl;

    string algo = string(argv[1]);

    // Determine which algorithm to run
    if (algo == BFS_ARG) {
      cout << "Running BFS...\n";

      // Get arguments
      int directRoutes;

      if (argc > 2) {
        string directRoutesArg = argv[2];
        directRoutes = std::stoi(directRoutesArg);
      } else {
        directRoutes = DEFAULT_DIRECT_ROUTES;
      }

      // Run BFS on Graph
      runBFS(g, directRoutes);
    } 
    else if (algo == DIJKSTRAS_ARG || algo == ASTAR_ARG) {
      // Get arguments, checking if user included arguments or not
      string sourceId = argc > 2 ? argv[2] : DEFAULT_SOURCE;
      string destId = argc > 3 ? argv[3] : DEFAULT_DEST;

      // Run shortest path
      runShortestPath(algo, g, sourceId, destId);
    }
    else if (algo == PATHS_ARG) {
      if (argc < 3) {
        cout << "Improper usage." << endl;
        cout << "Correct Usage: ./main paths [dj OR astar] [# of paths to calculate]" << endl;
        return 0;
      }

      string algoChoice = argv[2];
      if (algoChoice != DIJKSTRAS_ARG && algoChoice != ASTAR_ARG) {
        cout << "Please select either 'dj' (Dijkstra's) or 'astar' (A*) for calcluating paths" << endl;
        cout << "Correct Usage: ./main paths [dj OR astar] [# of paths to calculate]" << endl;
        return 0;
      }

      // Get paths, checking if user included it or not
      int paths;
      if (argc > 3) {
        string pathsArg = argv[3];
        paths = std::stoi(pathsArg);
      } else {
        paths = DEFAULT_PATHS_RANGE;
      }

      runCalculatePaths(g, algoChoice, paths);
    }
    else {
      cout << "Invalid algorithm. Choose 'bfs', 'dj', or 'astar'" << endl;
    }
  }

  return 0;
}
