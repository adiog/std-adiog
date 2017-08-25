// This file is a part of cpp-training project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPP_TRAINING_BST_H
#define CPP_TRAINING_BST_H

#include <algorithm>
#include <vector>
#include <memory>

namespace dataStructure {

    template<typename KeyType = int, typename ValueType = int>
    class BinarySearchTree {
        struct Node {
            Node(KeyType &&key, ValueType &&value)
                    : key(std::move(key)), value(std::move(value)) {
            }

            KeyType key;
            ValueType value;
            std::unique_ptr<Node> left;
            std::unique_ptr<Node> right;
        };

        Node *getNode(KeyType key) {
            auto nodePtrPtr = &root;
            while (*nodePtrPtr != nullptr) {
                if (key < (*nodePtrPtr)->key) {
                    nodePtrPtr = &((*nodePtrPtr)->left);
                } else if (key > (*nodePtrPtr)->key) {
                    nodePtrPtr = &((*nodePtrPtr)->right);
                } else {
                    break;
                }
            }
            return nodePtrPtr->get();
        }


    public:
        BinarySearchTree() = default;

        int insert(KeyType &&key, ValueType &&value) {
            auto nodePtrPtr = &root;
            while (*nodePtrPtr != nullptr) {
                if (key < (*nodePtrPtr)->key) {
                    nodePtrPtr = &((*nodePtrPtr)->left);
                } else {
                    nodePtrPtr = &((*nodePtrPtr)->right);
                }
            }
            nodePtrPtr->reset(new Node(std::forward<KeyType>(key), std::forward<ValueType>(value)));
        }

        bool hasKey(KeyType key) {
            return getNode(key) != nullptr;
        }

        ValueType &get(KeyType key) {
            auto nodePtr = getNode(key);
            if (nodePtr == nullptr) {
                throw (std::runtime_error("KeyError"));
            } else {
                return nodePtr->value;
            }
        }

        void print(std::ostream & os) const
        {
            print(os, root.get());
        }

    private:

        void print(std::ostream &os, Node* node) const
        {
            if (node != nullptr){
                print(os, node->left.get());
                os << "(" << node->key << ", " << node->value << ") ";
                print(os, node->right.get());
            }
        }

        std::unique_ptr<Node> root;
    };
}

template<typename KeyType = int, typename ValueType = int>
std::ostream &operator<<(
        std::ostream &os, const dataStructure::BinarySearchTree<KeyType, ValueType> &binaryIndexTree) {
    binaryIndexTree.print(os);

    return os;
}

#endif //CPP_TRAINING_BST_H
