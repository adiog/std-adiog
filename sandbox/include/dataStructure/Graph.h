// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_GRAPH_H
#define PROJECT_GRAPH_H

#include "common/GraphTypes.h"
#include <vector>

class Graph {
public:
    enum class Initialization { StdIn };
    using Edges = std::vector<std::vector<Vertex>>;

    Graph(Initialization initialization) {
        //if (initialization != Initialization::StdIn) {
        //    throw("Not supported initialization type.");
        //}
        std::cin >> v;
        std::cin >> e;
        edges = Edges(v);
        Vertex v1;
        Vertex v2;
        size_t ce = e;
        while (ce--) {
            std::cin >> v1 >> v2;
            --v1;
            --v2;
            edges[v1].push_back(v2);
            edges[v2].push_back(v1);
        }
    }

    Edges& getEdges(void) { return edges; }

    uint size() { return v; }

private:
    size_t v;
    size_t e;
    Edges edges;
};

#endif // PROJECT_GRAPH_H
