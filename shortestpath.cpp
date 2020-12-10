// Written using the following sources:
// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/

#include "shortestpath.h"

#include <map>
#include <queue>

// struct orderByDist {
//     orderByDist(std::map<Vertex, double> input) {
//         this->distance = input;
//     } 
// 	bool operator()(Vertex const& a, Vertex const& b) {
// 		return distance[a] > distance[b];
// 	}
//     std::map<Vertex, double> distance;
// };

vector<Vertex> getShortestPath(const Graph & g, const Vertex & src, const Vertex & dest) {

    std::vector<Vertex> path;

	std::map<Vertex, double> distance;
	std::map<Vertex, Vertex> predecessor;

	for (Vertex v : g.getVertices()) {
		distance[v] = std::numeric_limits<double>::infinity();	// maybe this doesnt work
	}
	distance[src] = 0;

    std::priority_queue<std::pair<double, Vertex>, vector<std::pair<double, Vertex>>, std::greater<std::pair<double, Vertex>>> q;

    // for (Vertex v : g.getVertices()) {
    //     q.push(v);
    // }

    q.push(std::make_pair(0, src));

	while (q.size()) {
		Vertex u = q.top().second;
		q.pop();
        
        if (u == dest) { break; }
		for (Vertex v : g.getAdjacent(u)) {
            if (distance[u] + g.getEdgeWeight(u, v) < distance[v]) {
                distance[v] = distance[u] + g.getEdgeWeight(u, v);
                q.push(std::make_pair(distance[v], v));
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
    if (path.empty() && (src != dest)) {
        return path;
    }

    path.push_back(src);
    std::reverse(path.begin(), path.end());

    return path;
}