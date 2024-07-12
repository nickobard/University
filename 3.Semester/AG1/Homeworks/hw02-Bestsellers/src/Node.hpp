// #PRIOR_1
// #EX_BEGIN
//
// Created by bardanik on 07/11/22.
//

#ifndef HW02_BESTSELLERS_NODE_HPP
#define HW02_BESTSELLERS_NODE_HPP

#include <random>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <vector>
#include <array>
#include <list>
#include <bitset>
#include <algorithm>
#include <optional>
#include <limits>
#include <memory>
#include <iostream>
#include <cassert>

using namespace std;
// #EX_END

constexpr int UNDEF_HEIGHT = -1;

template<typename Key>
struct Node {
    Node(const Key &key);

    ~Node();

    bool hasLeft() const;

    bool hasRight() const;

    size_t LeftSize() const;

    size_t RightSize() const;

    int LeftHeight() const;

    int RightHeight() const;

    bool isList() const;

    void UpdateNode();

    void UpdateHeight();

    void UpdateSize();

    int getWeight() const;

    Key key_;
    int height_;
    size_t size_;
    Node *parent_;
    Node *left_;
    Node *right_;

// #EX_BEGIN
    friend struct MultiMapTester;
    friend struct SetTester;
// #EX_END

};

// #EX_BEGIN
#include "Node.cpp"

#endif //HW02_BESTSELLERS_NODE_HPP
// #EX_END
