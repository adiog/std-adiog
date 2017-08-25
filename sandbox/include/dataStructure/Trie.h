// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPP_TRAINING_TRIE_H
#define CPP_TRAINING_TRIE_H

#include <array>
#include <memory>

namespace dataStructure {

template <typename T, typename Key = std::string>
class TrieNode {
  public:
    TrieNode() {}

    T* find(const Key& key) { return find(key.begin(), key.end()); }

    T& operator[](const Key& key) { return get(key.begin(), key.end()); }

    template <typename... Args>
    void emplace(const Key& key, Args&&... args) {
        return get(key.begin(), key.end(), std::forward(args)...);
    }

  private:
    template <typename ForwardIt>
    T* find(ForwardIt begin, ForwardIt end) {
        if (begin < end) {
            auto uc = static_cast<UChar>(*begin);
            if (nodes[uc] == nullptr) {
                return nullptr;
            }
            begin++;
            return nodes[uc]->find(begin, end);

        } else {
            return ptr.get();
        }
    }

    template <typename ForwardIt>
    T& get(ForwardIt begin, ForwardIt end) {
        if (begin < end) {
            auto uc = static_cast<UChar>(*begin);
            if (nodes[uc] == nullptr) {
                nodes[uc].reset(new TrieNode<T>());
            }
            begin++;
            return nodes[uc]->get(begin, end);

        } else {
            if (!ptr) {
                ptr = std::make_unique<T>();
            }
            return *ptr;
        }
    }

    template <typename ForwardIt, typename... Args>
    void emplace(ForwardIt begin, ForwardIt end, Args&&... args) {
        if (begin < end) {
            auto uc = static_cast<UChar>(*begin);
            if (nodes[uc] == nullptr) {
                nodes[uc].reset(new TrieNode<T>());
            }
            begin++;
            nodes[uc]->emplace(begin, end, std::forward(args)...);

        } else {
            if (!ptr) {
                ptr = std::make_unique<T>(std::forward(args)...);
            }
            return *ptr;
        }
    }

  private:
    using Char = typename Key::value_type;
    using UChar = typename std::make_unsigned<Char>::type;

    static const size_t nodes_size = 1U << (8U * sizeof(UChar));

    std::array<std::unique_ptr<TrieNode<T>>, nodes_size> nodes;
    std::unique_ptr<T> ptr;
};

template <typename T, typename Key = std::string>
using Trie = typename TrieNode<T, Key>;
}

#endif  // CPP_TRAINING_TRIE_H
