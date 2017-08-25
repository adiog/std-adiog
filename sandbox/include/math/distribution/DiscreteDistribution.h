// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_DISCRETEDISTRIBUTION_H
#define CPPSTAT_DISCRETEDISTRIBUTION_H

#include <random>

namespace distribution {

class DiscreteDistribution {
  protected:
    DiscreteDistribution() : generator{std::random_device{}()} {}

    std::mt19937 generator;

  public:
    virtual int sample(void) = 0;
    virtual double cdf(int i) const = 0;
    virtual double pdf(int i) const = 0;
    virtual std::string getString(void) const = 0;
    virtual std::string getStyle(void) const = 0;
};
}

#endif  // CPPSTAT_DISCRETEDISTRIBUTION_H
