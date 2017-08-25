// This file is a part of cpps-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_DISTRIBUTION_H
#define CPPSTAT_DISTRIBUTION_H

#include <algorithm>
#include <random>

namespace math {
namespace distribution {

class Distribution
{
protected:
    Distribution()
            : generator{std::random_device{}()}
    {
    }

    std::mt19937 generator;

public:
    virtual double sample(void) = 0;

    virtual double cdf(double x) const = 0;

    virtual double pdf(double x) const = 0;

    virtual std::string getString(void) const = 0;

    virtual std::string getStyle(void) const = 0;

    SampleSet getSampleSet(int n)
    {
        SampleSet sampleSet(n);
        std::generate(sampleSet.begin(), sampleSet.end(), [this]() { return this->sample(); });
        return sampleSet;
    }

    SampleSet getSortedSampleSet(int n)
    {
        SampleSet sampleSet = getSampleSet(n);
        std::sort(sampleSet.begin(), sampleSet.end());
        return sampleSet;
    }
};
}
}

#endif  // CPPSTAT_DISTRIBUTION_H
