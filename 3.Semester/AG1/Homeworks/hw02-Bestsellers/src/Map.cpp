// #EX_BEGIN
//
// Created by bardanik on 05/11/22.
//

#include "Map.hpp"
// #EX_END

template<typename Key, typename Value>
Map<Key, Value>::Map()
        : root_(nullptr) {}

template<typename Key, typename Value>
void Map<Key, Value>::InsertKey(const Key &key, const Value &value) {
    root_ = Insert(root_, key, value);
}

template<typename Key, typename Value>
MapNode<Key, Value> *
Map<Key, Value>::Insert(MapNode<Key, Value> *node, const Key &key, const Value &value) {
    if (node == nullptr) {
        node = new MapNode<Key, Value>(key, value);
        return node;
    }
    if (key == node->key_) {
        return node;
    } else if (key < node->key_) {
        node->left_ = Insert(node->left_, key, value);
        node->left_->parent_ = node;
    } else {
        node->right_ = Insert(node->right_, key, value);
        node->right_->parent_ = node;
    }
    return UpdateAndBalanceNode(node);
}

template<typename Key, typename Value>
Map<Key, Value>::~Map() {
    delete root_;
}

template<typename Key, typename Value>
const MapNode<Key, Value> *Map<Key, Value>::Find(const Key &key) const {
    return Find(root_, key);
}

template<typename Key, typename Value>
const MapNode<Key, Value> *Map<Key, Value>::Find(const MapNode<Key, Value> *node, const Key &key) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (key == node->key_) {
        return node;
    } else if (key < node->key_) {
        return Find(node->left_, key);
    } else {
        return Find(node->right_, key);
    }
}

template<typename Key, typename Value>
bool Map<Key, Value>::Contains(const Key &key) const {
    if (Find(key) != nullptr) {
        return true;
    }
    return false;
}

template<typename Key, typename Value>
bool Map<Key, Value>::isEmpty() const {
    return root_ == nullptr;
}

template<typename Key, typename Value>
size_t Map<Key, Value>::size() const {
    return root_ == nullptr ? 0 : root_->size_;
}

template<typename Key, typename Value>
const MapNode<Key, Value> *Map<Key, Value>::Min(const MapNode<Key, Value> *node) const {
    if (node->hasLeft()) {
        return Min(node->left_);
    } else {
        return node;
    }
}

template<typename Key, typename Value>
const MapNode<Key, Value> *Map<Key, Value>::Max(const MapNode<Key, Value> *node) const {
    if (node->hasRight()) {
        return Max(node->right_);
    } else {
        return node;
    }
}

template<typename Key, typename Value>
const MapNode<Key, Value> *Map<Key, Value>::Successor(const MapNode<Key, Value> *current) const {
    if (current->hasRight()) {
        return Min(current->right_);
    }
    auto successor = current->parent_;
    while (successor != nullptr && current == successor->right_) {
        current = successor;
        successor = successor->parent_;
    }
    return successor;
}

template<typename Key, typename Value>
const MapNode<Key, Value> *Map<Key, Value>::Predecessor(const MapNode<Key, Value> *current) const {
    if (current->hasLeft()) {
        return Max(current->left_);
    }
    auto predecessor = current->parent_;
    while (predecessor != nullptr && current == predecessor->left_) {
        current = predecessor;
        predecessor = predecessor->parent_;
    }
    return predecessor;
}

template<typename Key, typename Value>
const MapNode<Key, Value> *Map<Key, Value>::Min() const {
    return Min(root_);
}

template<typename Key, typename Value>
const MapNode<Key, Value> *Map<Key, Value>::Max() const {
    return Max(root_);
}

template<typename Key, typename Value>
void Map<Key, Value>::DeleteKey(const Key &key) {
    root_ = Delete(root_, key);
}

template<typename Key, typename Value>
MapNode<Key, Value> *Map<Key, Value>::DeleteLeaf(MapNode<Key, Value> *leaf) {
    delete leaf;
    return nullptr;
}

template<typename Key, typename Value>
MapNode<Key, Value> *Map<Key, Value>::Delete(MapNode<Key, Value> *node, const Key &key) {
    if (node == nullptr) {
        return nullptr;
    } else if (key < node->key_) {
        node->left_ = Delete(node->left_, key);
    } else if (key > node->key_) {
        node->right_ = Delete(node->right_, key);
    } else if (key == node->key_) {
        if (node->isList()) {
            return DeleteLeaf(node);
        } else if (!node->hasLeft()) {
            return ReplaceWithRight(node);
        } else if (!node->hasRight()) {
            return ReplaceWithLeft(node);
        } else {
            node = ReplaceWithSuccessor(node);
        }
    }
    return UpdateAndBalanceNode(node);
}

template<typename Key, typename Value>
MapNode<Key, Value> *Map<Key, Value>::ReplaceWithRight(MapNode<Key, Value> *node) {
    auto right = node->right_;
    right->parent_ = node->parent_;
    node->right_ = nullptr;
    delete node;
    return right;
}

template<typename Key, typename Value>
MapNode<Key, Value> *Map<Key, Value>::ReplaceWithLeft(MapNode<Key, Value> *node) {
    auto left = node->left_;
    left->parent_ = node->parent_;
    node->left_ = nullptr;
    delete node;
    return left;
}

template<typename Key, typename Value>
MapNode<Key, Value> *Map<Key, Value>::ReplaceWithSuccessor(MapNode<Key, Value> *node) {
    auto successor = Successor(node);
    node->key_ = successor->key_;
    node->value_ = successor->value_;
    node->right_ = Delete(node->right_, successor->key_);
    return node;
}

template<typename Key, typename Value>
bool Map<Key, Value>::isBalanced(MapNode<Key, Value> *node) const {
    int weight = node->getWeight();
    return weight >= -1 && weight <= 1;
}

template<typename Key, typename Value>
MapNode<Key, Value> *Map<Key, Value>::Balance(MapNode<Key, Value> *node) {
    if (node->getWeight() < -1) {
        if (node->getWeight() + node->right_->getWeight() == -1) {
            node->right_ = RotateRight(node->right_);
        }
        return RotateLeft(node);
    } else {
        if (node->getWeight() + node->left_->getWeight() == 1) {
            node->left_ = RotateLeft(node->left_);
        }
        return RotateRight(node);
    }
}

template<typename Key, typename Value>
MapNode<Key, Value> *Map<Key, Value>::RotateLeft(MapNode<Key, Value> *node) {
    auto right = node->right_;
    node->right_ = right->left_;
    right->left_ = node;
    if (node->hasRight()) {
        node->right_->parent_ = node;
    }
    right->parent_ = node->parent_;
    node->parent_ = right;
    if (root_ == node) {
        root_ = right;
    }
    node->UpdateNode();
    right->UpdateNode();
    return right;
}

template<typename Key, typename Value>
MapNode<Key, Value> *Map<Key, Value>::RotateRight(MapNode<Key, Value> *node) {
    auto left = node->left_;
    node->left_ = left->right_;
    left->right_ = node;
    if (node->hasLeft()) {
        node->left_->parent_ = node;
    }
    left->parent_ = node->parent_;
    node->parent_ = left;
    if (root_ == node) {
        root_ = left;
    }
    node->UpdateNode();
    left->UpdateNode();
    return left;
}

template<typename Key, typename Value>
MapNode<Key, Value> *Map<Key, Value>::UpdateAndBalanceNode(MapNode<Key, Value> *node) {
    node->UpdateNode();
    if (!isBalanced(node)) {
        return Balance(node);
    }
    return node;
}

template<typename Key, typename Value>
const MapNode<Key, Value> *Map<Key, Value>::at(size_t index) const {
    return at(root_, index);
}

template<typename Key, typename Value>
const MapNode<Key, Value> *Map<Key, Value>::at(const MapNode<Key, Value> *node, size_t index) const {
    if (node == nullptr) {
        throw out_of_range("Key does not exists.");
    }
    if (index < node->RightSize()) {
        return at(node->right_, index);
    } else if (index > node->size_ - node->LeftSize() - 1) {
        return at(node->left_, index - node->RightSize() - 1);
    } else {
        return node;
    }

}

template<typename Key, typename Value>
size_t Map<Key, Value>::IndexOf(const Key &key) const {
    return IndexOf(root_, key);
}

template<typename Key, typename Value>
size_t Map<Key, Value>::IndexOf(const MapNode<Key, Value> *node, const Key &key) const {
    if (node == nullptr) {
        throw out_of_range("Key does not exists.");
    }
    if (key == node->key_) {
        return node->RightSize();
    } else if (key > node->key_) {
        return IndexOf(node->right_, key);
    } else {
        return IndexOf(node->left_, key) + node->RightSize() + 1;
    }
}

template<typename Key, typename Value>
const MapNode<Key, Value> *Map<Key, Value>::FindRangeSubtreeRoot(const MapNode<Key, Value> *current,
                                                                 const Key &from,
                                                                 const Key &to) const {
    if (current == nullptr) {
        throw out_of_range("Invalid range.");
    }
    if (current->key_ > from) {
        return FindRangeSubtreeRoot(current->left_, from, to);
    } else if (current->key_ < to) {
        return FindRangeSubtreeRoot(current->right_, from, to);
    } else {
        return current;
    }

}

template<typename Key, typename Value>
Value Map<Key, Value>::GetRangeSum(size_t from, size_t to) const {
    const MapNode<Key, Value> *rangeMin = at(to);
    const MapNode<Key, Value> *rangeMax = at(from);
    auto localRoot = FindRangeSubtreeRoot(root_, rangeMax->key_, rangeMin->key_);
    Value rangeSum = localRoot->value_;
    if (localRoot != rangeMin) {
        rangeSum += GetLeftSubRangeSum(localRoot->left_, rangeMin->key_);
    }
    if (localRoot != rangeMax) {
        rangeSum += GetRightSubRangeSum(localRoot->right_, rangeMax->key_);
    }
    return rangeSum;
}

template<typename Key, typename Value>
Value Map<Key, Value>::GetLeftSubRangeSum(const MapNode<Key, Value> *current, const Key &rangeMin) const {
    if (current == nullptr) {
        throw out_of_range("Invalid min range.");
    }
    if (current->key_ == rangeMin) {
        return current->value_ + current->RightSubtreeSum();
    } else if (current->key_ > rangeMin) {
        return current->value_ + current->RightSubtreeSum() + GetLeftSubRangeSum(current->left_, rangeMin);
    } else {
        return GetLeftSubRangeSum(current->right_, rangeMin);
    }
}

template<typename Key, typename Value>
Value Map<Key, Value>::GetRightSubRangeSum(const MapNode<Key, Value> *current, const Key &rangeMax) const {
    if (current == nullptr) {
        throw out_of_range("Invalid max range.");
    }
    if (current->key_ == rangeMax) {
        return current->value_ + current->LeftSubtreeSum();
    } else if (current->key_ < rangeMax) {
        return current->value_ + current->LeftSubtreeSum() + GetRightSubRangeSum(current->right_, rangeMax);
    } else {
        return GetRightSubRangeSum(current->left_, rangeMax);
    }
}




