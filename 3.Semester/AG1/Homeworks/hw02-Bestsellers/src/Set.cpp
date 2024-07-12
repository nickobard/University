// #EX_BEGIN
//
// Created by bardanik on 05/11/22.
//

#include "Set.hpp"
// #EX_END

template<typename Key>
Set<Key>::Set()
        : root_(nullptr) {}

template<typename Key>
void Set<Key>::InsertKey(const Key &key) {
    root_ = Insert(root_, key);
}

template<typename Key>
Node<Key> *Set<Key>::Insert(Node<Key> *node, const Key &key) {
    if (node == nullptr) {
        node = new Node(key);
        return node;
    }
    if (key == node->key_) {
        return node;
    } else if (key < node->key_) {
        node->left_ = Insert(node->left_, key);
        node->left_->parent_ = node;
    } else {
        node->right_ = Insert(node->right_, key);
        node->right_->parent_ = node;
    }
    return UpdateAndBalanceNode(node);
}

template<typename Key>
Set<Key>::~Set() {
    delete root_;
}

template<typename Key>
const Node<Key> *Set<Key>::Find(const Key &key) const {
    return Find(root_, key);
}

template<typename Key>
const Node<Key> *Set<Key>::Find(const Node<Key> *node, const Key &key) const {
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

template<typename Key>
bool Set<Key>::Contains(const Key &key) const {
    if (Find(key) != nullptr) {
        return true;
    }
    return false;
}

template<typename Key>
bool Set<Key>::isEmpty() const {
    return root_ == nullptr;
}

template<typename Key>
size_t Set<Key>::size() const {
    return root_ == nullptr ? 0 : root_->size_;
}

template<typename Key>
const Node<Key> *Set<Key>::Min(const Node<Key> *node) const {
    if (node->hasLeft()) {
        return Min(node->left_);
    } else {
        return node;
    }
}

template<typename Key>
const Node<Key> *Set<Key>::Max(const Node<Key> *node) const {
    if (node->hasRight()) {
        return Max(node->right_);
    } else {
        return node;
    }
}

template<typename Key>
const Node<Key> *Set<Key>::Successor(const Node<Key> *current) const {
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

template<typename Key>
const Node<Key> *Set<Key>::Predecessor(const Node<Key> *current) const {
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

template<typename Key>
const Node<Key> *Set<Key>::Min() const {
    return Min(root_);
}

template<typename Key>
const Node<Key> *Set<Key>::Max() const {
    return Max(root_);
}

template<typename Key>
void Set<Key>::DeleteKey(const Key &key) {
    root_ = Delete(root_, key);
}

template<typename Key>
Node<Key> *Set<Key>::DeleteLeaf(Node<Key> *leaf) {
    delete leaf;
    return nullptr;
}

template<typename Key>
Node<Key> *Set<Key>::Delete(Node<Key> *node, const Key &key) {
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

template<typename Key>
Node<Key> *Set<Key>::ReplaceWithRight(Node<Key> *node) {
    auto right = node->right_;
    right->parent_ = node->parent_;
    node->right_ = nullptr;
    delete node;
    return right;
}

template<typename Key>
Node<Key> *Set<Key>::ReplaceWithLeft(Node<Key> *node) {
    auto left = node->left_;
    left->parent_ = node->parent_;
    node->left_ = nullptr;
    delete node;
    return left;
}

template<typename Key>
Node<Key> *Set<Key>::ReplaceWithSuccessor(Node<Key> *node) {
    auto successor = Successor(node);
    node->key_ = successor->key_;
    node->right_ = Delete(node->right_, successor->key_);
    return node;
}

template<typename Key>
bool Set<Key>::isBalanced(Node<Key> *node) const {
    int weight = node->getWeight();
    return weight >= -1 && weight <= 1;
}

template<typename Key>
Node<Key> *Set<Key>::Balance(Node<Key> *node) {
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

template<typename Key>
Node<Key> *Set<Key>::RotateLeft(Node<Key> *node) {
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

template<typename Key>
Node<Key> *Set<Key>::RotateRight(Node<Key> *node) {
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

template<typename Key>
Node<Key> *Set<Key>::UpdateAndBalanceNode(Node<Key> *node) {
    node->UpdateNode();
    if (!isBalanced(node)) {
        return Balance(node);
    }
    return node;
}

template<typename Key>
const Node<Key> *Set<Key>::at(size_t index) const {
    return at(root_, index);
}

template<typename Key>
const Node<Key> *Set<Key>::at(const Node<Key> *node, size_t index) const {
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

template<typename Key>
size_t Set<Key>::IndexOf(const Key &key) const {
    return IndexOf(root_, key);
}

template<typename Key>
size_t Set<Key>::IndexOf(const Node<Key> *node, const Key &key) const {
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

