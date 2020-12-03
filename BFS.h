#pragma once

#include "graph.h"
#include "edge.h"

#include <map>

void BFS(Graph g);

void BFS(Graph g, Vertex v);

static std::map<Vertex, int> visitedVertices;

