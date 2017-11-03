// This file is a part of LoremFeed project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef LOREMFEED_H
#define LOREMFEED_H

#include <functional>
#include <memory>
#include <random>
#include <type_traits>

namespace LoremFeed {

template <typename FeedType> class FeedIterator {
public:
  explicit FeedIterator(FeedType &feed) : feed(feed) {}

  typename FeedType::value_type operator*() { return feed.get(); }

  void operator++() { feed.next(); }

  bool operator!=(const FeedIterator<FeedType> &otherFeed) {
    return !feed.done();
  }

private:
  FeedType &feed;
};

template <typename FeedType, typename FeedValueType> class FeedInterface {
public:
  virtual FeedValueType get() = 0;
  virtual FeedType &limit(size_t sizeLimit) {
    size = sizeLimit;
    return static_cast<FeedType &>(*this);
  }
  virtual FeedIterator<FeedType> begin() {
    return FeedIterator<FeedType>(static_cast<FeedType &>(*this));
  }
  virtual FeedIterator<FeedType> end() {
    return FeedIterator<FeedType>(static_cast<FeedType &>(*this));
  }
  void next() {
    if (size != 0) {
      current++;
    }
  }
  bool done() { return (size != 0) && (current == size); }

private:
  size_t current = 0;
  size_t size = 10;
};

template <typename FeedValueType, typename Distribution>
class RandomFeed : public FeedInterface<RandomFeed<FeedValueType, Distribution>,
                                        FeedValueType> {
public:
  using value_type = FeedValueType;
  explicit RandomFeed(Distribution &&distribution)
      : generator(randomDevice()),
        distribution(std::forward<Distribution>(distribution)) {}
  value_type get() { return distribution(generator); }

protected:
  std::random_device randomDevice;
  std::mt19937 generator;
  Distribution distribution;
};

template <typename FeedValueType>
RandomFeed<FeedValueType, std::uniform_int_distribution<FeedValueType>>
RandomInteger() {
  return RandomFeed<FeedValueType,
                    std::uniform_int_distribution<FeedValueType>>(
      std::uniform_int_distribution<FeedValueType>(
          std::numeric_limits<FeedValueType>::min(),
          std::numeric_limits<FeedValueType>::max()));
};

template <typename FeedValueType>
RandomFeed<FeedValueType, std::uniform_int_distribution<FeedValueType>>
UniformInteger(FeedValueType min, FeedValueType max) {
  return RandomFeed<FeedValueType,
                    std::uniform_int_distribution<FeedValueType>>(
      std::uniform_int_distribution<FeedValueType>(min, max));
};

template <typename FeedValueType, typename Distribution>
RandomFeed<FeedValueType, Distribution>
RandomByDistribution(Distribution &&distribution) {
  return RandomFeed<FeedValueType, Distribution>(
      std::forward<Distribution>(distribution));
};

/*
// numerically makes no sense
template <typename FeedValueType>
RandomFeed<FeedValueType, std::uniform_real_distribution<FeedValueType>>
RandomFloat() {
  return RandomFeed<FeedValueType,
                   std::uniform_real_distribution<FeedValueType>>(
      std::uniform_real_distribution<FeedValueType>(
          std::numeric_limits<FeedValueType>::min(),
          std::numeric_limits<FeedValueType>::max()));
};
*/

template <typename FeedValueType>
RandomFeed<FeedValueType, std::uniform_real_distribution<FeedValueType>>
UniformFloat(FeedValueType min, FeedValueType max) {
  return RandomFeed<FeedValueType,
                    std::uniform_real_distribution<FeedValueType>>(
      std::uniform_real_distribution<FeedValueType>(min, max));
};

template <typename POD, typename TupleType, std::size_t... Indices>
POD createPod(TupleType const &tupl, std::index_sequence<Indices...> const &) {

  return {std::invoke(std::get<Indices>(tupl))...};
}

template <typename CLASS, typename TupleType, std::size_t... Indices>
CLASS emplaceClass(TupleType const &tupl,
                   std::index_sequence<Indices...> const &) {

  return CLASS(std::invoke(std::get<Indices>(tupl))...);
}

template <typename FeedValueType, typename... FieldFeed>
class PodFeed : public FeedInterface<PodFeed<FeedValueType, FieldFeed...>,
                                     FeedValueType> {
public:
  using value_type = FeedValueType;

  explicit PodFeed(FieldFeed &&... fieldFeed)
      : fieldFeedsPacked{std::forward<FieldFeed>(fieldFeed)...} {}

  value_type get() {
    return createPod<value_type>(
        fieldFeedsPacked, std::make_index_sequence<sizeof...(FieldFeed)>());
  }

private:
  std::tuple<FieldFeed...> fieldFeedsPacked;
};

template <typename FeedValueType, typename... FieldFeed>
PodFeed<FeedValueType, FieldFeed...> Pod(FieldFeed &&... fieldFeed) {
  return PodFeed<FeedValueType, FieldFeed...>(
      std::forward<FieldFeed>(fieldFeed)...);
}

template <typename FeedValueType, typename... FieldFeed>
class EmplaceFeed
    : public FeedInterface<EmplaceFeed<FeedValueType, FieldFeed...>,
                           FeedValueType> {
public:
  using value_type = FeedValueType;

  explicit EmplaceFeed(FieldFeed &&... fieldFeed)
      : fieldFeedsPacked{std::forward<FieldFeed>(fieldFeed)...} {}

  FeedValueType get() {
    return emplaceClass<value_type>(
        fieldFeedsPacked, std::make_index_sequence<sizeof...(FieldFeed)>());
  }

private:
  std::tuple<FieldFeed...> fieldFeedsPacked;
};

template <typename FeedValueType, typename... FieldFeed>
EmplaceFeed<FeedValueType, FieldFeed...> Emplace(FieldFeed &&... fieldFeed) {
  return EmplaceFeed<FeedValueType, FieldFeed...>(
      std::forward<FieldFeed>(fieldFeed)...);
}

std::string generateRandomString(size_t length) {
  static const char alphanum[] = "0123456789"
                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz";

  static auto random = UniformInteger<unsigned int>(0, sizeof(alphanum) - 2);

  std::string ret;
  ret.resize(length);

  for (int i = 0; i < length; ++i) {
    ret[i] = alphanum[random.get()];
  }

  return ret;
}

class StringFeed : public FeedInterface<StringFeed, std::string> {
public:
  using value_type = std::string;

  explicit StringFeed(size_t length) : length(length) {}

  value_type get() { return generateRandomString(length); }

private:
  size_t length;
};

template <typename Distribution>
class RandomLengthStringFeed
    : public FeedInterface<RandomLengthStringFeed<Distribution>, std::string> {
public:
  using value_type = std::string;
  explicit RandomLengthStringFeed(Distribution &&distribution)
      : generator(randomDevice()),
        distribution(std::forward<Distribution>(distribution)) {}
  value_type get() { return generateRandomString(distribution(generator)); }

private:
  std::random_device randomDevice;
  std::mt19937 generator;
  Distribution distribution;
};

RandomLengthStringFeed<std::uniform_int_distribution<size_t>>
RandomLengthString(size_t min, size_t max) {
  return RandomLengthStringFeed<std::uniform_int_distribution<size_t>>(
      std::uniform_int_distribution<size_t>(min, max));
};
}

#endif
