// #PRIOR_3
// #EX_BEGIN
//
// Created by bardanik on 05/11/22.
//

#ifndef HW02_BESTSELLERS_SET_HPP
#define HW02_BESTSELLERS_SET_HPP

#include <cassert>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <bitset>
#include <list>
#include <array>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <random>

using namespace std;

#include "Node.hpp"
// #EX_END


template<typename Key>
class Set {
public:

    Set();

    ~Set();

    void DeleteKey(const Key &key);

    void InsertKey(const Key &key);

    const Node<Key> *Find(const Key &key) const;

    size_t size() const;

    bool isEmpty() const;

    bool Contains(const Key &key) const;

    size_t IndexOf(const Key &key) const;

    const Node<Key> *at(size_t index) const;

    const Node<Key> *Min() const;

    const Node<Key> *Max() const;

    const Node<Key> *Successor(const Node<Key> *current) const;

    const Node<Key> *Predecessor(const Node<Key> *current) const;

private:

    size_t IndexOf(const Node<Key> *node, const Key &key) const;

    const Node<Key> *at(const Node<Key> *node, size_t index) const;

    Node<Key> *UpdateAndBalanceNode(Node<Key> *node);

    Node<Key> *Balance(Node<Key> *node);

    Node<Key> *RotateLeft(Node<Key> *node);

    Node<Key> *RotateRight(Node<Key> *node);

    bool isBalanced(Node<Key> *node) const;

    Node<Key> *Delete(Node<Key> *node, const Key &key);

    Node<Key> *DeleteLeaf(Node<Key> *leaf);

    Node<Key> *ReplaceWithRight(Node<Key> *node);

    Node<Key> *ReplaceWithLeft(Node<Key> *node);

    Node<Key> *ReplaceWithSuccessor(Node<Key> *node);

    Node<Key> *Insert(Node<Key> *node, const Key &key);

    const Node<Key> *Find(const Node<Key> *node, const Key &key) const;

    const Node<Key> *Min(const Node<Key> *node) const;

    const Node<Key> *Max(const Node<Key> *node) const;

    Node<Key> *root_;

// #EX_BEGIN
    friend struct MultiMapTester;
    friend struct SetTester;
// #EX_END
};

// #EX_BEGIN
#include "Set.cpp"

#endif //HW02_BESTSELLERS_SET_HPP
// #EX_END
