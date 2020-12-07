#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "graph.h"

using std::unordered_map;
using std::unordered_set;
using std::vector;

/**
 * Finds the shortest path from one vertex to another in a graph
 * using the A* search algorithm
 */
vector<Vertex> getShortestPath(const Graph& g, const Vertex& src,
                             const Vertex& dest);

/**
 * Calculates the heuristic value of a vertex based on its destination.
 */
double calculateHeuristic(const Graph& g, const Vertex& src,
                          const Vertex& dest);

/**
 * Finds the vertex in the open list with the lowest f score
 */
Vertex findVertexOfLowestF(const unordered_set<Vertex>& openList,
                           const unordered_map<Vertex, double>& f);

/**
 * Reconstructs the path of an A* search algorithm
 */
vector<Vertex> reconstructPath(const unordered_map<Vertex, Vertex>& cameFrom,
                             const Vertex& dest);

long double degreesToRadians(const long double degree);

double getOrthodromicDistance(const Vertex& source, const Vertex& destination);

