// This file is a part of std-adiog project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef _ADG_ISTREAM_H
#define _ADG_ISTREAM_H

#include <istream>

#ifdef _STL_PAIR_H
template <typename A, typename B>
std::istream &operator>>(std::istream &is, std::pair<A, B> &pair)
{
    is >> pair.first >> pair.second;
    return is;
}
#endif

#ifdef _GLIBCXX_UTILITY
template <typename A>
std::istream &operator>>(std::istream &is, std::tuple<A> &tuple)
{
    is >> std::get<0>(tuple);
    return is;
}

template <typename A, typename B>
std::istream &operator>>(std::istream &is, std::tuple<A, B> &tuple)
{
    is >> std::get<0>(tuple);
    is >> std::get<1>(tuple);
    return is;
}

template <typename A, typename B, typename C>
std::istream &operator>>(std::istream &is, std::tuple<A, B, C> &tuple)
{
    is >> std::get<0>(tuple);
    is >> std::get<1>(tuple);
    is >> std::get<2>(tuple);
    return is;
}

template <typename A, typename B, typename C, typename D>
std::istream &operator>>(std::istream &is, std::tuple<A, B, C, D> &tuple)
{
    is >> std::get<0>(tuple);
    is >> std::get<1>(tuple);
    is >> std::get<2>(tuple);
    is >> std::get<3>(tuple);
    return is;
}

template <typename A, typename B, typename C, typename D, typename E>
std::istream &operator>>(std::istream &is, std::tuple<A, B, C, D, E> &tuple)
{
    is >> std::get<0>(tuple);
    is >> std::get<1>(tuple);
    is >> std::get<2>(tuple);
    is >> std::get<3>(tuple);
    is >> std::get<4>(tuple);
    return is;
}
#endif

#ifdef _GLIBCXX_ARRAY
template <typename T, size_t N>
std::istream &operator>>(std::istream &is, std::array<T, N> &array)
{
    for (auto &element : array)
    {
        is >> element;
    }
    return is;
}
#endif

#ifdef _STL_VECTOR_H
template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &vector)
{
    for (auto &element : vector)
    {
        is >> element;
    }
    return is;
}
#endif

#endif
