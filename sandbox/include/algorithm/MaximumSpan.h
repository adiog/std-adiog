// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_MAXIMUMSPANNINGTREE_H
#define PROJECT_MAXIMUMSPANNINGTREE_H

#include "DFS.h"

namespace algorithm {
    class MaximumSpan {
    public:
        MaximumSpan(Graph &graph) : graph(graph) {}

        void print() {
            auto algo = algorithm::DFS(graph);
            Vertex start = algo.mostDistantVertex(0);
            Vertex end = algo.mostDistantVertex(start);
            std::cout << start << " " << end << std::endl;
            auto altSt = algo.mostDistantVertex(0);
            std::cout << altSt << " " << algo.mostDistantVertex(altSt) << std::endl;
            std::cout << algo.findPath(start, end);
        }

    private:
        Graph graph;
    };
}

/*
void printPath(int cv, int dv) {
    path.push(cv);
    if (cv == dv) {
        auto pathCopy = path;
        while (!pathCopy.empty()) {
            std::cout << (pathCopy.top() + 1) << " ";
            pathCopy.pop();
        }
        std::cout << std::endl;
    }
    for (auto va : edge[cv]) {
        if (visited[va] == 0) {
            visited[va] = 1;
            printPath(va, dv);
        }
    }
    path.pop();
}

void maxSpan() {
    if (v == 0) {
        std::cout << "empty graph" << std::endl;
        return;
    }
    int startV = 0;
    visited[startV] = 1;
    maxD = 0;

    mostDistant(startV, 0);
    std::fill(visited.begin(), visited.end(), 0);

    startV = maxV;
    visited[startV] = 1;
    maxD = 0;

    mostDistant(startV, 0);
    std::fill(visited.begin(), visited.end(), 0);

    printPath(startV, maxV);
}
*/

#endif //PROJECT_MAXIMUMSPANNINGTREE_H
