// #EX_BEGIN
//
// Created by bardanik on 07/11/22.
//

#include "MapNode.hpp"
// #EX_END

template<typename Key, typename Value>
MapNode<Key, Value>::MapNode(const Key &key, const Value &value)
        : key_(key)
          , value_(value)
          , subtreeSum_(value)
          , height_(0)
          , size_(1)
          , parent_(nullptr)
          , left_(nullptr)
          , right_(nullptr) {}

template<typename Key, typename Value>
MapNode<Key, Value>::~MapNode() {
    delete left_;
    delete right_;
}

template<typename Key, typename Value>
bool MapNode<Key, Value>::hasLeft() const {
    return left_ != nullptr;
}

template<typename Key, typename Value>
bool MapNode<Key, Value>::hasRight() const {
    return right_ != nullptr;
}

template<typename Key, typename Value>
bool MapNode<Key, Value>::isList() const {
    return !hasLeft() && !hasRight();
}

template<typename Key, typename Value>
void MapNode<Key, Value>::UpdateHeight() {
    int left = LeftHeight(), right = RightHeight();
    height_ = (left > right ? left : right) + 1;
}

template<typename Key, typename Value>
int MapNode<Key, Value>::getWeight() const {
    return LeftHeight() - RightHeight();
}

template<typename Key, typename Value>
void MapNode<Key, Value>::UpdateSize() {
    size_ = LeftSize() + RightSize() + 1;
}

template<typename Key, typename Value>
void MapNode<Key, Value>::UpdateNode() {
    UpdateHeight();
    UpdateSize();
    UpdateSubtreeSum();
}

template<typename Key, typename Value>
size_t MapNode<Key, Value>::RightSize() const {
    return hasRight() ? right_->size_ : 0;
}

template<typename Key, typename Value>
size_t MapNode<Key, Value>::LeftSize() const {
    return hasLeft() ? left_->size_ : 0;
}

template<typename Key, typename Value>
int MapNode<Key, Value>::LeftHeight() const {
    return hasLeft() ? left_->height_ : UNDEF_HEIGHT;
}

template<typename Key, typename Value>
int MapNode<Key, Value>::RightHeight() const {
    return hasRight() ? right_->height_ : UNDEF_HEIGHT;
}

template<typename Key, typename Value>
void MapNode<Key, Value>::UpdateSubtreeSum() {
    subtreeSum_ = LeftSubtreeSum() + RightSubtreeSum() + value_;
}

template<typename Key, typename Value>
Value MapNode<Key, Value>::LeftSubtreeSum() const {
    return hasLeft() ? left_->subtreeSum_ : 0;
}

template<typename Key, typename Value>
Value MapNode<Key, Value>::RightSubtreeSum() const {
    return hasRight() ? right_->subtreeSum_ : 0;

}
