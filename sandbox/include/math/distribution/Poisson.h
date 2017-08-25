// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_POISSON_H
#define CPPSTAT_POISSON_H

#include "DiscreteDistribution.h"
#include <boost/math/distributions/poisson.hpp>

namespace distribution {

class Poisson : public DiscreteDistribution {
  public:
    Poisson(double lambda)
        : lambda{lambda},
          mathDistribution{lambda},
          randomDistribution{lambda} {}
    virtual ~Poisson() = default;
    Poisson(const Poisson &poisson) = default;
    Poisson &operator=(const Poisson &poisson) = default;
    Poisson(Poisson &&poisson) = default;
    Poisson &operator=(Poisson &&poisson) = default;

    int sample(void) override { return randomDistribution(generator); }
    double cdf(int i) const override {
        return boost::math::cdf(mathDistribution, i);
    }
    double pdf(int i) const override {
        return boost::math::pdf(mathDistribution, i);
    }
    std::string getString(void) const override {
        std::stringstream ss;
        ss << "Poisson(" << lambda << ")";
        return ss.str();
    }
    std::string getStyle(void) const override { return "points"; }

  private:
    double lambda;
    boost::math::poisson mathDistribution;
    std::poisson_distribution<> randomDistribution;
};
}

#endif  // CPPSTAT_POISSON_H
