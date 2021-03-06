//Copied from lab_ml
/**
 * @file edge.h
 * Definition and (minimal) implementation of an edge class.
 */

#pragma once

#include <string>
#include <limits.h>

using std::string;
using std::pair;
struct Vertex {
  Vertex() 
    : label(""), name(""), latitude(0), longitude(0) {}
  Vertex(const string& s) 
    : label(s), name(""), latitude(0), longitude(0) {}
  Vertex(const string& s, const string& setName, double setLat, double setLong) 
    : label(s), name(setName), latitude(setLat), longitude(setLong) {}
  
  string label;
  string name;
  double latitude;
  double longitude;
  
  bool operator==(const Vertex& other) const {
    return label == other.label 
      && latitude == other.latitude 
      && longitude == other.longitude;
  }

  bool operator!=(const Vertex& other) const {
    return !(*this == other);
  }

  bool operator<(const Vertex& other) const {
    return label < other.label;
  }

  bool empty() const { return label.empty(); }
};

// Override hash functionality for Vertex
// https://prateekvjoshi.com/2014/06/05/using-hash-function-in-c-for-user-defined-classes/
namespace std {
  template<>
  struct hash<Vertex> {
    size_t operator()(const Vertex& v) const {
      return hash<string>()(v.label);
    }
  };
}  // namespace std

/**
 * Represents an edge in a graph; used by the Graph class.
 *
 * @author Sean Massung
 * @date Spring 2012
 */
class Edge
{
  public:
    Vertex source; /**< The source of the edge **/
    Vertex dest; /**< The destination of the edge **/
    pair<double, double> sourceLatLong;
    pair<double, double> destLatLong;

    /**
     * Parameter constructor for unweighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     */
    Edge(Vertex u, Vertex v)
        : source(u), dest(v), label(""), weight(-1)
    { /* nothing */
    }

    /**
     * Parameter constructor for unweighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     * @param lbl - the edge label
     */
    Edge(Vertex u, Vertex v, string lbl)
        : source(u), dest(v), label(lbl), weight(-1)
    { /* nothing */
    }

    /**
     * Parameter constructor for weighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     * @param w - the weight of the edge
     * @param lbl - the edge label
     */
    Edge(Vertex u, Vertex v, double w, string lbl)
        : source(u), dest(v), label(lbl), weight(w)
    { /* nothing */
    }

    /**
     * Default constructor.
     */
    Edge() : source(""), dest(""), label(""), weight(-1)
    { /* nothing */
    }

    /**
     * Compares two Edges.
     * operator< is defined so Edges can be sorted with std::sort.
     * @param other - the edge to compare with
     * @return whether the current edge is less than the parameter
     */
    bool operator<(const Edge& other) const
    {
        return weight < other.weight;
    }

    /**
     * Gets edge label.
     */
    string getLabel() const
    {
        return this->label;
    }

    /**
     * Gets edge weight.
     */
    double getWeight() const
    {
        return this->weight;
    }

    /**
     * Compares two edges' source and dest.
     * @param other - the edge to compare with
     */
    bool operator==(Edge& other) const
    {
        if (this->source != other.source)
            return false;
        if (this->dest != other.dest)
            return false;
        return true;
    }
private:
    string label; /**< The edge label **/
    double weight; /**< The edge weight (if in a weighed graph) **/

};