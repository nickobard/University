//
// Created by bardanik on 16/12/22.
//
#include <iostream>
#include <optional>
#include <vector>
#include <cassert>

using namespace std;
using cuts_count = long;
using length = long;
using DPTable = vector<cuts_count>;

constexpr cuts_count UNDEF_CUTS_COUNT = -1;
constexpr cuts_count CANNOT_CUT = -2;

class Solution {
public:
    /**
     * Initializes algorithm.
     * @param ribbon_length - length of the original ribbon.
     * @param a - first cut length.
     * @param b - second cut length.
     * @param c - third cut length.
     * @return maximum count of cuts of ribbon into pieces a, b, c.
     */
    cuts_count get_max_cuts_count(length ribbon_length, length a, length b, length c) {
        // initializing
        ribbon_length_ = ribbon_length;
        a_ = a;
        b_ = b;
        c_ = c;
        dpTable = DPTable(ribbon_length + 1, UNDEF_CUTS_COUNT);
        dpTable[0] = 0; // if length is 0, then no cuts are possible.


//        cuts_count result = solve_recursive(ribbon_length_); // recursive algorithm
        cuts_count result = solve_iterative(); // iterative algorithm
        // if cannot cut original ribbon to a, b, c pieces, then there are 0 of such cuts.
        return result != CANNOT_CUT ? result : 0;
    }


private:

    /**
     * Helper to get precalculated value from DP table of the current length
     * @param current_length of the ribbon.
     * @return maximum of cuts count from DP table.
     * @return CANNOT_CUT if this ribbon cannot be cut into a, b, c pieces or is negative after some cut.
     */
    cuts_count get_cut_counts(length current_length) {
        if (current_length < 0)
            return CANNOT_CUT;
        return dpTable[current_length];
    }

    /**
     * Iteratively try to find all maximum cuts count of ribbon from 0 to original ribbon length.
     * @return maximum count of cuts of current ribbon into a, b, c pieces.
     * @return CANNOT_CUT if cannot cut current ribbon into a, b, c pieces.
     */
    cuts_count solve_iterative() {
        // for 0 we have already defined value in DP table.
        for (length current_length = 1; current_length <= ribbon_length_; current_length++) {

            // get maximum cuts count after each cut.
            cuts_count a_counts = get_cut_counts(current_length - a_);
            cuts_count b_counts = get_cut_counts(current_length - b_);
            cuts_count c_counts = get_cut_counts(current_length - c_);

            // get maximum number of cuts - best option for this ribbon.
            cuts_count max_cuts_count = max({a_counts, b_counts, c_counts});
            // if cannot cut in any of 3 ways, then this ribbon cannot cut at all.
            if (max_cuts_count == CANNOT_CUT) {
                dpTable[current_length] = CANNOT_CUT;
                continue;
            }
            // return max cut count and +1 for current cutting done above.
            dpTable[current_length] = max_cuts_count + 1;
        }
        // return result for original ribbon.
        return dpTable[ribbon_length_];
    }

    /**
     * Recursively try all subtractions from original ribbon length,
     * saves results into DP table and uses them if find same result of subtraction.
     *
     * @param current_length - length of the ribbon (original or with some pieces cut off)
     * @return maximum count of cuts of current ribbon into a, b, c pieces.
     * @return CANNOT_CUT if cannot cut current ribbon into a, b, c pieces.
     */
    cuts_count solve_recursive(length current_length) {
        // check if cut is valid, if not - then return up the CANNOT_CUT signal.
        if (current_length < 0) {
            return CANNOT_CUT;
        }
        // look into DP table if there is some precalculated result.
        if (dpTable[current_length] != UNDEF_CUTS_COUNT) {
            return dpTable[current_length];
        }
        // Try to cut off all 3 possible variants of cut, and store maximum cuts, if can cut.
        cuts_count a_counts = solve_recursive(current_length - a_);
        cuts_count b_counts = solve_recursive(current_length - b_);
        cuts_count c_counts = solve_recursive(current_length - c_);

        // get maximum number of cuts - best option for this ribbon.
        cuts_count max_cuts_count = max({a_counts, b_counts, c_counts});
        // if cannot cut in any of 3 ways, then this ribbon cannot cut at all.
        if (max_cuts_count == CANNOT_CUT)
            return dpTable[current_length] = CANNOT_CUT;
        // return max cut count and +1 for current cutting done above.
        return dpTable[current_length] = max_cuts_count + 1;
    }

    /// original length of the ribbon.
    length ribbon_length_ = 0;
    /// possible cuts.
    length a_ = 0, b_ = 0, c_ = 0;
    /// Table to store already calculated cut combinations.
    DPTable dpTable;

};


int main() {
    Solution s;
#ifndef DEBUG
    length ribbon_length, a, b, c;
    cin >> ribbon_length >> a >> b >> c;
    cout << s.get_max_cuts_count(ribbon_length, a, b, c) << endl;
#endif
#ifdef DEBUG // use -D DEBUG compiler flag option to run asserts.
    cout << "Asserts..." << endl;
    assert(s.get_max_cuts_count(5, 5, 3, 2) == 2);
    assert(s.get_max_cuts_count(23, 100, 120, 123) == 0);
    assert(s.get_max_cuts_count(1, 1, 1, 1) == 1);
    assert(s.get_max_cuts_count(3, 1, 2, 3) == 3);
    assert(s.get_max_cuts_count(4, 1, 2, 3) == 4);
    assert(s.get_max_cuts_count(4000, 1, 2, 3) == 4000);
    assert(s.get_max_cuts_count(4, 2, 1, 4) == 4);
    assert(s.get_max_cuts_count(370, 2, 1, 15) == 370);
    assert(s.get_max_cuts_count(2683, 83, 26, 2709) == 101);
    assert(s.get_max_cuts_count(2600, 83, 26, 2709) == 100);
    assert(s.get_max_cuts_count(442, 83, 26, 2709) == 17);
    assert(s.get_max_cuts_count(525, 83, 26, 2709) == 18);
    assert(s.get_max_cuts_count(2517, 83, 26, 2709));
    assert(s.get_max_cuts_count(2517, 83, 26, 2709));
    assert(s.get_max_cuts_count(2434, 83, 26, 2709));
    assert(s.get_max_cuts_count(1687, 83, 26, 2709));
    assert(s.get_max_cuts_count(857, 83, 26, 2709));
    assert(s.get_max_cuts_count(1604, 83, 26, 2709));


    cout << "Finished." << endl;
#endif
    return 0;
}