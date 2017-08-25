#include <io>
#include <adiog/algorithm/FordFulkerson.h>

int main() {
    Graph graph;
    graph.read_stdin();
    
    int s;
    int t;
    std::cin >> s >> t;
    graph.setSource(s);
    graph.setTarget(t);
    auto algo = algorithm::FordFulkerson(graph);

    std::cout << algo.maxFlow() << std::endl;

    return 0;
}
