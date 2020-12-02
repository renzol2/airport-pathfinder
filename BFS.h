#pragma once

#include "graph.h"
#include "edge.h"


class BFS {
    public:
        /**
         * Constructor to read CSV of airports and routes into a graph of nodes and edges
         */
        BFS();

        BFS(Graph g);

        BFS(Graph g, Vertex v);
        
    private:
    
    Graph g_;

    map<Vertex, int> visitedVertices;
};
