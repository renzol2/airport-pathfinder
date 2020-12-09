#pragma once

#include "graph.h"
#include "edge.h"

#include <map>

vector<Vertex> BFS(Graph g, int directRoutes);

vector<Vertex> BFS(Graph g, Vertex v, int directRoutes, vector<Vertex> & airports);

static std::map<Vertex, int> visitedVertices;

