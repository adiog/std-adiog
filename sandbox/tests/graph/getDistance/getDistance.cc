// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <iostream>
#include "common/GraphTypes.h"
#include "dataStructure/Graph.h"
#include "algorithm/BFS.h"

int main() {
    Graph graph(Graph::Initialization::StdIn);
    std::vector<int> distance(graph.size(), -1);
    algorithm::BFS bfs(graph);


    const int MAGIC_LENGTH = 6;
    Vertex source;
    std::cin >> source;
    distance[source] = -MAGIC_LENGTH;
    bfs.doBFS(source, [&distance](std::pair<Vertex, Vertex> edge) {
        distance[edge.second] = distance[edge.first] + MAGIC_LENGTH;
    });
    for(auto d : distance) {
        if (d != 0) {
            std::cout << d << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}