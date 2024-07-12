// #PRIOR_2
// #EX_BEGIN
//
// Created by bardanik on 07/11/22.
//

#ifndef HW02_BESTSELLERS_MAPNODE_HPP
#define HW02_BESTSELLERS_MAPNODE_HPP

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

#include "Node.hpp"
using namespace std;
// #EX_END

template<typename Key, typename Value>
struct MapNode {
    MapNode(const Key &key, const Value &value);

    ~MapNode();

    bool hasLeft() const;

    bool hasRight() const;

    size_t LeftSize() const;

    size_t RightSize() const;

    Value LeftSubtreeSum() const;

    Value RightSubtreeSum() const;


    int LeftHeight() const;

    int RightHeight() const;

    bool isList() const;

    void UpdateNode();

    void UpdateHeight();

    void UpdateSize();

    void UpdateSubtreeSum();

    int getWeight() const;

    Key key_;
    Value value_;
    Value subtreeSum_;
    int height_;
    size_t size_;
    MapNode *parent_;
    MapNode *left_;
    MapNode *right_;

// #EX_BEGIN
    friend struct MapTester;
// #EX_END

};

// #EX_BEGIN
#include "MapNode.cpp"

#endif //HW02_BESTSELLERS_MAPNODE_HPP
// #EX_END
