// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPP_TRAINING_MAXTREE_H
#define CPP_TRAINING_MAXTREE_H

#include <vector>

namespace dataStructure {

class MaxTree {
  public:
    using ValueType = unsigned long long int;
    using IndexType = unsigned long;
    using TreeType = std::vector<ValueType>;

    MaxTree(IndexType size) : size(size) {
        sizeRoundUp = roundUp(size);
        tree = TreeType(2U * sizeRoundUp);
    }

    void set(IndexType pos, ValueType value) {
        int node = sizeRoundUp + pos - 1;
        tree[node] = value;
        while (node != 0U) {
            node = upNode(node);
            tree[node] = std::max(tree[node], value);
        }
    }

    ValueType getValue(IndexType pos) { return tree[sizeRoundUp + pos - 1]; }

    ValueType getMax(IndexType begin, IndexType end) {
        return doGetMax(0, 0, sizeRoundUp, sizeRoundUp / 2, begin, end);
    }

    const TreeType &getValues() const { return tree; }

  private:
    IndexType roundUp(IndexType n) const {
        IndexType ret = 1U;
        while (ret < n) {
            ret *= 2U;
        }
        return ret;
    }

    IndexType leftNode(IndexType node) const { return 2U * node + 1U; }
    IndexType rightNode(IndexType node) const { return 2U * node + 2U; }
    IndexType upNode(IndexType node) const { return (node - 1U) / 2U; }

    int doGetMax(IndexType node, IndexType begin, IndexType endExclusive,
                 IndexType halfRange, IndexType rangeBegin,
                 IndexType rangeEndExclusive) {
        if ((begin == rangeBegin) && (endExclusive == rangeEndExclusive)) {
            return tree[node];
        } else if (rangeEndExclusive <= begin + halfRange) {
            return doGetMax(leftNode(node), begin, begin + halfRange,
                            halfRange / 2U, rangeBegin, rangeEndExclusive);
        } else if (rangeBegin >= begin + halfRange) {
            return doGetMax(rightNode(node), begin + halfRange, endExclusive,
                            halfRange / 2U, rangeBegin, rangeEndExclusive);
        } else if (halfRange > 0U) {
            return std::max(
                doGetMax(leftNode(node), begin, begin + halfRange,
                         halfRange / 2U, rangeBegin, begin + halfRange),
                doGetMax(rightNode(node), begin + halfRange, endExclusive,
                         halfRange / 2U, begin + halfRange, rangeEndExclusive));
        } else {
            return -1;
        }
    }

  private:
    IndexType size;
    IndexType sizeRoundUp;
    TreeType tree;
};
}

std::ostream &operator<<(std::ostream &os, const dataStructure::MaxTree &maxTree) {
    os << maxTree.getValues();

    return os;
}

#endif  // CPP_TRAINING_MAXTREE_H
