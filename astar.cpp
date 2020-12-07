#include "astar.h"

#include <set>
#include <cfloat>

using std::unordered_set;
using std::unordered_map;

// Written using pseudocode from the following source:
// https://en.wikipedia.org/wiki/A*_search_algorithm

vector<Vertex> getShortestPath(const Graph& graph, const Vertex& src,
                             const Vertex& dest) {
  // Keeps track of where a vertex's source
  unordered_map<Vertex, Vertex> cameFrom;

  // g(n) is cost of the cheapest path from src to n
  unordered_map<Vertex, double> gScores;
  gScores[src] = 0;

  // f(n) = g(n) + h(n)
  unordered_map<Vertex, double> fScores;
  fScores[src] = calculateHeuristic(src, dest);

  // The open list of vertices that must be explored
  unordered_set<Vertex> openList;
  openList.insert(src);

  while (!openList.empty()) {
    Vertex current = findVertexOfLowestF(openList, fScores);

    if (current == dest) {
      return reconstructPath(cameFrom, dest);
    }

    openList.erase(current);
    for (const Vertex& neighbor : graph.getAdjacent(current)) {
      double gCurrent = gScores[current] + graph.getEdgeWeight(current, neighbor);

      // Initialize g score of neighbor as max if it doesn't exist
      if (gScores.find(neighbor) == gScores.end()) {
        gScores[neighbor] = DBL_MAX;
      }

      if (gCurrent < gScores[neighbor]) {
        cameFrom[neighbor] = current;
        gScores[neighbor] = gCurrent;
        fScores[neighbor] = gScores[neighbor] + calculateHeuristic(current, dest);
        if (openList.find(neighbor) == openList.end()) {
          openList.insert(neighbor);
        }
      }
    }
  }

  return vector<Vertex>();
}

double calculateHeuristic(const Vertex& src, const Vertex& dest) {
  return getOrthodromicDistance(src, dest);
}

Vertex findVertexOfLowestF(const unordered_set<Vertex>& openList,
                           const unordered_map<Vertex, double>& f) {
  Vertex lowest;
  for (const Vertex& v : openList) {
    if (lowest.empty() || f.at(v) < f.at(lowest)) {
      lowest = v;
    }
  }
  return lowest;
}

vector<Vertex> reconstructPath(const unordered_map<Vertex, Vertex>& cameFrom,
                             const Vertex& dest) {
  vector<Vertex> path = { dest };
  Vertex current = dest;

  while (cameFrom.find(current) != cameFrom.end()) {
    current = cameFrom.at(current);
    path.push_back(current);
  }
  
  std::reverse(path.begin(), path.end());
  return path;
}

long double degreesToRadians(const long double degree) { 
  return (degree * 3.14 / 180);
} 

double getOrthodromicDistance(const Vertex& source, const Vertex& destination)  {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = degreesToRadians(source.latitude);
  lon1r = degreesToRadians(source.longitude);
  lat2r = degreesToRadians(destination.latitude);
  lon2r = degreesToRadians(destination.longitude);

  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  const double EARTH_RADIUS_KM = 6371.0;
  return 2.0 * EARTH_RADIUS_KM * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}
