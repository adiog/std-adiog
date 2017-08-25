// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_DIJKSTRA_H
#define PROJECT_DIJKSTRA_H

#include <queue>
#include <utility>

#include "common/GraphTypes.h"
#include "../common/WeightedGraph.h"
namespace algorithm {

class Dijkstra {
  public:
    Dijkstra(WeightedGraph graph) : graph(graph) {}

    std::vector<uint> compute(Vertex start) {
        std::priority_queue<WeightedEdge, std::vector<WeightedEdge>,
                            WeightedEdgeCompare>
            heap;
        std::vector<bool> visited(graph.size(), false);

        std::vector<uint> dist(graph.size(), 0);
        std::vector<uint> prev(graph.size(), 0);

        heap.push(WeightedEdge{{start, start}, Weight{}});

        while (!heap.empty()) {
            WeightedEdge weightedEdge = heap.top();
            heap.pop();

            Edge currentEdge = weightedEdge.first;
            Vertex previousVertex = currentEdge.first;
            Vertex currentVertex = currentEdge.second;
            uint distanceToCurrent = weightedEdge.second;

            if (visited[currentVertex]) {
                continue;
            }

            visited[currentVertex] = true;

            dist[currentVertex] = distanceToCurrent;
            prev[currentVertex] = previousVertex;

            for (auto arrow : graph.getEdges()[currentVertex]) {
                heap.push(WeightedEdge{{currentVertex, arrow.first},
                                       arrow.second + distanceToCurrent});
            }
        }
        return dist;
    }

  private:
    WeightedGraph graph;
};
}

#endif  // PROJECT_DIJKSTRA_H
