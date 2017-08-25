// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_RENDER_H
#define CPPSTAT_RENDER_H

#include "math/distribution/DistributionFactory.h"

namespace plot {

class Render {
  public:
    Render() = delete;

    template <typename DistributionType, typename DistributionParameters, typename ReferenceFunction>
    static void draw(
        distribution::DistributionFactory<DistributionType> distributionFactory,
        DistributionParameters distributionParameters,
        estimator::EstimateGraph estimateGraph,
        ReferenceFunction referenceFunction,
        std::string label) {
        Plot plot;

        for (auto dp : distributionParameters) {
            auto distribution = distributionFactory.get(dp);

            std::stringstream ss;
            ss << "with " << distribution.getStyle() << " title 'estimated "
               << label << " of " << distribution.getString() << "'";
            plot.addGraph(
                estimateGraph([&]() { return distribution.sample(); }),
                ss.str());

            std::stringstream ss2;
            ss2 << "with " << distribution.getStyle() << " title 'real "
                << label << " of " << distribution.getString() << "'";
            plot.addGraph(estimator::GraphFactory::generate(
                              [&](double x) { return referenceFunction(distribution, x); }),
                          ss2.str());
        }
        plot.render();
    }
};
}

#endif  // CPPSTAT_RENDER_H
