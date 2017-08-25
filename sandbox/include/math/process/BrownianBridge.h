// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_BROWNIANMOTION_H
#define CPPSTAT_BROWNIANMOTION_H

#include "common/MathTypes.h"
#include "math/distribution/Normal.h"
#include <xrange>

namespace math {
namespace process {

class BrownianBridge
{
public:
    BrownianBridge() = delete;

    static FunctionGraph getSamplePath(Real T, Real dt)
    {
        distribution::Normal normal(0.0, dt);
        FunctionGraph graph;
        Real acc = 0.0;
        Real epsilon = 0.00001;
        for (Real t : xrange<Real>(0.0, T+epsilon, dt))
        {
            graph.emplace_back(t, acc);
            acc += normal.sample();
            std::cout << graph.back().first << " " << graph.back().second << std::endl;
        }
        auto last = graph.back().second;
        for (int i : xrange<int>(graph.size()))
        {
            graph[i] = {graph[i].first, graph[i].second - last * ((static_cast<Real>(i)) / static_cast<Real>(graph.size() - 1))};
            std::cout << graph[i].first << " " << graph[i].second << std::endl;
        }
        return graph;
    }
};
}
}

#endif  // CPPSTAT_BROWNIANMOTION_H
