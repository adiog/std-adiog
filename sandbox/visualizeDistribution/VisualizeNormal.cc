// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.
#include <functional>
#include <vector>
#include "math/distribution/DistributionFactory.h"
#include "math/distribution/Normal.h"
#include "math/plot/Render.h"
#include "statistics/estimator/GraphFactory.h"
#include "statistics/estimator/Estimator.h"

int main() {
    /* Normal */
    /*
     * Config::N = 1000;
    Config::dx = 1;
    Config::xrange_min = -10;
    Config::xrange_max = 10;
    Config::yrange_max = 1.5;
*/

    std::vector<std::pair<double, double>> normalParams;
    for (double var : xrange<double>(1.0, 3.0)) {
        normalParams.emplace_back(0.0, var);
    }
    plot::Render::draw(
        distribution::DistributionFactory<distribution::Normal>(), normalParams,
        estimator::GraphFactory::estimateDiscretePDF,
        std::mem_fn(&distribution::Distribution::pdf), std::string("PDF"));
    plot::Render::draw(
        distribution::DistributionFactory<distribution::Normal>(), normalParams,
        estimator::GraphFactory::estimateCDF,
        std::mem_fn(&distribution::Distribution::cdf), std::string("CDF"));
}