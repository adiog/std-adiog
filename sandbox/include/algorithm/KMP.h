// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_KMP_H
#define PROJECT_KMP_H

#include <io>
#include <ostream>
#include <string>
#include <vector>

namespace algorithm {

class KMP {
  public:
    using IndexType = unsigned int;
    using Text = std::string;
    using PrefixTable = std::vector<IndexType>;

    static std::vector<IndexType> find(const Text &pattern, const Text &text, const char special_char = '#') {
        Text special = pattern + special_char + text;
        PrefixTable prefixTable = getPrefixTable(special);
        std::vector<IndexType> result;

        for (IndexType i = pattern.size(); i < text.size(); ++i) {
            if (pattern.size() == prefixTable[pattern.size()+i+1]) {
              result.push_back(i-pattern.size()+1);
            }
        }
        
        return result;
    }

    template<typename ForwardIt>
    static PrefixTable getPrefixTable(ForwardIt begin, ForwardIt end) {
        const typename ForwardIt::value_type *text = &(*begin);
        size_t text_size = static_cast<size_t>(end-begin);

        PrefixTable prefixTable(text_size+1U, 0);
        prefixTable[1] = 0U;
        IndexType longestPS = 0U;

        for (IndexType i = 2; i <= text_size; ++i) {
            while ((longestPS > 0U) && (text[i-1] != text[longestPS])) {
                longestPS = prefixTable[longestPS];
            }
            if (text[i-1] == text[longestPS]) {
                longestPS = longestPS + 1U;
            }
            prefixTable[i] = longestPS;
        }

        std::cout << prefixTable << std::endl;

        return prefixTable;
    }
    
    static PrefixTable getPrefixTable(Text &text) {
        return getPrefixTable(text.begin(), text.end());
    }
};
}

#endif  // PROJECT_KMP_H
