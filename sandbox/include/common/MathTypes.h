// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_MATHTYPES_HPP
#define CPPSTAT_MATHTYPES_HPP

#include <functional>
#include <utility>
#include <vector>

using Real = double;
using RealSet = std::vector<Real>;

using Yield = std::function<Real()>;
using Point = std::pair<Real, Real>;
using FunctionGraph = std::vector<Point>;

using PDF = std::function<Real(Real)>;
using CDF = std::function<Real(Real)>;

using SampleSet = std::vector<Real>;

#endif  // CPPSTAT_MATHTYPES_HPP

