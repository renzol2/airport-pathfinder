#include "astar.h"

#include <set>
#include <functional>
#include <queue>
#include <cfloat>

using std::unordered_set;
using std::unordered_map;
using std::vector;
using std::pair;
using std::priority_queue;

// Written using pseudocode from the following source:
// https://en.wikipedia.org/wiki/A*_search_algorithm

const double EARTH_RADIUS_KM = 6371.0;

vector<Vertex> getShortestPathAStar(const Graph& graph, const Vertex& src,
                             const Vertex& dest) {
  // Keeps track of where a vertex's source
  unordered_map<Vertex, Vertex> cameFrom;

  // g(n) is cost of the cheapest path from src to n
  unordered_map<Vertex, double> gScores;
  gScores[src] = 0;

  // f(n) = g(n) + h(n)
  unordered_map<Vertex, double> fScores;

  // h(n) is estimated cost from n to dest
  fScores[src] = calculateHeuristic(src, dest);

  // The queue of vertices that must be explored
  priority_queue<pair<double, Vertex>, vector<pair<double, Vertex>>, std::greater<pair<double, Vertex>>> openSet;
  // A duplicate container of vertices as the priority queue. Used for searching
  unordered_set<Vertex> openSetItems;
  
  openSet.push({ fScores[src], src });
  openSetItems.insert(src);

  while (!openSet.empty()) {
    // Vertex current = findVertexOfLowestF(openList, fScores);
    Vertex current = openSet.top().second;

    // If destination is reached, return path
    if (current == dest) {
      return reconstructPath(cameFrom, dest);
    }

    openSet.pop();
    openSetItems.erase(current);

    for (const Vertex& neighbor : graph.getAdjacent(current)) {
      double gCurrent = gScores[current] + graph.getEdgeWeight(current, neighbor);

      // Initialize g score of neighbor as max if it doesn't exist
      if (gScores.find(neighbor) == gScores.end()) {
        gScores[neighbor] = DBL_MAX;
      }

      // If neighbor n has a better g(n), add it to the list to check later
      if (gCurrent < gScores[neighbor]) {
        cameFrom[neighbor] = current;
        gScores[neighbor] = gCurrent;
        // f(n) = g(n) + h(n). This is the key difference from Dijkstra's
        fScores[neighbor] = gScores[neighbor] + calculateHeuristic(current, dest);

        // This is where the openSet map comes in; searching for neighbors
        // Probably not the best implementation
        if (openSetItems.find(neighbor) == openSetItems.end()) {
          openSet.push({ fScores[neighbor], neighbor });
          openSetItems.insert(neighbor);
        }
      }
    }
  }

  return vector<Vertex>();
}

double calculateHeuristic(const Vertex& src, const Vertex& dest) {
  double distance = getOrthodromicDistance(src, dest);
  // Divide by Earth's diameter to guarantee a value in range [0, 1]
  double h = distance / (2 * EARTH_RADIUS_KM);
  return h;
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

// https://stackoverflow.com/questions/10198985/calculating-the-distance-between-2-latitudes-and-longitudes-that-are-saved-in-a
double getOrthodromicDistance(const Vertex& source, const Vertex& destination)  {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = degreesToRadians(source.latitude);
  lon1r = degreesToRadians(source.longitude);
  lat2r = degreesToRadians(destination.latitude);
  lon2r = degreesToRadians(destination.longitude);

  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  double distance = 2.0 * EARTH_RADIUS_KM * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
  return distance;
}
