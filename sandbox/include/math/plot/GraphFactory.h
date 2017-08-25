// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_GRAPHFACTORY_H
#define CPPSTAT_GRAPHFACTORY_H

#include <xrange.h>
#include "../../common/MathTypes.h"

namespace math {
namespace plot {

class GraphFactory {
  public:
    GraphFactory() = delete;

    template <typename Function>
    static FunctionGraph generate(Function function, Real xrange_min = -10.0,
                          Real xrange_max = 10.0, Real dx = 0.1) {
        FunctionGraph graph;
        for (Real x : xrange<Real>(xrange_min, xrange_max, dx)) {
            graph.push_back(Point(x, function(x)));
        }
        return graph;
    }
};
}
}

#endif  // CPPSTAT_GRAPHFACTORY_H
