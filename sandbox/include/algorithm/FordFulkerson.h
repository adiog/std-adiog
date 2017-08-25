// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_FORDFULKERSON_H
#define PROJECT_FORDFULKERSON_H

#include <memory>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename UnorderedMap, typename Key, typename Item>
void insert_or_update(UnorderedMap &um, const Key &key, Item &&i) {
    auto it = um.find(key);
    if (it != um.end()) {
        if (i.second != 0) {
            um.insert(it,
                      std::pair<Key, Item>(key, i));  // std::forward<Item>(i));
        }
    } else {
        um[key] = std::forward<Item>(i);
    }
}

class Graph {
  public:
    Graph(int n) : s(n) { internal.resize(n); }

    void addEdge(int a, int b, int w) {
        insert_or_update(internal[a], b, std::pair<int, int>(0, w));
        insert_or_update(internal[b], a, std::pair<int, int>(0, 0));
    }

    void read_stdin(void) {
        int m;
        std::cin >> s >> m;
        internal.resize(s);
        while (m--) {
            int a;
            int b;
            int w;
            std::cin >> a >> b >> w;
            insert_or_update(internal[a], b, std::pair<int, int>(0, w));
            insert_or_update(internal[b], a, std::pair<int, int>(0, 0));
        }
    }

    void setSource(int source) { this->source = source; }

    void setTarget(int target) { this->target = target; }

    int getSource(void) { return this->source; }

    int getTarget(void) { return this->target; }

    int size() { return s; }
    int source;
    int target;
    int s;
    // internal[vertex_from][vertex_to] = (flow, capacitity);
    std::vector<std::unordered_map<int, std::pair<int, int>>> internal;
};

std::ostream &operator<<(std::ostream &os, const Graph &graph) {
    os << graph.internal << std::endl;
    return os;
}

namespace algorithm {

class FordFulkerson {
  public:
    FordFulkerson(Graph &graph) : graph(graph) {}

    std::vector<int> getAugmentedPath() {
        std::vector<int> parent(graph.size(), -1);
        std::queue<int> queue;

        queue.push(graph.getSource());

        while (!queue.empty()) {
            auto next = queue.front();
            queue.pop();

            if (next == graph.getTarget()) {
                std::stack<int> stack;
                while (next != graph.getSource()) {
                    std::cout << next << " " << parent[next] << std::endl;
                    stack.push(next);
                    next = parent[next];
                }
                std::vector<int> result;
                //                    result.push_back(graph.getSource();
                while (!stack.empty()) {
                    result.push_back(stack.top());
                    stack.pop();
                }
                return result;
            } else {
                for (const auto &edge : graph.internal[next]) {
                    if ((edge.second.second - edge.second.first > 0) &&
                        (parent[edge.first] == -1)) {
                        queue.push(edge.first);
                        parent[edge.first] = next;
                    }
                }
            }
        }

        return std::vector<int>();
    }

    int maxFlow() {
        int result = 0;

        while (true) {
            auto path = getAugmentedPath();
            if (path.empty()) {
                break;
            }

            std::cout << "aug " << path << std::endl;

            unsigned int flow = -1;

            int v = graph.getSource();
            for (auto nv : path) {
                int cf =
                    graph.internal[v][nv].second - graph.internal[v][nv].first;
                if (cf < flow) {
                    flow = cf;
                }
                v = nv;
            }

            std::cout << flow << std::endl;

            v = graph.getSource();
            for (auto nv : path) {
                graph.internal[v][nv].first += flow;
                graph.internal[nv][v].first -= flow;
                v = nv;
            }

            std::cout << graph << std::endl;

            result += flow;
        }

        return result;
    }

  private:
    Graph &graph;
};
}

#endif  // PROJECT_FORDFULKERSON_H
