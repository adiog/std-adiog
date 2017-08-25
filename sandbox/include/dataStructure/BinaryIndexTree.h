// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPP_TRAINING_BINARYINDEXTREE_H
#define CPP_TRAINING_BINARYINDEXTREE_H

#include <algorithm>
#include <vector>

namespace dataStructure {
class BinaryIndexTree {
  public:
    explicit BinaryIndexTree(int size) : v(size + 1, 0) {}
    explicit BinaryIndexTree(const std::vector<int> &in) : v(in.size() + 1, 0) {
        for (int i = 0; i < in.size(); i++) {
            add(i, in[i]);
        }
    }

    int get(int i) const {
        int sum = 0;
        while (i > 0) {
            sum += v[i];
            i -= i & -i;
        }
        return sum;
    }

    void add(int i, int k) {
        i++;
        while (i < v.size()) {
            v[i] += k;
            i += i & -i;
        }
    }

    std::vector<int> getValues() const {
        std::vector<int> ret(v.size());
        int i = 0;
        std::generate(ret.begin(), ret.end(), [&]() { return this->get(i++); });
        return ret;
    }

    const std::vector<int> &getRepresentation() const { return v; }

  private:
    std::vector<int> v;
};
}

/*
 * std::ostream &operator<<(
    std::ostream &os, const dataStructure::BinaryIndexTree &binaryIndexTree) {
    os << binaryIndexTree.getRepresentation();

    return os;
}
*/
#endif  // CPP_TRAINING_BINARYINDEXTREE_H
