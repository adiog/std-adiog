// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_RANGETREE_H
#define PROJECT_RANGETREE_H

namespace dataStructure {

class RangeTree {
  public:
    using ValueType = unsigned long long int;
    using IndexType = unsigned long;
    using TreeType = std::vector<ValueType>;

    RangeTree(IndexType size, ValueType value = 0U) : size(size) {
        sizeRoundUp = roundUp(size);
        tree = TreeType(2U * sizeRoundUp);
    }

    void insert(IndexType rangeBegin, IndexType rangeEnd, ValueType value) {
        doInsert(0U, 0U, sizeRoundUp, sizeRoundUp / 2U, rangeBegin, rangeEnd,
                 value);
    }

    ValueType getValue(IndexType node) {
        ValueType ret = tree[node];
        while (node != 0U) {
            node = upNode(node);
            ret += tree[node];
        }
        return ret;
    }

    TreeType getValues() const {
        TreeType values(size);
        doGetValues(values, 0U, 0U);
        return values;
    }

    ValueType getMax(IndexType node = 0U) {
        if (node >= sizeRoundUp - 1U) {
            return tree[node];
        } else {
            return tree[node] +
                   std::max(getMax(leftNode(node)), getMax(rightNode(node)));
        }
    }

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

    void doInsert(IndexType node, IndexType begin, IndexType endExclusive,
                  IndexType halfRange, IndexType rangeBegin,
                  IndexType rangeEndExclusive, ValueType value) {
        if ((begin == rangeBegin) && (endExclusive == rangeEndExclusive)) {
            tree[node] += value;
        } else if (rangeEndExclusive <= begin + halfRange) {
            doInsert(leftNode(node), begin, begin + halfRange, halfRange / 2U,
                     rangeBegin, rangeEndExclusive, value);
        } else if (rangeBegin >= begin + halfRange) {
            doInsert(rightNode(node), begin + halfRange, endExclusive,
                     halfRange / 2U, rangeBegin, rangeEndExclusive, value);
        } else if (halfRange > 0U) {
            doInsert(leftNode(node), begin, begin + halfRange, halfRange / 2U,
                     rangeBegin, begin + halfRange, value);
            doInsert(rightNode(node), begin + halfRange, endExclusive,
                     halfRange / 2U, begin + halfRange, rangeEndExclusive,
                     value);
        }
    }

    void doGetValues(TreeType &values, IndexType node, ValueType sum) const {
        if (node >= sizeRoundUp - 1U) {
            IndexType i = node - sizeRoundUp + 1U;
            std::cout << i << std::endl;
            if (i < size) {
                values[i] = sum + tree[node];
            }
        } else {
            doGetValues(values, leftNode(node), sum + tree[node]);
            doGetValues(values, rightNode(node), sum + tree[node]);
        }
    }

  private:
    IndexType size;
    IndexType sizeRoundUp;
    TreeType tree;
};
}

std::ostream &operator<<(std::ostream &os,
                         const dataStructure::RangeTree &rangeTree) {
    os << rangeTree.getValues();

    return os;
}

#endif  // PROJECT_RANGETREE_H
