// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_PROCESS_PROCESS_H
#define CPPSTAT_PROCESS_PROCESS_H

#include "common/MathTypes.h"

namespace process {

class Process {
  public:
    virtual FunctionGraph getSamplePath(double T) = 0;
};
}

#endif  // CPPSTAT_PROCESS_PROCESS_H
