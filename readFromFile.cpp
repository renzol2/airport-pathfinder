#include "readFromFile.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <cfloat>

using std::fstream;
using std::ios;
using std::stringstream;
using std::unordered_map;
using std::pair;

FileReader::FileReader() {}

Graph FileReader::getAirportData() {
  Graph g(true, true);

  //Read in the airports as vertices of the graph
    fstream fin;

    fin.open("airports.dat.txt", ios::in);

    int airportsLines = 7698;
    string airportLine;

    //The 14 entries in each row of airports.dat.txt
    string airportID, name, city, country, IATA, ICAO, latitude, longitude, altitude, timezone, DST, tz, type, source_airport;

    // Map to ensure Vertex keys are added with other data
    unordered_map<string, Vertex> idVertexMap;

    while (airportsLines > 0) {
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
        getline(fin, source_airport);

        //Creates a vertex with label set to the airport's ID
        Vertex v(airportID, name, std::stod(latitude), std::stod(longitude));
        g.insertVertex(v);
        idVertexMap[airportID] = v;
        
        airportsLines--;
    }

    //Read in the routes as edges between vertices
    fstream fin2; //Note: not sure this it's necessary to declare another fstream for another file. Doing it to be safe.

    fin2.open("routes.dat.txt", ios::in);

    int routesLines = 67663;
    string routeLine;

    //The nine entries in each row of routes.dat.txt
    string airline, airlineID, source_route, sourceID, destination, destinationID, codeshare, stops, equipment;

    while (routesLines > 0) {
        getline(fin2, routeLine);

        stringstream s(routeLine);

        getline(fin2, airline, ',');
        getline(fin2, airlineID, ','); 
        getline(fin2, source_route, ',');
        getline(fin2, sourceID, ','); //Use for source vertex of an edge;
        getline(fin2, destination, ',');
        getline(fin2, destinationID, ','); //Use for destination vertex of an edge;
        getline(fin2, codeshare, ',');
        getline(fin2, stops, ',');
        getline(fin2, equipment);
        
        // Edge cannot exist if either source or dest wasn't found
        if (idVertexMap.find(sourceID) == idVertexMap.end() 
          || idVertexMap.find(destinationID) == idVertexMap.end()) {
          routesLines--;
          continue;
        }

        // If a route already exists between the airports, adds 1 to the weight. 
        // Otherwise it creates an edge.
        Vertex src = idVertexMap.at(sourceID);
        Vertex dest = idVertexMap.at(destinationID);
        if (g.edgeExists(src, dest)) {
            // 1 / ( routes + 1 )
            g.setEdgeWeight(src, dest, 1 / ((1 / g.getEdgeWeight(src, dest)) + 1));
        } else {
            g.insertEdge(src, dest);
            g.setEdgeWeight(src, dest, 1);
        }

        routesLines--;
    }

  return g;
}