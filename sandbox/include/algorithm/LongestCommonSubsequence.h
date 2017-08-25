// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPP_TRAINING_LONGESTCOMMONSUBSEQUENCE_H
#define CPP_TRAINING_LONGESTCOMMONSUBSEQUENCE_H

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

namespace algorithm {

class LongestCommonSubsequence {
    template <typename IterableContainer>
    static std::vector<typename IterableContainer::value_type> compute(
        IterableContainer ic1, IterableContainer ic2) {
        return LongestCommonSubsequence(std::begin(ic1), std::end(ic1),
                                        std::begin(ic2), std::end(ic2));
    }

    template <typename ForwardIt>
    static std::vector<typename ForwardIt::value_type> compute(ForwardIt begin1,
                                                               ForwardIt end1,
                                                               ForwardIt begin2,
                                                               ForwardIt end2) {
        int n = end1 - begin1;
        int m = end2 - begin2;
        vector<vector<int>> lcs(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (*(begin1 + i - 1) == *(begin2 + j - 1)) {
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                } else {
                    lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
                }
            }
        }
        int i = n;
        int j = m;
        int rend = lcs[n][m] - 1;
        vector<int> ret(lcs[n][m]);
        while ((i > 0) && (j > 0)) {
            if (*(begin1 + i - 1) == *(begin2 + j - 1)) {
                ret[rend] = *(begin1 + i - 1);
                i--;
                j--;
            } else {
                if (lcs[i - 1][j] > lcs[i][j - 1]) {
                    i--;
                } else {
                    j--;
                }
            }
        }
        return ret;
    }
};
}

#endif  // CPP_TRAINING_LONGESTCOMMONSUBSEQUENCE_H
