// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_NORMAL_H
#define CPPSTAT_NORMAL_H

#include <boost/math/distributions/normal.hpp>
#include <math/distribution/Distribution.h>

namespace math {
namespace distribution {

class Normal : public Distribution
{
public:
    Normal(std::pair<double, double> args)
            : Normal(args.first, args.second)
    {
    }

    Normal(double mean, double variance)
            : mean{mean}
            , variance{variance}
            , mathDistribution{mean, variance}
            , randomDistribution{mean, variance}
    {
    }

    virtual ~Normal() = default;

    Normal(const Normal &normal) = default;

    Normal &operator=(const Normal &normal) = default;

    Normal(Normal &&normal) = default;

    Normal &operator=(Normal &&normal) = default;

    double sample(void) override { return randomDistribution(generator); }

    double cdf(double x) const override
    {
        return boost::math::cdf(mathDistribution, x);
    }

    double pdf(double x) const override
    {
        return boost::math::pdf(mathDistribution, x);
    }

    std::string getString(void) const override
    {
        std::stringstream ss;
        ss << "Normal(" << mean << ", " << variance << ")";
        return ss.str();
    }

    std::string getStyle(void) const override { return "linespoints"; }

private:
    double mean;
    double variance;
    boost::math::normal mathDistribution;
    std::normal_distribution<> randomDistribution;
};
}
}

#endif  // CPPSTAT_NORMAL_H
