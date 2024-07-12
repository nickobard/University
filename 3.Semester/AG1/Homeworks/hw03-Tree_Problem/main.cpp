#ifndef __PROGTEST__
#include <cassert>
#include <cstdint>
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
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <random>

using ChristmasTree = size_t;

struct TreeProblem {
  int max_group_size;
  std::vector<uint64_t> gifts;
  std::vector<std::pair<ChristmasTree, ChristmasTree>> connections;
};

#endif

using namespace std;

using Neighbours = vector<ChristmasTree>;
using AdjacencyList = vector<Neighbours>;
using Connection = pair<ChristmasTree, ChristmasTree>;
using Connections = vector<Connection>;
using GiftsCount = ::uint64_t;
using DPTable = vector<vector<GiftsCount>>;

constexpr GiftsCount UNDEF_GIFTS_COUNT = -1; // == long max - overflow
constexpr size_t WITH_NO_GUARD = 0;
constexpr size_t WITH_ONE_GUARD = 1;
constexpr size_t WITH_TWO_GUARDS = 2;

class Graph {
public:
    Graph(const TreeProblem &tree)
            : gifts(tree.gifts), maxGroupSize(tree.max_group_size) {
        BuildAdjacencyList(tree.connections);
        graphSize = adjacencyList.size();
        dpTable = DPTable(graphSize, {UNDEF_GIFTS_COUNT, UNDEF_GIFTS_COUNT, UNDEF_GIFTS_COUNT});
    }

    GiftsCount MaxGuardedGiftsCountTwoGuards(ChristmasTree start) {
        stack<Connection> stack;
        GetStackWithFirstLeaves(start, stack);
        while (!stack.empty()) {
            auto [current, parent] = stack.top();
            stack.pop();
            // guard is on this vertex
            GiftsCount maxCountWithoutGuardHere = 0;
            GiftsCount maxCountWithOneGuardHere = gifts[current];
            GiftsCount maxCountWithTwoGuardsHere = gifts[current];

            GiftsCount maxTwoGuardsDifference = 0;

            for (auto child: adjacencyList.at(current)) {
                if (child == parent)
                    continue;

                auto childMaxCountWithNoGuard = dpTable[child][WITH_NO_GUARD];
                auto childMaxCountWithOneGuard = dpTable[child][WITH_ONE_GUARD];
                auto childMaxCountWithTwoGuards = dpTable[child][WITH_TWO_GUARDS];

                maxCountWithoutGuardHere += max(
                        {childMaxCountWithNoGuard, childMaxCountWithOneGuard, childMaxCountWithTwoGuards});
                maxCountWithOneGuardHere += childMaxCountWithNoGuard;
                maxCountWithTwoGuardsHere += childMaxCountWithNoGuard;

                if (childMaxCountWithNoGuard < childMaxCountWithOneGuard) {
                    auto difference = childMaxCountWithOneGuard - childMaxCountWithNoGuard;
                    if (maxTwoGuardsDifference < difference)
                        maxTwoGuardsDifference = difference;
                }

            }

            dpTable[current][WITH_NO_GUARD] = maxCountWithoutGuardHere;
            dpTable[current][WITH_ONE_GUARD] = maxCountWithOneGuardHere;
            dpTable[current][WITH_TWO_GUARDS] = maxCountWithTwoGuardsHere + maxTwoGuardsDifference;
        }
        return max({dpTable[start][WITH_ONE_GUARD], dpTable[start][WITH_NO_GUARD], dpTable[start][WITH_TWO_GUARDS]});
    }

    GiftsCount MaxGuardedGiftsCountOneGuard(ChristmasTree start) {
        stack<Connection> stack;
        GetStackWithFirstLeaves(start, stack);
        while (!stack.empty()) {
            auto [current, parent] = stack.top();
            stack.pop();
            // guard is on this vertex
            GiftsCount maxCountWithGuardHere = gifts[current];
            GiftsCount maxCountWithoutGuardHere = 0;
            for (auto child: adjacencyList.at(current)) {
                if (child == parent)
                    continue;

                auto childMaxCountWithNoGuard = dpTable[child][WITH_NO_GUARD];
                auto childMaxCountWithOneGuard = dpTable[child][WITH_ONE_GUARD];

                maxCountWithGuardHere += childMaxCountWithNoGuard;
                maxCountWithoutGuardHere += max(childMaxCountWithNoGuard, childMaxCountWithOneGuard);
            }

            dpTable[current][WITH_NO_GUARD] = maxCountWithoutGuardHere;
            dpTable[current][WITH_ONE_GUARD] = maxCountWithGuardHere;
        }
        return max(dpTable[start][WITH_ONE_GUARD], dpTable[start][WITH_NO_GUARD]);
    }

    GiftsCount MaxGuardedGiftsCountIterative(ChristmasTree start) {
        if (maxGroupSize == 1) {
            return MaxGuardedGiftsCountOneGuard(start);
        } else {
            return MaxGuardedGiftsCountTwoGuards(start);
        }
    }

private:

    stack<Connection> GetStackWithFirstLeaves(ChristmasTree root, stack<Connection> &stack) {
        queue<Connection> queue;

        queue.emplace(root, root);
        stack.emplace(root, root);

        while (!queue.empty()) {
            auto [current, parent] = queue.front();
            queue.pop();
            for (auto child: adjacencyList[current]) {
                if (child == parent)
                    continue;
                queue.emplace(child, current);
                stack.emplace(child, current);
            }
        }
        return stack;
    }

    void AddNeighbor(ChristmasTree current, ChristmasTree neighbor) {
        while (adjacencyList.size() <= current) {
            adjacencyList.emplace_back();
        }
        adjacencyList[current].emplace_back(neighbor);
    }

    void BuildAdjacencyList(const Connections &connections) {
        for (const Connection &connection: connections) {
            AddNeighbor(connection.first, connection.second);
            AddNeighbor(connection.second, connection.first);
        }
    }

    AdjacencyList adjacencyList;
    size_t graphSize;
    vector<GiftsCount> gifts;
    DPTable dpTable;
    int maxGroupSize;
};


uint64_t solve(const TreeProblem &tree) {
    Graph g(tree);
    return g.MaxGuardedGiftsCountIterative(0);
}

#ifndef __PROGTEST__

using TestCase = std::pair<uint64_t, TreeProblem>;

const std::vector<TestCase> BASIC_TESTS = {
  { 3, { 1, { 1, 1, 1, 2 }, { {0,3}, {1,3}, {2,3} }}},
  { 4, { 1, { 1, 1, 1, 4 }, { {0,3}, {1,3}, {2,3} }}},
  { 57, { 1, {
    17, 11, 5, 13, 8, 12, 7, 4, 2, 8,
  }, {
    {1, 4}, {6, 1}, {2, 1}, {3, 8}, {8, 0}, {6, 0}, {5, 6}, {7, 2}, {0, 9},
  }}},
  { 85, { 1, {
    10, 16, 13, 4, 19, 8, 18, 17, 18, 19, 10,
  }, {
    {9, 7}, {9, 6}, {10, 4}, {4, 9}, {7, 1}, {0, 2}, {9, 2}, {3, 8}, {2, 3}, {5, 4},
  }}},
  { 79, { 1, {
    8, 14, 11, 8, 1, 13, 9, 14, 15, 12, 1, 11,
  }, {
    {9, 1}, {1, 2}, {1, 4}, {5, 10}, {7, 8}, {3, 7}, {11, 3}, {11, 10}, {6, 8}, {0, 1}, {0, 3},
  }}},
  { 102, { 1, {
    15, 10, 18, 18, 3, 4, 18, 12, 6, 19, 9, 19, 10,
  }, {
    {10, 2}, {11, 10}, {6, 3}, {10, 8}, {5, 3}, {11, 1}, {9, 5}, {0, 4}, {12, 3}, {9, 7}, {11, 9}, {4, 12},
  }}},
  { 93, { 1, {
    1, 7, 6, 18, 15, 2, 14, 15, 18, 8, 15, 1, 5, 6,
  }, {
    {0, 13}, {6, 12}, {0, 12}, {7, 8}, {8, 3}, {12, 11}, {12, 1}, {10, 12}, {2, 6}, {6, 9}, {12, 7}, {0, 4}, {0, 5},
  }}},
};

const std::vector<TestCase> BONUS_TESTS = {
  { 3, { 2, { 1, 1, 1, 2 }, { {0,3}, {1,3}, {2,3} }}},
  { 5, { 2, { 1, 1, 1, 4 }, { {0,3}, {1,3}, {2,3} }}},
};

void test(const std::vector<TestCase>& T) {
  int i = 0;
  for (auto &[s, t] : T) {
    if (s != solve(t))
      std::cout << "Error in " << i << " (returned " << solve(t) << ")"<< std::endl;
    i++;
  }
  std::cout << "Finished" << std::endl;
}

int main() {
  test(BASIC_TESTS);
   test(BONUS_TESTS);
}

#endif


