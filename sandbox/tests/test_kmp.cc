// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <iostream>
//#include "common/Graph.h"
#include "algorithm/MergeSort.h"
//#include "common/WeightedGraph.h"
//#include "algorithm/Dijkstra.h"
//#include "algorithm/MaximumSpan.h"
#include "algorithm/KMP.h"
//#include "algorithm/MinimumSpanningTree.h"
//#include "dataStructure/RangeTree.h"
#include <include/range>
int main() {
/*
    WeightedGraph graph(WeightedGraph::Initialization::StdIn);
    auto algo = algorithm::Dijkstra(graph);
    std::cout << algo.compute(0U);
*/

    /*
    WeightedGraph graph(WeightedGraph::Initialization::StdIn);
    auto algo = algorithm::MinimumSpanningTree(graph);
    algo.print();
*/

    /*
    Graph graph(Graph::Initialization::StdIn);
    auto algo = algorithm::MaximumSpan(graph);
    algo.print();
*/

  
  
    std::string pattern("AABAADUPAABAA");
    for(auto a : range(pattern.begin(), pattern.end())) {
      std::cout << ">" << a << "<";
    }
    std::cout << std::endl;
    return 0;
    
    std::string text("AABABABBABAABAADUPAABAABBABBAA");
    std::cout << "start" << std::endl;
    std::cout << algorithm::KMP::getPrefixTable(std::string("AABAADUPAABAA")) << std::endl;
    int pos = algorithm::KMP::find(pattern, text);
    while(pos-- > 0)
        std::cout << " ";
    std::cout << pattern << std::endl;
    std::cout << text << std::endl;

    std::cout << "done" << std::endl;
    return 0;
}

