#ifndef PROJECT_DFS_H
#define PROJECT_DFS_H

namespace algorithm {

class DFS {
  public:
    using VisitedMap = std::vector<bool>;

    DFS(Graph &graph) : graph(graph) {}

    template <typename Acc, typename Arg, typename EnterFunction,
              typename NextArgFunction, typename CleanUpFunction>
    void doDFS(VisitedMap &visitedMap, Vertex currentVertex, Acc &acc, Arg arg,
               const EnterFunction &enterFunction,
               const CleanUpFunction &cleanUpFunction,
               NextArgFunction nextArgFunction) {
        visitedMap[currentVertex] = true;
        if (!enterFunction(currentVertex, acc, arg)) {
            return;
        }
        for (auto nextVertex : graph.getEdges()[currentVertex]) {
            if (!visitedMap[nextVertex]) {
                Arg nextArg =
                    nextArgFunction(currentVertex, nextVertex, acc, arg);
                doDFS(visitedMap, nextVertex, acc, nextArg, enterFunction,
                      cleanUpFunction, nextArgFunction);
            }
        }
        cleanUpFunction(currentVertex, acc, arg);
    }

    Path findPath(Vertex source, Vertex target) {
        using Acc = std::pair<Path, bool>;
        using Arg = Vertex;
        Acc acc{{}, false};
        auto enterFunction = [](Vertex &vertex, Acc &acc, Arg arg) {
            if (!acc.second) {
                acc.first.push_back(vertex);
                if (arg == vertex) {
                    acc.second = true;
                }
                std::cout << acc.first << " " << acc.second << std::endl;
            }
            return (!acc.second);
        };
        auto cleanUpFunction = [](Vertex &vertex, Acc &acc, Arg arg) {
            if (!acc.second) {
                acc.first.resize(acc.first.size() - 1);
            }
        };
        auto nextArgFunction = [](Vertex &vertex, Vertex &nextVertex, Acc &acc,
                                  Arg arg) { return arg; };
        auto visitedMap = VisitedMap(graph.size());
        doDFS(visitedMap, source, acc, target, enterFunction, cleanUpFunction,
              nextArgFunction);
        return acc.first;
    }

    Vertex mostDistantVertex(Vertex source) {
        using Acc = std::pair<Vertex, uint>;
        using Arg = uint;
        Acc acc{source, 0};
        auto enterFunction = [](Vertex &vertex, Acc &acc, Arg arg) {
            if (arg > acc.second) {
                acc.second = arg;
                acc.first = vertex;
            }
            return true;
        };
        auto cleanUpFunction = [](Vertex &vertex, Acc &acc, Arg arg) {};
        auto nextArgFunction = [](Vertex &vertex, Vertex &nextVertex, Acc &acc,
                                  Arg arg) { return arg + 1; };
        auto visitedMap = VisitedMap(graph.size());
        doDFS(visitedMap, source, acc, 0, enterFunction, cleanUpFunction,
              nextArgFunction);
        return acc.first;
    }

  private:
    Graph graph;
};
}

#endif  // PROJECT_DFS_H


