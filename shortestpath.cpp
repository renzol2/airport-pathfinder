#include "shortestpath.h"

#include <map>
#include <queue>

// TODO: fix graph stuff to return double....
struct orderByDist {
    orderByDist(std::map<Vertex, double> input) {
        this->distance = input;
    } 
	bool operator()(Vertex const& a, Vertex const& b) {
		return distance[a] > distance[b];
	}
    std::map<Vertex, double> distance;
};

vector<Vertex> getShortestPath(const Graph & g, const Vertex & src, const Vertex & dest) {

  std::vector<Vertex> path;

  if (src == dest) {
    return { src };
  }

	std::map<Vertex, double> distance;
	std::map<Vertex, Vertex> predecessor;

	for (const Vertex& v : g.getVertices()) {
		distance[v] = std::numeric_limits<double>::infinity();	// maybe this doesnt work
	}
	distance[src] = 0;

    std::priority_queue<Vertex, vector<Vertex>, orderByDist> q((orderByDist(distance)));

    for (Vertex v : g.getVertices()) {
        q.push(v);
    }

	while (q.size()) {
		Vertex u = q.top();
		q.pop();
        // if (u == dest) { break; }
		for (const Vertex& v : g.getAdjacent(u)) {
            if (distance[u] + (double)g.getEdgeWeight(u, v) < distance[v]) {
                distance[v] = distance[u] + (double)g.getEdgeWeight(u, v);
                predecessor[v] = u;
            }
        }
	} 

    Vertex temp = dest;
    while (predecessor.find(temp) != predecessor.end()) {
        path.push_back(temp);
        temp = predecessor[temp];
    }

    // If no path is found (given the source is NOT the destination), return empty path
    if (path.empty()) {
        return path;
    }

    path.push_back(src);
    std::reverse(path.begin(), path.end());

    return path;
}
