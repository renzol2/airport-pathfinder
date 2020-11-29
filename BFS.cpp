#include "BFS.h"

#include <fstream>

using namespace std;

BFS::BFS() : g_(true, true) {
    //Read in the airports as vertices of the graph
    fstream fin;

    fin.open("airports.dat.txt", ios::in);

    int airportsLines = 7698;
    string airportLine;

    //The 14 entries in each row of airports.dat.txt
    string airportID, name, city, country, IATA, ICAO, latitude, longitude, altitude, timezone, DST, tz, type, source;

    while (airportsLines >= 0) {
        getline(fin, airportLine);

        stringstream s(airportLine);

        getline(fin, airportID, ','); //Use for the name of the vertex. Each unique number represents an airport.
        getline(fin, name, ',');
        getline(fin, city, ',');
        getline(fin, country, ',');
        getline(fin, IATA, ',');
        getline(fin, ICAO, ',');
        getline(fin, latitude, ',');
        getline(fin, longitude, ',');
        getline(fin, altitude, ',');
        getline(fin, timezone, ',');
        getline(fin, DST, ',');
        getline(fin, tz, ',');
        getline(fin, type, ',');
        getline(fin, source);

        g_.insertVertex(airportID); //Creates a vertex with label set to the airport's ID
        
        airportsLines--;
    }

    
    //Read in the routes as edges between vertices
    fstream fin2; //Note: not sure this it's necessary to declare another fstream for another file. Doing it to be safe.

    fin2.open("routes.dat.txt", ios::in);

    int routesLines = 67663;
    string routeLine;

    //The nine entries in each row of routes.dat.txt
    string airline, airlineID, source, sourceID, destination, destinationID, codeshare, stops, equipment;

    while (routesLines >= 0) {
        getline(fin2, routeLine);

        stringstream s(routeLine);

        getline(fin2, airline, ',');
        getline(fin2, airlineID, ','); 
        getline(fin2, source, ',');
        getline(fin2, sourceID, ','); //Use for source node of an edge;
        getline(fin2, destination, ',');
        getline(fin2, destinationID, ','); //Use for destination node of an edge;
        getline(fin2, codeshare, ',');
        getline(fin2, stops, ',');
        getline(fin2, equipment);
        
        //If a route already exists between the airports, adds 1 to the weight. Otherwise it creates an edge.
        if (g_.edgeExists(sourceID, destinationID)) {
            g_.setEdgeWeight(sourceID, destinationID, g_.getEdgeWeight(sourceID, destinationID) + 1);
        } else {
            g_.insertEdge(sourceID, destinationID);
            g_.setEdgeWeight(sourceID, destinationID, 1);
        }
        
        routesLines--;
    }
}

bool BFS::findAirport(int sourceID, int destinationID, int edgeLimit) {
    return false;
}