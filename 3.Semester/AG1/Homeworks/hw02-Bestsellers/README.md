## Code Structure:

```text
hw02-Bestsellers
├── CMakeLists.txt
├── guide
│   ├── hw02_for_dummies.md
│   ├── img
│   │   ├── buno.png
│   │   ├── bvs_methods.png
│   │   ├── depth.png
│   │   ├── global.png
│   │   ├── index.png
│   │   ├── local.png
│   │   ├── local_root.png
│   │   ├── subtree_size.png
│   │   ├── subtree_sum.png
│   │   └── wtf.png
│   └── tests
│       ├── BestsellersTester.hpp
│       ├── MapTester.hpp
│       └── SetTester.hpp
├── main.cpp
├── README.md
└── src
    ├── Bestsellers.cpp
    ├── Bestsellers.hpp
    ├── BestsellersTester.hpp
    ├── Map.cpp
    ├── Map.hpp
    ├── MapNode.cpp
    ├── MapNode.hpp
    ├── MapTester.hpp
    ├── Node.cpp
    ├── Node.hpp
    ├── Set.cpp
    ├── Set.hpp
    └── SetTester.hpp

```

[hw02_for_dummies.md](guide/hw02_for_dummies.md) - my guide for classmates to help them solve this task.

## Bestsellers

### Program Interface

Your task is to implement a template class `Bestsellers` parameterized by the type `Product`, which serves as an identifier for individual products. It is promised that the `Product` type has a copy constructor (and assignment operator), destructor, comparison operators, and `std::hash` implemented. The `Bestsellers` class must implement the following public methods:

- `size_t products() const` returning the number of recorded types of goods (not the number of sold units),

- `void sell(const Product& p, size_t amount)` which records the sale of `amount` units of product `p`,

- `size_t rank(const Product& p) const` which returns the rank of the best-selling product starting from 1 (if multiple products have the same sales, you can rank them arbitrarily),

- `const Product& product(size_t rank) const` the inverse function to `rank` (so if no exception occurs, it always holds that `product(rank(p)) == p` and `rank(product(r)) == r`),

- `size_t sold(size_t r) const` the number of sold units of the `r`-th best-selling product,

- `size_t sold(size_t from, size_t to) const` analogous to the single-parameter version but returns the total number of sold units over the interval from `from` to `to` (including both bounds; so `sold(r, r) == sold(r)` and `sold(1, products())` is the total number of sold units across all types of goods; input `to < from` is considered invalid).

Just a bonus: `size_t first_same(size_t r) const` and `size_t last_same(size_t r) const` return the smallest (or largest, respectively) rank `r'`, for which it holds that `sold(r') == sold(r)`. These methods are used only in the bonus test. If you do not address the bonus, leave the default implementation that always returns 0.

If the arguments of the call are invalid (i.e., rank out of bounds or unknown product in the `rank` method), throw a `std::out_of_range` exception.

## Point Conditions

- To earn 1 point, you need to functionally implement the above-described interface, but the implementation does not have to be very efficient.

- To earn 3.5 points, the implementation must be efficient if the number of sold items is random, but the complexity of the `sold(from, to)` method may depend on `to - from`.

- To earn 7 points, the implementation must be efficient, but the complexity of the `sold(from, to)` method can still depend on `to - from`.

- To earn 10 points, the `sold(from, to)` method must be efficient even with a large `to - from`.

- Bonus: To earn 12 points, the `first_same` and `last_same` methods must be correctly and efficiently implemented.
