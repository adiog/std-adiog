// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.
#include <functional>
#include <vector>
#include "math/distribution/DistributionFactory.h"
#include "math/distribution/UniformInt.h"
#include "math/plot/Render.h"
#include "statistics/estimator/GraphFactory.h"
#include "statistics/estimator/Estimator.h"

int main() {
    /* Uniform Int */
    /*
    Config::N = 1000;
    Config::pdfEstimationStep = 1.0;
    Config::dx = 1;
    Config::xrange_min = 0;
    Config::xrange_max = 20;
    Config::yrange_max = 1.5;
    */

    std::vector<std::pair<double, double>> uniformIntParams;
    for (double var : xrange<double>(5.0, 20.0, 10.0)) {
        uniformIntParams.emplace_back(1.0, var);
    }
    plot::Render::draw(
        distribution::DistributionFactory<distribution::UniformInt>(),
        uniformIntParams, estimator::GraphFactory::estimateDiscretePDF,
        std::mem_fn(&distribution::DiscreteDistribution::pdf),
        std::string("PDF"));
    plot::Render::draw(
        distribution::DistributionFactory<distribution::UniformInt>(),
        uniformIntParams, estimator::GraphFactory::estimateCDF,
        std::mem_fn(&distribution::DiscreteDistribution::cdf),
        std::string("CDF"));
}