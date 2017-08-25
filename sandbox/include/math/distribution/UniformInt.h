// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_UNIFORMINT_H
#define CPPSTAT_UNIFORMINT_H

#include "Distribution.h"

namespace distribution {

class UniformInt : public DiscreteDistribution {
  public:
    UniformInt(std::pair<double, double> args) : UniformInt(args.first, args.second) {}
    UniformInt(int range_min, int range_max)
        : range_min{range_min},
          range_max{range_max},
          randomDistribution{range_min, range_max} {}
    virtual ~UniformInt() = default;
    UniformInt(const UniformInt &uniformInt) = default;
    UniformInt &operator=(const UniformInt &uniformInt) = default;
    UniformInt(UniformInt &&uniformInt) = default;
    UniformInt &operator=(UniformInt &&uniformInt) = default;

    int sample(void) override { return randomDistribution(generator); }
    double cdf(int i) const override {
        if (i < range_min) {
            return 0.0;
        } else if (i > range_max) {
            return 1.0;
        } else {
            return (i - range_min + 1.0) / (range_max - range_min + 1.0);
        }
    }
    double pdf(int i) const override {
        return ((i >= range_min) && (i <= range_max)) ? 1.0 / (range_max - range_min + 1.0) : 0.0;
    }
    std::string getString(void) const override {
        std::stringstream ss;
        ss << "UniformInt(" << range_min << ", " << range_max << ")";
        return ss.str();
    }
    std::string getStyle(void) const override { return "points"; }

  private:
    int range_min;
    int range_max;
    std::uniform_int_distribution<> randomDistribution;
};
}

#endif  // CPPSTAT_UNIFORMINT_H
