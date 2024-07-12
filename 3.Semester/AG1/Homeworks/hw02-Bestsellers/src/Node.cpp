// #EX_BEGIN
//
// Created by bardanik on 07/11/22.
//

#include "Node.hpp"
// #EX_END

template<typename Key>
Node<Key>::Node(const Key &key)
        : key_(key)
          , height_(0)
          , size_(1)
          , parent_(nullptr)
          , left_(nullptr)
          , right_(nullptr) {}

template<typename Key>
Node<Key>::~Node() {
    delete left_;
    delete right_;
}

template<typename Key>
bool Node<Key>::hasLeft() const {
    return left_ != nullptr;
}

template<typename Key>
bool Node<Key>::hasRight() const {
    return right_ != nullptr;
}

template<typename Key>
bool Node<Key>::isList() const {
    return !hasLeft() && !hasRight();
}

template<typename Key>
void Node<Key>::UpdateHeight() {
    int left = LeftHeight(), right = RightHeight();
    height_ = (left > right ? left : right) + 1;
}

template<typename Key>
int Node<Key>::getWeight() const {
    return LeftHeight() - RightHeight();
}

template<typename Key>
void Node<Key>::UpdateSize() {
    size_ = LeftSize() + RightSize() + 1;
}

template<typename Key>
void Node<Key>::UpdateNode() {
    UpdateHeight();
    UpdateSize();
}

template<typename Key>
size_t Node<Key>::RightSize() const {
    return hasRight() ? right_->size_ : 0;
}

template<typename Key>
size_t Node<Key>::LeftSize() const {
    return hasLeft() ? left_->size_ : 0;
}

template<typename Key>
int Node<Key>::LeftHeight() const {
    return hasLeft() ? left_->height_ : UNDEF_HEIGHT;
}

template<typename Key>
int Node<Key>::RightHeight() const {
    return hasRight() ? right_->height_ : UNDEF_HEIGHT;
}
