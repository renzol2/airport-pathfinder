#pragma once

#include "graph.h"
#include "edge.h"


class BFS {
    public:
        /**
         * Constructor to read CSV of airports and routes into a graph of nodes and edges
         */
        BFS();

        /**
         * This function uses the BFS algorithm to determine if a destination airport
         * is within a certain number of edges (routes) from a source airport.
         * 
         * @param sourceID The unique OpenFlights identifier for the source airport
         * @param destinationID The unique OpenFlights identifier for the destination airport
         * @param edgeLimit The limit on the number of edges that the BFS will search away from the source
         * 
         */
        bool findAirport(int sourceID, int destinationID, int edgeLimit);
        
    private:
    
    Graph g_;
};
