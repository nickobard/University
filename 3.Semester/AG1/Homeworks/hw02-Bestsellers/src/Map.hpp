// #PRIOR_4
// #EX_BEGIN
//
// Created by bardanik on 05/11/22.
//

#ifndef HW02_BESTSELLERS_MAP_HPP
#define HW02_BESTSELLERS_MAP_HPP

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

#include "MapNode.hpp"
#include "Set.hpp"
// #EX_END


template<typename Key, typename Value>
class Map {
public:

    Map();

    ~Map();

    void DeleteKey(const Key &key);

    void InsertKey(const Key &key, const Value &value);

    const MapNode<Key, Value> *Find(const Key &key) const;

    size_t size() const;

    bool isEmpty() const;

    bool Contains(const Key &key) const;

    size_t IndexOf(const Key &key) const;

    const MapNode<Key, Value> *at(size_t index) const;

    const MapNode<Key, Value> *Min() const;

    const MapNode<Key, Value> *Max() const;

    const MapNode<Key, Value> *Successor(const MapNode<Key, Value> *current) const;

    const MapNode<Key, Value> *Predecessor(const MapNode<Key, Value> *current) const;

    Value GetRangeSum(size_t from, size_t to) const;


private:

    const MapNode<Key, Value> *FindRangeSubtreeRoot(const MapNode<Key, Value> *current,
                                                    const Key &from,
                                                    const Key &to) const;

    Value GetLeftSubRangeSum(const MapNode<Key, Value> *current, const Key &rangeMin) const;

    Value GetRightSubRangeSum(const MapNode<Key, Value> *current, const Key &rangeMax) const;

    size_t IndexOf(const MapNode<Key, Value> *node, const Key &key) const;

    const MapNode<Key, Value> *at(const MapNode<Key, Value> *node, size_t index) const;

    MapNode<Key, Value> *UpdateAndBalanceNode(MapNode<Key, Value> *node);

    MapNode<Key, Value> *Balance(MapNode<Key, Value> *node);

    MapNode<Key, Value> *RotateLeft(MapNode<Key, Value> *node);

    MapNode<Key, Value> *RotateRight(MapNode<Key, Value> *node);

    bool isBalanced(MapNode<Key, Value> *node) const;

    MapNode<Key, Value> *Delete(MapNode<Key, Value> *node, const Key &key);

    MapNode<Key, Value> *DeleteLeaf(MapNode<Key, Value> *leaf);

    MapNode<Key, Value> *ReplaceWithRight(MapNode<Key, Value> *node);

    MapNode<Key, Value> *ReplaceWithLeft(MapNode<Key, Value> *node);

    MapNode<Key, Value> *ReplaceWithSuccessor(MapNode<Key, Value> *node);

    MapNode<Key, Value> *Insert(MapNode<Key, Value> *node, const Key &key, const Value &value);

    const MapNode<Key, Value> *Find(const MapNode<Key, Value> *node, const Key &key) const;

    const MapNode<Key, Value> *Min(const MapNode<Key, Value> *node) const;

    const MapNode<Key, Value> *Max(const MapNode<Key, Value> *node) const;

    MapNode<Key, Value> *root_;

// #EX_BEGIN
    friend struct MapTester;
// #EX_END
};

// #EX_BEGIN
#include "Map.cpp"

#endif //HW02_BESTSELLERS_MAP_HPP
// #EX_END
