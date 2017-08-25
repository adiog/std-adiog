// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_STDTYPES_H
#define PROJECT_STDTYPES_H

#include <utility>
#include <vector>
#include <map>
#include <queue>

template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, const std::pair<A, B> &pair) {
    os << "(" << pair.first << "," << pair.second << ")";
    return os;
}

template <typename A, typename B, typename C>
std::ostream &operator<<(std::ostream &os,
                         const std::priority_queue<A, B, C> &priorityQueue) {
    auto priorityQueueCopy = std::priority_queue<A, B, C>(priorityQueue);
    os << "[";
    while (!priorityQueueCopy.empty()) {
        os << priorityQueueCopy.top() << ";";
        priorityQueueCopy.pop();
    }
    os << "]";

    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &t) {
    os << "[";
    for (const auto &i : t) {
        os << i << ";";
    }
    os << "]";

    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::queue<T> &t) {
    std::queue<T> copy(t);
    os << "[";
    while (!copy.empty()) {
        auto val = copy.front();
        copy.pop();
        os << val << ";";
    }
    os << "]";

    return os;
}

template<typename K, typename V>
std::ostream &operator<<(std::ostream &os, const std::map<K, V> &map) {
    os << "[";

  for (auto it=map.begin(); it!=map.end(); ++it)
    os << it->first << " => " << it->second << "; ";
            /*       for (const auto &i : map) {
        os << i.first << "->" << i.second << ";";
    }*/
    os << "]";

    return os;
}

#endif  // PROJECT_STDTYPES_H
