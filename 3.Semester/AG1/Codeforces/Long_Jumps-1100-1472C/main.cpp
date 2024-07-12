//
// Created by bardanik on 17/12/22.
//
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
using Score = long long;
using Scores = vector<Score>;
using Item = long long;
using DPTable = Scores;

constexpr Score UNDEF_SCORE = -1;


class Solution {
public:
    /**
     * Initializer and starter.
     */
    Score get_max_score(Scores scores) {
        // Initialization
        scores_ = std::move(scores);
        dpTable_ = DPTable(scores_.size(), UNDEF_SCORE);

        return get_max_score_iterative(); // iterative
//        return get_max_score_recursive(); // recursive
    }


private:

    /**
     * Get max score iteratively.
     */
    Score get_max_score_iterative() {

        Score score = 0; // initial value

        // iterate from the end to the beginning
        for (Item i = (long long) scores_.size() - 1; i >= 0; i--) {

            Score current = scores_[i]; // score on this item
            Score next_item = i + current; // index of the next item

            if (next_item >= scores_.size()) { // if next item is out of range, save current score to DP table.
                dpTable_[i] = current;
            } else { // if next item is in range, save score of this item plus score of the next item from DP table.
                dpTable_[i] = current + dpTable_[next_item];
            }
            score = max(score, dpTable_[i]); // change score if new result is bigger
        }
        return score;
    }

    /**
     * Starter for recursion.
     */
    Score get_max_score_recursive() {

        Score score = 0; // init value

        for (Item i = 0; i < scores_.size(); i++) { // iterate from start to end
            score = max(score, max_score(i)); // update score if new result is bigger.
        }
        return score;
    }

    /**
     * Get max score of this item.
     * @param i - current item in the scores array.
     */
    Score max_score(Item i) {
        if (dpTable_[i] != UNDEF_SCORE) { // check if this item was precalculated in the DP table.
            return dpTable_[i]; // if yes, return score of this item.
        }
        if (i + scores_[i] >= scores_.size()) { // check if index of the next item is not out of range.
            return dpTable_[i] = scores_[i]; // if is out of range,
                                             // then this item is the last,
                                             // store its score in the DP table
        } else { // or if next item is in range,
                 // then calculate score of next item plus score of this item,
                 // store result  in the DP table
            return dpTable_[i] = max_score(i + scores_[i]) + scores_[i];
        }
    }

    Scores scores_;
    DPTable dpTable_;
};


int main() {
#ifndef DEBUG
    Solution s;
    int tests;
    cin >> tests;
    for (int test = 0; test < tests; test++) {
        Item size;
        Scores scores;
        cin >> size;
        for (Item number = 0; number < size; number++) {
            Score score;
            cin >> score;
            scores.emplace_back(score);
        }
        cout << s.get_max_score(scores) << endl;

    }
#endif
#ifdef DEBUG // Use -D DEBUG compiler option to run asserts instead of reading from stdin.
    cout << "Asserts..." << endl;
    Solution s;
    assert(s.get_max_score({7, 3, 1, 2, 3}) == 7);
    assert(s.get_max_score({2, 1, 4}) == 6);
    assert(s.get_max_score({2, 1000, 2, 3, 995, 1}) == 1000);
    assert(s.get_max_score({1, 1, 1, 1, 1}) == 5);
    assert(s.get_max_score({2, 1, 2, 1, 50}) == 54);
    cout << "Finished." << endl;
#endif
    return 0;
}