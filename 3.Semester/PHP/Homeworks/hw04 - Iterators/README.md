### Code Structure:

```text
.
├── README.md
├── run.php
├── src
│   ├── Iterator
│   │   ├── AbstractOrderIterator.php
│   │   ├── InOrderIterator.php
│   │   ├── PostOrderIterator.php
│   │   └── PreOrderIterator.php
│   └── Node.php
└── trees.php
```


# Task 4

In the `src` directory, there is a class `Node` representing a node of a binary tree. Each node may have a numerical value and left and right children. If a node does not have one of the children, the attribute holds `null`; otherwise, it contains a reference to another `Node`.

The goal is to create implementations of iterators (implementing the [Iterator](https://www.php.net/manual/en/class.iterator.php) interface) for traversing the tree in the following orders:

- in-order,
- pre-order, and
- post-order.

The iterator will allow the tree to be traversed using `foreach`.

## Assignment

1. Implement and register an autoloader that correctly loads classes, including namespaces from the `src` directory. (1 point)
2. Complete the methods in `Iterator\InOrderIterator` for **in-order** traversal. (1 point). You may adjust `Iterator\AbstractOrderIterator` as needed while maintaining the `\Iterator` interface.
3. Complete the methods in `Iterator\PreOrderIterator` and `Iterator\PostOrderIterator` for **pre-order** and **post-order** traversal, respectively. Try to share common code through inheritance. (2 points)
4. Modify the `Node` class to implement [IteratorAggregate](https://www.php.net/manual/en/class.iteratoraggregate.php), defaulting to using `InOrderIterator`. (2 points)

Except for the fourth point, **do not modify** the `Node` class.
