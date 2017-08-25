// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPP_TRAINING_HEAP_H
#define CPP_TRAINING_HEAP_H

#include <vector>
#include <functional>

namespace dataStructure {

template<typename Compare = std::greater<int>>
class Heap {
  public:
    Heap(int size) : a(size), n(0) {}
    Heap(const std::vector<int> &v) : a(v.size()), n(0) {
        for (int i : v) {
            push(i);
        }
    }

    bool empty() { return n == 0; }

    void push(int e) {
        a[n] = e;
        int m = n;
        while ((m > 0) && (Compare()(a[m / 2], a[m])))
            std::swap(a[m], a[m / 2]), m /= 2;
    }

    int top() { return a[0]; }

    int left(int i) { return i * 2 + 1; }

    int right(int i) { return i * 2 + 2; }

    void pop() {
        std::swap(a[0], a[n - 1]);
        n--;
        int i = 0;
        while (true) {
            if ((right(i) == n) && (Compare()(a[i], a[left(i)]))) {
                std::swap(a[i], a[left(i)]);
                i = left(i);
            } else if (right(i) < n) {
                if (Compare()(a[left(i)], a[right(i)])) {
                    std::swap(a[i], a[right(i)]);
                    i = right(i);
                } else {
                    std::swap(a[i], a[left(i)]);
                    i = left(i);
                }
            } else {
                break;
            }
        }
    }

  private:
    std::vector<int> a;
    int n;
};
}

#endif  // CPP_TRAINING_HEAP_H
