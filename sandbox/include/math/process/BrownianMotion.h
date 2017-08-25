// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_BROWNIANMOTION_H
#define CPPSTAT_BROWNIANMOTION_H

#include "common/MathTypes.h"
#include "math/distribution/Normal.h"
#include <xrange>

namespace math {
namespace process {

class BrownianMotion
{
public:
    BrownianMotion() = delete;

    static FunctionGraph getSamplePath(Real T, Real dt)
    {
        distribution::Normal normal(0.0, dt);
        FunctionGraph graph;
        Real acc = 0.0;
        for (Real t : xrange<Real>(0.0, T, dt))
        {
            graph.emplace_back(t, acc);
            acc += normal.sample();
        }
        return graph;
    }
};
}
}

#endif  // CPPSTAT_BROWNIANMOTION_H
