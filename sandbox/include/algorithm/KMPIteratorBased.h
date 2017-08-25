// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_KMP_H
#define PROJECT_KMP_H

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

namespace algorithm {

class KMPIteratorBased {
  public:
    using IndexType = unsigned int;
    using Text = std::string;
    using PrefixTable = std::vector<IndexType>;

    static int findFast(Text &pattern, ForwardIt textBegin, ForwardIt textEnd, PrefixTable &prefixTable) {
        std::vector<int> result;
        IndexType longestMatch = 0U;
        for (auto it = textBegin; it < textEnd; i++) {
            if (*it == pattern[longestMatch]) {
                longestMatch++;
                if (longestMatch == pattern.size()) {
                    result.push_back(i - pattern.size() + 1);
                }
            } else {
                while ((*it != pattern[longestMatch]) &&
                       (longestMatch > 0U)) {
                    longestMatch = prefixTable[longestMatch - 1U];
                }
            }
        }
        return -1;
    }

    static PrefixTable getPrefixTable(Text text) {
        PrefixTable prefixTable(text.size(), 0);
        prefixTable[0] = 0U;
        IndexType longestPS = 0U;

        for (IndexType i = 1; i < text.size(); ++i) {
            while ((text[i] != text[longestPS]) && (longestPS > 0U)) {
                longestPS = prefixTable[longestPS - 1U];
            }
            if (text[i] == text[longestPS]) {
                longestPS = longestPS + 1U;
            }
            prefixTable[i] = longestPS;
        }
        return prefixTable;
    }
};
}

#endif  // PROJECT_KMP_H
