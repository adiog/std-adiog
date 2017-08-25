// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_NAIVELAGRANGEPOLYNOMIAL_H
#define PROJECT_NAIVELAGRANGEPOLYNOMIAL_H

namespace numerical {

class NaiveLagrangePolynomial {
  public:
    NaiveLagrangePolynomial(RealSet xvalues, RealSet yvalues)
        : xvalues(xvalues), yvalues(yvalues) {}

    Real estimate(Real x) const {
        Real y = 0;
        for (unsigned int yi = 0; yi < yvalues.size(); yi++) {
            Real ypart = yvalues[yi];
            for (unsigned int xi = 0; xi < xvalues.size(); xi++) {
                if (xi != yi) {
                    ypart *= (x - xvalues[xi]) / (xvalues[yi] - xvalues[xi]);
                }
            }
            y += ypart;
        }
        return y;
    }

  private:
    RealSet xvalues;
    RealSet yvalues;
};
}

#endif  // PROJECT_NAIVELEGRANGEPOLYNOMIAL_H
