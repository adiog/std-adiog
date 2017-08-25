// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_EXPONENTIAL_H
#define CPPSTAT_EXPONENTIAL_H

#include "Distribution.h"
#include <boost/math/distributions/exponential.hpp>

namespace distribution {

class Exponential : public Distribution {
  public:
    Exponential(double rate)
        : rate{rate}, mathDistribution{rate}, randomDistribution{rate} {}
    virtual ~Exponential() = default;
    Exponential(const Exponential &exponential) = default;
    Exponential &operator=(const Exponential &exponential) = default;
    Exponential(Exponential &&exponential) = default;
    Exponential &operator=(Exponential &&exponential) = default;

    double sample(void) override { return randomDistribution(generator); }

    double cdf(double x) const override {
        return boost::math::cdf(mathDistribution, x);
    }

    double pdf(double x) const override {
        return boost::math::pdf(mathDistribution, x);
    }

    std::string getString(void) const override {
        std::stringstream ss;
        ss << "Exponential(" << rate << ")";
        return ss.str();
    }
    std::string getStyle(void) const override { return "linespoints"; }

  private:
    double rate;
    boost::math::exponential mathDistribution;
    std::exponential_distribution<> randomDistribution;
};
}

#endif  // CPPSTAT_EXPONENTIAL_H
