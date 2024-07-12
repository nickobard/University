// #EX_BEGIN
//
// Created by bardanik on 05/11/22.
//

#include "Bestsellers.hpp"
#include "Map.hpp"
// #EX_END

template<typename Product>
Products Bestsellers<Product>::products() const {
    return products_.size();
}

template<typename Product>
void Bestsellers<Product>::sell(const Product &p, Amount amount) {
    auto productEntry = products_.find(p);
    if (productEntry == products_.end()) {
        products_.emplace(p, amount);

        auto item = productsBySameAmount_.find(amount);
        if (item != productsBySameAmount_.end()) {
            item->second->InsertKey(p);
        } else {
            auto set = new Set<Product>;
            set->InsertKey(p);
            productsBySameAmount_.emplace(amount, unique_ptr<Set<Product>>(set));
        }

        amounts_.InsertKey({amount, p}, amount);
    } else {
        amounts_.DeleteKey({productEntry->second, p});
        auto item = productsBySameAmount_.find(productEntry->second);
        productEntry->second += amount;
        amounts_.InsertKey({productEntry->second, p}, productEntry->second);

        item->second->DeleteKey(p);
        if (item->second->isEmpty()) {
            productsBySameAmount_.erase(item->first);
        }
        auto moveToItem = productsBySameAmount_.find(productEntry->second);
        if (moveToItem == productsBySameAmount_.end()) {
            auto set = new Set<Product>;
            set->InsertKey(p);
            productsBySameAmount_.emplace(productEntry->second, unique_ptr<Set<Product>>(set));
        } else {
            moveToItem->second->InsertKey(p);
        }
    }
}

template<typename Product>
Rank Bestsellers<Product>::rank(const Product &p) const {
    auto productEntry = products_.find(p);
    if (productEntry == products_.end()) {
        throw out_of_range("Product doesn't exist.");
    }
    return amounts_.IndexOf({productEntry->second, p}) + 1;
}

template<typename Product>
const Product &Bestsellers<Product>::product(Rank rank) const {
    if (rank > products() || rank < 1) {
        throw out_of_range("Rank doesn't exist.");
    }
    return amounts_.at(rank - 1)->key_.second;
}

template<typename Product>
Amount Bestsellers<Product>::sold(Rank rank) const {
    if (rank > products() || rank < 1) {
        throw out_of_range("Rank doesn't exist.");
    }

    return amounts_.at(rank - 1)->value_;
}

template<typename Product>
Amount Bestsellers<Product>::sold(Rank from, Rank to) const {
    if (from > to || from < 1 || to > products()) {
        throw out_of_range("Invalid range from and to.");
    }
    return amounts_.GetRangeSum(from - 1, to - 1);
}

template<typename Product>
Rank Bestsellers<Product>::first_same(Rank r) const {
    if (r > products() || r < 1) {
        throw out_of_range("Rank doesn't exist.");
    }
    const Product &prod = product(r);
    Amount amountOfProduct = amounts_.at(r - 1)->value_;
    auto &set = productsBySameAmount_.find(amountOfProduct)->second;
    auto localRank = set->IndexOf(prod) + 1;
    return r - localRank + 1;
}

template<typename Product>
Rank Bestsellers<Product>::last_same(Rank r) const {
    if (r > products() || r < 1) {
        throw out_of_range("Rank doesn't exist.");
    }
    const Product &prod = product(r);
    Amount amountOfProduct = amounts_.at(r - 1)->value_;
    auto &set = productsBySameAmount_.find(amountOfProduct)->second;
    auto localRank = set->IndexOf(prod) + 1;
    return r + (set->size() - localRank);
}
