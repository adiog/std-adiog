// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_GRAPHTYPES_H
#define PROJECT_GRAPHTYPES_H

#include <vector>
#include  <utility>

using Vertex = uint;
using VertexSet = std::vector<Vertex>;

using Weight = uint;

using Edge = std::pair<Vertex, Vertex>;
using WeightedEdge = std::pair<Edge, Weight>;
using Arrow = std::pair<uint, Weight>;

using Path = std::vector<Vertex>;

class WeightedEdgeCompare {
  public:
    bool operator()(const WeightedEdge &we1, const WeightedEdge &we2) {
        return we1.second > we2.second;
    }
};

std::ostream &operator<<(std::ostream &os, const std::vector<Vertex> &t) {
    os << "[";
    for (const auto &i : t) {
        os << (int)(i+1) << ";";
    }
    os << "]";

    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &t) {
    os << "[";
    for (const auto &i : t) {
        os << i << ";";
    }
    os << "]";

    return os;
}

template<typename ForwardIt>
void print(ForwardIt begin, ForwardIt end) {
    if (begin < end) {
        std::cout << *begin << ";";
        print(begin+1, end);
    } else {
        std::cout << std::endl;
    }
}

#endif  // PROJECT_GRAPHTYPES_H
