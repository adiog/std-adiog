// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_MANACHER_H
#define PROJECT_MANACHER_H

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

namespace algorithm {

class Manacher {
  public:
    Manacher() {}

    std::string preProcess(const std::string& s) {
        std::string ret = std::string(s.size()*2+1, '#');
        for (int i = 0; i < s.size(); i++) {
            ret[2*i+1] = s[i];
        }
        return ret;
    }

    void findPalindroms(const std::string &s) {
        std::string T = preProcess(s);
        P = std::vector<int>(T.size());
        int C = 1;
        int R = 1;

        for (int i = 1; i < T.size()-1; i++) {
            int i_mirror = 2*C-i; // equals to i' = C - (i-C)
    
            P[i] = (R > i) ? std::min(R-i, P[i_mirror]) : 0;
    
            // Attempt to expand palindrome centered at i
            while ((i + P[i] + 1 < T.size()) && (i - 1 - P[i] >= 0) && (T[i + 1 + P[i]] == T[i - 1 - P[i]])) {
                P[i]++;
            }

            // If palindrome centered at i expand past R,
            // adjust center based on expanded palindrome.
            if (i + P[i] > R) {
                C = i;
                R = i + P[i];
            }
        }
    }

    const std::vector<int>& getPalindroms(void) const {
        return P;
    }

  private:
    std::vector<int> P;
};
}

#endif  // PROJECT_MANACHER_H
