#pragma once

#include "graph.h"
#include "edge.h"

#include <map>

void BFS(Graph g, int directRoutes);

void BFS(Graph g, Vertex v, int directRoutes);

static std::map<Vertex, int> visitedVertices;

