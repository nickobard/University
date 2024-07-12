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

I have traveled almost the entire world and can confidently say that there is no nation that enjoys Christmas as much as these Whos. From my encounters with the Whos, I have learned that it's not just the anticipation of presents, fun in the snow, and time spent with family and friends. What the Whos feel for Christmas comes from deep within their hearts, and I would dare to call it an instinctive desire or primal need for a happy and peaceful Christmas.

At least, that's the case for most of them. Just like any other group, there are exceptions among the Whos. And I don't mean the Grinch. I'm talking about someone even worse. What could be worse than someone who, out of their own fear and sense of injustice, wants to steal Christmas from these people, you ask? Well, it is someone who exploits these basest human instincts, strengthens fear and uncertainty, and offers simple solutions for everything. And all with one goal - to profit as much as possible. Yes, dear readers, you guessed correctly. It is none other than the esteemed Mayor!

For such a naive nation as the Whos, it is not surprising that the Mayor has been in power for several consecutive terms. Each time winning with more than 99% of the votes. Those of us who have been around for a while are also not surprised that in reality, caring for the village is only a secondary concern for the Mayor. The Mayor owns the largest (and also the only, to be honest) toy store in Whoville. A colossal conflict of interest, one might say! But it doesn't bother the locals.

According to the saying "appetite comes with eating," the Mayor is never satisfied. Last year, he launched an operation called Bestselling Products. This massive digitization of all purchases and analysis of product sales led to a tenfold increase in the Mayor's profits. This year, he plans to continue the digitization and take it to an even higher level. Ladies and gentlemen, welcome Bestselling Products II, an even more monstrous operation aimed at thoroughly emptying the Whos' wallets. The gossips claim that this operation will not only drain their savings but might even steal a small piece of each Who's soul.

And how do you fit into all of this? After all, you are the good guys, and you wouldn't dirty your hands with such wickedness. The truth is, no one other than the town council and the Mayor's toy store will give you a contract. Moreover, you proved yourself last year. Therefore, this year, the implementation of Bestselling Products falls on you.

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

### Scoring Conditions

- For 1 point, you need to functionally implement the above-described interface, but the implementation does not have to be very efficient.

- For 3.5 points, the implementation must be efficient if the number of sold units is random, but the complexity o
