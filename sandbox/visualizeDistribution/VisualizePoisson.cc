// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <functional>
#include <vector>
#include "math/distribution/DistributionFactory.h"
#include "math/distribution/Poisson.h"
#include "math/plot/Render.h"
#include "statistics/estimator/GraphFactory.h"
#include "statistics/estimator/Estimator.h"

int main() {
    /* Poisson */
/*
    Config::N = 1000;
    Config::dx = 1;
    Config::xrange_min = 0;
    Config::xrange_max = 15;
    Config::yrange_max = 1.5;
*/

    std::vector<double> poissonParams = {1.0, 2.0};
    plot::Render::draw(
        distribution::DistributionFactory<distribution::Poisson>(),
        poissonParams, estimator::GraphFactory::estimateDiscretePDF,
        std::mem_fn(&distribution::DiscreteDistribution::pdf),
        std::string("PDF"));
    plot::Render::draw(
        distribution::DistributionFactory<distribution::Poisson>(),
        poissonParams, estimator::GraphFactory::estimateCDF,
        std::mem_fn(&distribution::DiscreteDistribution::cdf),
        std::string("CDF"));
}
