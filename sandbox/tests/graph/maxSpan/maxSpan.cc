// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#include "dataStructure/Graph.h"
#include "algorithm/MaximumSpan.h"

int main() {
    Graph graph(Graph::Initialization::StdIn);
    auto algo = algorithm::MaximumSpan(graph);
    algo.print();

    return 0;
}
