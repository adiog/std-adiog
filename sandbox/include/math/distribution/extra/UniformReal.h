// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_NORMAL_H
#define CPPSTAT_NORMAL_H

#include <boost/math/distributions/uniform.hpp>
#include "Distribution.h"

namespace distribution {

class UniformReal : public Distribution {
  public:
    UniformReal(std::pair<Real, Real> args) : UniformReal(args.first, args.second) {}
    UniformReal(Real range_min, Real range_max)
        : range_min{range_min},
          range_max{range_max},
          mathDistribution{range_min, range_max},
          randomDistribution{range_min, range_max} {}
    virtual ~UniformReal() = default;
    UniformReal(const UniformReal &uniformReal) = default;
    UniformReal &operator=(const UniformReal &uniformReal) = default;
    UniformReal(UniformReal &&uniformReal) = default;
    UniformReal &operator=(UniformReal &&uniformReal) = default;

    Real sample(void) override { return randomDistribution(generator); }
    Real cdf(Real x) const override {
        return boost::math::cdf(mathDistribution, x);
    }
    Real pdf(Real x) const override {
        return boost::math::pdf(mathDistribution, x);
    }
    std::string getString(void) const override {
        std::stringstream ss;
        ss << "UniformReal(" << range_min << ", " << range_max << ")";
        return ss.str();
    }
    std::string getStyle(void) const override { return "linespoints"; }

  private:
    Real range_min;
    Real range_max;
    boost::math::uniform_distribution mathDistribution;
    std::uniform_real_distribution<> randomDistribution;
};
}

#endif  // CPPSTAT_NORMAL_H
