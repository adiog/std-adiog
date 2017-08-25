// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_BFS_H
#define PROJECT_BFS_H

#include <vector>
#include <queue>

namespace algorithm {

    class BFS {
    public:
        using VisitedMap = std::vector<bool>;

        BFS(Graph &graph) : graph(graph) {}

        template<typename ProcessEdge>
        void doBFS(Vertex source, ProcessEdge processEdge) {
            VisitedMap visitedMap(graph.size(), false);
            std::queue<std::pair<Vertex, Vertex>> queue;
            queue.emplace(source,source);
            visitedMap[source] = true;
            while(!queue.empty()) {
                auto edge = queue.front();
                queue.pop();
                processEdge(edge);
                auto currentVertex = edge.second;
                for(auto nextVertex : graph.getEdges()[currentVertex]) {
                    if (!visitedMap[nextVertex]) {
                        queue.emplace(currentVertex, nextVertex);
                    }
                }
            }
        }

    private:
        Graph graph;
    };
}

#endif //PROJECT_BFS_H
