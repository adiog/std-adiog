// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_ORIENTEDWEIGHTEDGRAPH_H
#define PROJECT_ORIENTEDWEIGHTEDGRAPH_H

template<typename Weight = uint>
class OrientedWeightedGraph {
public:
    using Vertex = uint;
    using Edge = std::pair<Vertex, Weight>;
    using Edges = std::vector<std::vector<Edge>>;

    enum class Initialization { StdIn };

    OrientedWeightedGraph(Initialization initialization) {
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
            edge[v1].emplace_back(v2, w);
        }
    }

    Edges& getEdges(void) {
        return edges;
    }

    uint size() {
        return v;
    }

private:
    uint v;
    uint e;
    Edges edges;
};

#endif // PROJECT_ORIENTEDWEIGHTEDGRAPH_H
