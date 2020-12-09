#include "BFS.h"

#include <fstream>
#include <queue>
#include <map>

using namespace std;

void BFS(Graph g, int directRoutes) {
    for (Vertex v : g.getVertices()) {
        pair<Vertex, int> p;
        p.first = v;
        p.second = 0; //0 means unvisited.
        visitedVertices.insert(p);
    }

    for (Edge e : g.getEdges()) {
        g.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }

    for (Vertex v : g.getVertices()) {
        if (visitedVertices[v] == 0) {
            BFS(g, v, directRoutes);
        }
    }
}

void BFS(Graph g, Vertex v, int directRoutes) {
    queue<Vertex> q;

    visitedVertices[v] = 1; //Setting vertex to visited.

    q.push(v);

    while (!q.empty()) {
        Vertex vert = q.front();
        q.pop();

        //BFS traverses the graph and prints the airports that have direct routes to at least n other airports.
        if (g.getAdjacent(vert).size() >= (unsigned long)directRoutes) {
            cout << vert.label << ": " << vert.name << '\n';
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
}
