// Written using the following sources:
// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/

#include "shortestpath.h"

#include <map>
#include <queue>

vector<Vertex> getShortestPath(const Graph & g, const Vertex & src, const Vertex & dest) {

    // Maps a vertex to its distance from the source
	std::map<Vertex, double> distance;
    // Maps a vertex to its predecessor
	std::map<Vertex, Vertex> predecessor;
    // Contains the shortest path to return at the end
    std::vector<Vertex> path;

    // Initially populate each vertex's distance to infinity
	for (Vertex v : g.getVertices()) {
		distance[v] = std::numeric_limits<double>::infinity();
	}
    // Set src distance to 0 to give it priority
	distance[src] = 0;

    std::priority_queue<std::pair<double, Vertex>, vector<std::pair<double, Vertex>>, std::greater<std::pair<double, Vertex>>> q;
    q.push(std::make_pair(0, src));

	while (q.size()) {
		Vertex u = q.top().second;
		q.pop();
        
        if (u == dest) { break; } // If we've found a best path, stop the search
		for (Vertex v : g.getAdjacent(u)) {
            if (distance[u] + g.getEdgeWeight(u, v) < distance[v]) {
                distance[v] = distance[u] + g.getEdgeWeight(u, v);
                q.push(std::make_pair(distance[v], v));
                predecessor[v] = u;
            }
        }
	} 

    // Backtrack through predecessors to set the (inverted) shortest path
    Vertex temp = dest;
    while (predecessor.find(temp) != predecessor.end()) {
        path.push_back(temp);
        temp = predecessor[temp];
    }

    // If no path is found (given the source is NOT the destination), return empty path
    if (path.empty() && (src != dest)) {
        return path;
    }

    path.push_back(src);
    std::reverse(path.begin(), path.end());

    return path;
}