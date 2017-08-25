// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_ESTIMATOR_H
#define CPPSTAT_ESTIMATOR_H

#include "common/MathTypes.h"

namespace estimator {

class Estimator {
  public:
    Estimator() = delete;

    static CDF estimateCDF(SampleSet &sampleSet) {
        FunctionGraph graph;
        double diff = 1.0 / sampleSet.size();
        double acc = diff;
        for (auto p : sampleSet) {
            if ((!graph.empty()) && (p == graph.back().first)) {
                graph.back().second = acc;
            } else {
                graph.emplace_back(p, acc);
            }
            acc += diff;
        }

        return [graph](double x) {
            Point spot{x, 0.0};
            auto pointIterator =
                std::lower_bound(graph.begin(), graph.end(), spot,
                                 [](const Point &p1, const Point &p2) {
                                     return p1.first < p2.first;
                                 });
            if (pointIterator == graph.end()) {
                return 1.0;
            } else if (x == pointIterator->first) {
                return pointIterator->second;
            } else if (pointIterator == graph.begin()) {
                return 0.0;
            } else {
                pointIterator--;
                return pointIterator->second;
            }
        };
    }

    static double Estimator::estimateMoment(SampleSet &sampleSet, int n) {
        double sum = 0.0;
        double mean = estimateMean(sampleSet);
        for (auto x : sampleSet) {
            sum += std::pow(std::abs(x - mean), n);
        }
        return sum / sampleSet.size();
    }

    static double Estimator::estimateMean(SampleSet &sampleSet) {
        double sum = 0.0;
        for (auto x : sampleSet) {
            sum += x;
        }
        return sum / sampleSet.size();
    }
};
}

#endif  // CPPSTAT_ESTIMATOR_H
