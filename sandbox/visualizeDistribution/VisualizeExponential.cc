// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <vector>
#include "math/plot/Render.h"
#include <functional>
#include <vector>
#include "math/distribution/DistributionFactory.h"
#include "math/distribution/Exponential.h"
#include "math/plot/Render.h"
#include "statistics/estimator/GraphFactory.h"
#include "statistics/estimator/Estimator.h"


int main() {
    /* Exponential*/
/*    Config::N = 1000;
    Config::dx = 1;
    Config::xrange_min = 0;
    Config::xrange_max = 15;
    Config::yrange_max = 1.5;
*/
    std::vector<double> exponentialParams = {1.0, 2.0};
    plot::Render::draw(
        distribution::DistributionFactory<distribution::Exponential>(),
        exponentialParams, estimator::GraphFactory::estimateDiscretePDF,
        std::mem_fn(&distribution::Distribution::pdf), std::string("PDF"));
    plot::Render::draw(
        distribution::DistributionFactory<distribution::Exponential>(),
        exponentialParams, estimator::GraphFactory::estimateCDF,
        std::mem_fn(&distribution::Distribution::cdf), std::string("CDF"));
}