// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_WEIGHTEDGRAPH_H
#define PROJECT_WEIGHTEDGRAPH_H

#include <xrange>
#include "GraphTypes.h"

template <typename Weight = uint>
class WeightedGraphParam {
  public:
    using Vertex = uint;
    using Edge = std::pair<Vertex, Weight>;
    using Edges = std::vector<std::vector<Edge>>;

    enum class Initialization { StdIn };

    WeightedGraphParam(Initialization initialization) {
        if (initialization != Initialization::StdIn) {
            throw("Not supported initialization type.");
        }
        std::cin >> v;
        std::cin >> e;

        edges = Edges(v);
        Vertex v1;
        Vertex v2;
        Weight w;
        uint ce = e;
        while (ce-- > 0U) {
            std::cin >> v1 >> v2 >> w;
            --v1;
            --v2;
            edges[v1].emplace_back(v2, w);
            edges[v2].emplace_back(v1, w);
        }
    }

    xrange getVertex(void) { return xrange(v); }

    Edges& getEdges(void) { return edges; }

    uint size() { return v; }

    void insert(WeightedEdge weightedEdge) {
        Edge edge = weightedEdge.first;
        Weight weight = weightedEdge.second;
        edges[edge.first].emplace_back(edge.second, weight);
        edges[edge.second].emplace_back(edge.first, weight);
    }

  private:
    uint v;
    uint e;
    Edges edges;
};

using WeightedGraph = WeightedGraphParam<>;

#endif  // PROJECT_WEIGHTEDGRAPH_H
