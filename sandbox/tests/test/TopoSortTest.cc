#include <gtest/gtest.h>
#include <queue>
#include <iostream>
#include <common/StdTypes.h>
class Graph
{
public:
    Graph() = default;

    template<typename InputStream>
            void read(InputStream && inputStream)
    {
        int maxSize;
        inputStream >> maxSize;
        internalRepresentation.assign(maxSize, std::vector<int>{});
        for(int v = 0; v < maxSize; v++)
        {
            int edges;
            inputStream >> edges;
            for(int edge = 0; edge < edges; edge++) {
                int nextVertex;
                inputStream >> nextVertex;
                internalRepresentation[v].push_back(nextVertex);
            }
        }

        std::cout << internalRepresentation << std::endl;
    }

    int size() const {
        return internalRepresentation.size();
    }

    const std::vector<std::vector<int>>& getEdges() const {
        return internalRepresentation;
    };

    Graph reversed() const {
        Graph reversedGraph;
        reversedGraph.internalRepresentation.resize(this->size());
        for(int v1 = 0; v1 < internalRepresentation.size(); v1++){
            for(int v2index = 0; v2index < internalRepresentation[v1].size(); v2index++)
            {
                int v2 = internalRepresentation[v1][v2index];
                reversedGraph.internalRepresentation[v2].push_back(v1);
            }
        }

        return reversedGraph;
    }

private:
    std::vector<std::vector<int>> internalRepresentation;
};

class TopoSortCycle : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class TopoSort
{
public:
    static std::vector<int> sort(const Graph &graph)
    {
        std::vector<int> sortedVertices;
        std::vector<int> incomingCount(graph.size());
        auto reversedGraph = graph.reversed();

        std::cout << reversedGraph.getEdges() << std::endl;

        for(int v2 = 0; v2 < graph.size(); v2++) {
            incomingCount[v2] = static_cast<int>(reversedGraph.getEdges()[v2].size());
        }

        std::cout << incomingCount << std::endl;

        std::queue<int> verticesToProcess;
        int enumerator = 0;
        for_each(incomingCount.begin(), incomingCount.end(), [&verticesToProcess, &enumerator](int count) {
            if(count == 0){
                verticesToProcess.push(enumerator);
            }
            enumerator++;
        });

        std::cout << verticesToProcess << std::endl;

        int verticesNotProcessed = graph.size();
        while(!verticesToProcess.empty()){
            verticesNotProcessed--;
            int v1 = verticesToProcess.front();
            verticesToProcess.pop();
            sortedVertices.push_back(v1);
            for_each(graph.getEdges()[v1].begin(), graph.getEdges()[v1].end(), [&verticesToProcess, &incomingCount](int v2){
                incomingCount[v2]--;
                if (incomingCount[v2] == 0){
                    verticesToProcess.push(v2);
                }
            });
            std::cout << incomingCount << std::endl;
        }

        if (verticesNotProcessed>0) {
            throw TopoSortCycle("");
        }

        return sortedVertices;
    }
};

TEST(TopoSort, TopoSortTest)
{
    std::istringstream is("4 1 2 2 2 3 0 1 2");
    Graph graph;
    graph.read(is);
    auto sorted = TopoSort::sort(graph);
    std::cout << sorted << std::endl;
}

