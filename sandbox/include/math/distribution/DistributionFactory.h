// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_DISTRIBUTIONFACTORY_H
#define CPPSTAT_DISTRIBUTIONFACTORY_H

namespace distribution {

template <typename DistributionType>
class DistributionFactory {
  public:
    DistributionFactory() = default;

    template <typename... Args>
    DistributionType get(Args... args) {
        return DistributionType(args...);
    }
};
}

#endif  // CPPSTAT_DISTRIBUTIONFACTORY_H
