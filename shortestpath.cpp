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

	std::map<Vertex, double> distance;
	std::map<Vertex, Vertex> predecessor;

	for (Vertex v : g.getVertices()) {
		// distance[v] = std::numeric_limits<double>::infinity();	// maybe this doesnt work
        distance[v] = 1000;
	}
	distance[src] = 0;
    // distance["b"] = 4; // test

    std::priority_queue<Vertex, vector<Vertex>, orderByDist> q((orderByDist(distance)));

    for (Vertex v : g.getVertices()) {
        q.push(v);
    }
    
    // distance[src] = 3000;

    // TEST
    // while (q.size()) {
    //     std::cout << q.top() << std::endl;
    //     q.pop();
    // }

	while (q.size()) { // Note: keep an eye on heapify for minheap...
		Vertex u = q.top();
		q.pop();
        // std::cout << "top: " << u << std::endl;
		for (Vertex v : g.getAdjacent(u)) {
            // std::cout << "vertex: " << v << " edge weight: " << g.getEdgeWeight(u, v) << " sum of dist: " << distance[u] + (double)g.getEdgeWeight(u, v) << std::endl;
            if (distance[u] + (double)g.getEdgeWeight(u, v) < distance[v]) {
                distance[v] = distance[u] + (double)g.getEdgeWeight(u, v);
                predecessor[v] = u;
            }
        }
	} // can optionally kill the loop as soon as u = destination if (u == dest) { break; }

    // for (auto j : distance) {
    //     std::cout << "fisrt: " << j.first << " second: " << j.second << std::endl;
    // }

    Vertex temp = dest;
    while (predecessor.find(temp) != predecessor.end()) {
        path.push_back(temp);
        temp = predecessor[temp];
    }

    path.push_back(src);
    std::reverse(path.begin(), path.end());

    return path;
}

// void buildHeap(const std::vector<Vertex>& vertices,
// 			   std::priority_queue<Vertex, vector<Vertex>, std::greater<Vertex>>& q) {
// }