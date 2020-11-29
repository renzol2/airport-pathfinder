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

  // g(vertex) = f(vertex) + h(vertex)
  unordered_map<Vertex, double> gScores;
  gScores[src] = 0;

  unordered_map<Vertex, double> fScores;
  fScores[src] = calculateHeuristic(graph, src, dest);

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
        fScores[neighbor] = gScores[neighbor] + calculateHeuristic(graph, current, neighbor);
        if (openList.find(neighbor) == openList.end()) {
          openList.insert(neighbor);
        }
      }
    }
  }

  return vector<Vertex>();
}

// FIXME: this should be able to calculate the orthodromic distance of any
// pair of vertices, regardless of an edge existing. Need to refactor
double calculateHeuristic(const Graph& g, const Vertex& src,
                          const Vertex& dest) {
  if (g.edgeExists(src, dest)) {
    return g.getOrthodromicDistance(src, dest);
  } else {
    return DBL_MAX;
  }
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
