// #PRIOR_6
// #EX_BEGIN
//
// Created by bardanik on 05/11/22.
//

#ifndef HW02_BESTSELLERS_BESTSELLERS_HPP
#define HW02_BESTSELLERS_BESTSELLERS_HPP

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

#include "Map.hpp"

// #EX_END

using Amount = size_t;
using Rank = size_t;
using Products = size_t;

template<typename Product>
class Bestsellers {
public:


    // The total number of tracked products
    Products products() const;

    void sell(const Product &p, Amount amount);

    // The most sold product has rank 1
    Rank rank(const Product &p) const;

    const Product &product(Rank rank) const;

    // How many copies of product with given rank were sold
    Amount sold(Rank rank) const;

    // The same but sum over interval of products (including from and to)
    // It must hold: sold(x) == sold(x, x)
    Amount sold(Rank from, Rank to) const;

    // Bonus only, ignore if you are not interested in bonus
    // The smallest (resp. largest) rank with sold(rank) == sold(r)
    Rank first_same(Rank r) const;

    Rank last_same(Rank r) const;

private:

    Map<pair<Amount , Product>, Amount> amounts_;
    unordered_map<Amount , unique_ptr<Set<Product>>> productsBySameAmount_;
    unordered_map<Product, Amount> products_;

// #EX_BEGIN
    friend struct Tester;
    friend struct BestsellersTester;
// #EX_END

};

// #EX_BEGIN
#include "Bestsellers.cpp"

#endif //HW02_BESTSELLERS_BESTSELLERS_HPP
// #EX_END
