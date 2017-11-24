// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef _ADG_OSTREAM_H
#define _ADG_OSTREAM_H

#ifdef _STL_PAIR_H
template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, const std::pair<A, B> &pair) {
    os << PAIR_BEGIN << pair.first << PAIR_DELIMITER << pair.second << PAIR_END;
    return os;
}
#endif

#ifdef _GLIBCXX_UTILITY
template <typename A>
std::ostream &operator<<(std::ostream &os, const std::tuple<A> &tuple) {
    os << std::get<0>(tuple);
    return os;
}

template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, const std::tuple<A, B> &tuple) {
    os << TUPLE_BEGIN;
    os << std::get<0>(tuple) << TUPLE_DELIMITER;
    os << std::get<1>(tuple);
    os << TUPLE_END;
    return os;
}

template <typename A, typename B, typename C>
std::ostream &operator<<(std::ostream &os, const std::tuple<A, B, C> &tuple) {
    os << TUPLE_BEGIN;
    os << std::get<0>(tuple) << TUPLE_DELIMITER;
    os << std::get<1>(tuple) << TUPLE_DELIMITER;
    os << std::get<2>(tuple);
    os << TUPLE_END;
    return os;
}

template <typename A, typename B, typename C, typename D>
std::ostream &operator<<(std::ostream &os,
                         const std::tuple<A, B, C, D> &tuple) {
    os << TUPLE_BEGIN;
    os << std::get<0>(tuple) << TUPLE_DELIMITER;
    os << std::get<1>(tuple) << TUPLE_DELIMITER;
    os << std::get<2>(tuple) << TUPLE_DELIMITER;
    os << std::get<3>(tuple);
    os << TUPLE_END;
    return os;
}

template <typename A, typename B, typename C, typename D, typename E>
std::ostream &operator<<(std::ostream &os,
                         const std::tuple<A, B, C, D, E> &tuple) {
    os << TUPLE_BEGIN;
    os << std::get<0>(tuple) << TUPLE_DELIMITER;
    os << std::get<1>(tuple) << TUPLE_DELIMITER;
    os << std::get<2>(tuple) << TUPLE_DELIMITER;
    os << std::get<3>(tuple) << TUPLE_DELIMITER;
    os << std::get<4>(tuple);
    os << TUPLE_END;
    return os;
}
#endif

#ifdef _GLIBCXX_ARRAY
template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const std::array<T, N> &array) {
    os << ARRAY_BEGIN;
    for (auto it = array.cbegin(); it < array.cend(); it++) {
        os << *it;
        if (it + 1 < array.cend()) {
            os << ARRAY_DELIMITER;
        }
    }
    os << ARRAY_END;
    return os;
}
#endif

#ifdef _STL_VECTOR_H
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vector) {
    os << VECTOR_BEGIN;
    for (auto it = vector.cbegin(); it < vector.cend(); it++) {
        os << *it;
        if (it + 1 < vector.cend()) {
            os << VECTOR_DELIMITER;
        }
    }
    os << VECTOR_END;
    return os;
}
#endif

#ifdef _STL_QUEUE_H
template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, const std::queue<A, B> &queue) {
    os << QUEUE_BEGIN;
    auto queueCopy = std::queue<A, B>(queue);
    while (queueCopy.size() > 1U) {
        os << queueCopy.front() << QUEUE_DELIMITER;
        queueCopy.pop();
    }
    if (!queueCopy.empty()) {
        os << queueCopy.front();
    }
    os << QUEUE_END;
    return os;
}
#endif

#ifdef _STL_STACK_H
template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, const std::stack<A, B> &stack) {
    os << STACK_BEGIN;
    auto stackCopy = std::stack<A, B>(stack);
    while (stackCopy.size() > 1U) {
        os << stackCopy.top() << STACK_DELIMITER;
        stackCopy.pop();
    }
    if (!stackCopy.empty()) {
        os << stackCopy.top();
    }
    os << STACK_END;
    return os;
}
#endif

#ifdef _STL_QUEUE_H
template <typename A, typename B, typename C>
std::ostream &operator<<(std::ostream &os,
                         const std::priority_queue<A, B, C> &priorityQueue) {
    os << PRIORITY_QUEUE_BEGIN;
    auto priorityQueueCopy = std::priority_queue<A, B, C>(priorityQueue);
    while (priorityQueueCopy.size() > 1U) {
        os << priorityQueueCopy.top() << PRIORITY_QUEUE_DELIMITER;
        priorityQueueCopy.pop();
    }
    if (!priorityQueueCopy.empty()) {
        os << priorityQueueCopy.top();
    }
    os << PRIORITY_QUEUE_END;
    return os;
}
#endif

#ifdef _STL_SET_H
template <typename A, typename B, typename C>
std::ostream &operator<<(std::ostream &os, const std::set<A, B, C> &set) {
    os << SET_BEGIN;
    for (auto it = set.cbegin(); it != set.cend(); ++it) {
        os << *it;
        if (std::next(it) != set.cend()) {
            os << SET_DELIMITER;
        }
    }
    os << SET_END;
    return os;
};
#endif

#ifdef _STL_MAP_H
template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const std::map<K, V> &map) {
    os << MAP_BEGIN;
    for (auto it = map.begin(); it != map.end(); ++it) {
        os << MAP_PAIR_BEGIN << it->first << MAP_PAIR_DELIMITER << it->second
           << MAP_PAIR_END;
        if (std::next(it) != map.end()) {
            os << MAP_DELIMITER;
        }
    }
    os << MAP_END;
    return os;
}
#endif

#ifdef _UNORDERED_MAP_H
template <typename K, typename V>
std::ostream &operator<<(std::ostream &os,
                         const std::unordered_map<K, V> &map) {
    os << MAP_BEGIN;
    for (auto it = map.begin(); it != map.end(); ++it) {
        os << MAP_PAIR_BEGIN << it->first << MAP_PAIR_DELIMITER << it->second
           << MAP_PAIR_END;
        if (std::next(it) != map.end()) {
            os << MAP_DELIMITER;
        }
    }
    os << MAP_END;
    return os;
}
#endif

#ifdef _GLIBCXX_BITSET
template <typename T, int N = 8>
std::string to_b(const T &t) {
    return std::bitset<N>(t).to_string();
}
#endif

namespace adg {
template<typename T>
struct to_2d
{
    to_2d(const T &t) : t(t)
    {}

    const T &t;
};

template<typename T>
to_2d<T> to_2(const T &t)
{
    return to_2d<T>(t);
}
}

#ifdef _STL_VECTOR_H
template <typename T>
std::ostream &operator<<(std::ostream &os, const adg::to_2d<T> &vector_2d) {
    os << VECTOR_BEGIN;
    for (auto it = vector_2d.t.cbegin(); it < vector_2d.t.cend(); it++) {
        if (it != vector_2d.t.cbegin()) {
            os << VECTOR_EMPTY_BEGIN;
        }
        os << VECTOR_BEGIN;
        for (auto it2 = it->cbegin(); it2 < it->cend(); it2++) {
            os << *it2;
            if (it2 + 1 < it->cend()) {
                os << ",\t";
            }
        }
        os << VECTOR_END;
        if (it + 1 < vector_2d.t.cend()) {
            os << VECTOR_DELIMITER << std::endl;
        }
    }
    os << VECTOR_END;
    return os;
}
#endif

#endif
