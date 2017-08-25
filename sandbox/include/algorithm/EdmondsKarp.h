// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_EDMUNDKARP_H
#define PROJECT_EDMUNDKARP_H

template <typename Weight = uint>
class EdmondsKarp {
  public:
    EdmondsKarp(OrientedWeightedGraph<Weight> &graph, Vertex source,
                Vertex target)
        : graph(graph), source(source), target(target) {}

    OrientedWeightedGraph<Weight> graph;
    Vertex source;
    Vertex target;
};

#endif  // PROJECT_EDMUNDKARP_H
