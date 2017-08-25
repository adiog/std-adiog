// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_GRAPHFACTORY_H
#define CPPSTAT_GRAPHFACTORY_H

#include "common/MathTypes.h"
#include "xrange"

namespace estimator {

using EstimateGraph = std::function<FunctionGraph(Yield)>;

class GraphFactory {
  public:
    GraphFactory() = delete;

    template <typename Function>
    static FunctionGraph generate(Function function) {
        FunctionGraph graph;
        for (double x : xrange<double>(Config::xrange_min, Config::xrange_max,
                                       Config::dx)) {
            graph.push_back(std::pair<double, double>(x, function(x)));
        }
        return graph;
    }

    static FunctionGraph estimateCDF(Yield yield) {
        std::vector<double> points;
        for (auto i : xrange<>(Config::N)) {
            points.push_back(yield());
        }
        std::sort(points.begin(), points.end());

        FunctionGraph graph;
        double diff = 1.0 / Config::N;
        double acc = diff;
        graph.emplace_back(Config::xrange_min, 0.0);
        for (auto p : points) {
            if ((!graph.empty()) && (p == graph.back().first)) {
                graph.back().second = acc;
            } else {
                graph.emplace_back(p, acc);
            }
            acc += diff;
        }
        graph.emplace_back(Config::xrange_max, 1.0);

        return graph;
    }

    static FunctionGraph estimatePDF(Yield yield) {
        std::vector<double> points;
        for (auto i : xrange<>(Config::N)) {
            points.push_back(yield());
        }
        std::sort(points.begin(), points.end());

        FunctionGraph graph;
        double diff = 1.0 / Config::N / Config::pdfEstimationStep;
        auto p = points.begin();
        for (auto x : xrange<double>(Config::xrange_min, Config::xrange_max,
                                     Config::pdfEstimationStep)) {
            double acc = 0.0;
            while ((p != points.end()) && (*p < x)) {
                acc += diff;
                p++;
            }
            graph.emplace_back(x, acc);
        }

        return graph;
    }

    static FunctionGraph estimateDiscretePDF(Yield yield) {
        std::vector<double> points;
        for (auto i : xrange<>(Config::N)) {
            points.push_back(yield());
        }
        std::sort(points.begin(), points.end());

        FunctionGraph graph;
        double diff = 1.0 / Config::N;
        auto p = points.begin();
        for (auto x : xrange<int>(static_cast<int>(Config::xrange_min),
                                  static_cast<int>(Config::xrange_max))) {
            double acc = 0.0;
            while ((p != points.end()) && (*p <= x)) {
                acc += diff;
                p++;
            }
            graph.emplace_back(x, acc);
        }

        return graph;
    }
}
};
}

#endif  // CPPSTAT_GRAPHFACTORY_H
