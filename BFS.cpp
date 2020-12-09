#include "BFS.h"

#include <fstream>
#include <queue>
#include <map>

using namespace std;

vector<Vertex> BFS(Graph g, int directRoutes) {
    for (Vertex v : g.getVertices()) {
        pair<Vertex, int> p;
        p.first = v;
        p.second = 0; //0 means unvisited.
        visitedVertices.insert(p);
    }

    for (Edge e : g.getEdges()) {
        g.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }
    
    vector<Vertex> airports;
    
    for (Vertex v : g.getVertices()) {
        if (visitedVertices[v] == 0) {
            airports = BFS(g, v, directRoutes, airports);
        }
    }

    return airports;
}

vector<Vertex> BFS(Graph g, Vertex v, int directRoutes, vector<Vertex> & airports) {
    queue<Vertex> q;

    visitedVertices[v] = 1; //Setting vertex to visited.

    q.push(v);

    while (!q.empty()) {
        Vertex vert = q.front();
        q.pop();

        //BFS traverses the graph and prints the airports that have direct routes to at least n other airports.
        if (g.getAdjacent(vert).size() >= (unsigned long)directRoutes) {
            // cout << vert.label << ": " << vert.name << '\n';
            airports.push_back(vert);
        }

        for (Vertex w : g.getAdjacent(vert)) {
            if (visitedVertices[w] == 0) {
                g.setEdgeLabel(vert, w, "DISCOVERY");
                visitedVertices[w] = 1;
                q.push(w);
            }
            else if (g.getEdgeLabel(vert, w) == "UNEXPLORED") {
                g.setEdgeLabel(vert, w, "CROSS");
            }
        }
    }
    return airports;
}
