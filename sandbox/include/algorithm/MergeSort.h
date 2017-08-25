// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_MERGESORT_H
#define PROJECT_MERGESORT_H

#include <algorithm>

template<typename ForwardIt>
void merge(ForwardIt begin, ForwardIt middle, ForwardIt end) {
    using Value = typename ForwardIt::value_type;

    std::vector<Value> target(end-begin);
    auto begin1 = begin;
    auto begin2 = middle;
    std::generate(target.begin(), target.end(), [=]() mutable {
        Value ret;
        if (begin1 < middle) {
            if (begin2 < end) {
                if (*begin1 < *begin2) {
                    ret = *begin1;
                    begin1++;
                } else {
                    ret = *begin2;
                    begin2++;
                }
            } else {
                ret = *begin1;
                begin1++;
            }
        } else {
            ret = *begin2;
            begin2++;
        }
        return ret;
    } );

    std::copy(target.begin(), target.end(), begin);
}

template<typename ForwardIt>
void mergeSort(ForwardIt begin, ForwardIt end) {
    if (end - begin <= 1) {
        return;
    } else if (end - begin == 2) {
        if (*begin > *(begin+1)) {
            std::iter_swap(begin, begin+1);
        }
    } else {
        auto middle = begin + ((end - begin) / 2);
        mergeSort(begin, middle);
        mergeSort(middle, end);
        merge(begin, middle, end);
    }
}

#endif // PROJECT_MERGESORT_H
