#ifndef __PROGTEST__
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <bitset>
#include <list>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>

/// Alias for vertex in the graph.
using Place = size_t;

/**
 * @brief Structure that represents data for graph initialization.
 */
struct Map {
    /// Number of places in the map.
    size_t places;
    /// Start and end of the shortest path to be found.
    Place start, end;
    /// All edges between places vertices, represented as connections.
    std::vector<std::pair<Place, Place>> connections;
    /// Represents all places, where each item can be found.
    std::vector<std::vector<Place>> items;
};

/// Helping hashing function to hash a pair of hashable objects.
template < typename F, typename S >
struct std::hash<std::pair<F, S>> {
    std::size_t operator () (const std::pair<F, S> &p) const noexcept {
        // something like boost::combine would be much better
        return std::hash<F>()(p.first) ^ (std::hash<S>()(p.second) << 1);
    }
};

#endif

using namespace std;

/// Alias for item index.
using Item = size_t;
/// Alias for edge.
using Connection = pair<Place, Place>;
/// Alias for currently stored items, if true - item is present, if false - item is not present.
using PresentItems = vector<bool>;
/// Alias for structure, which stores all places, where each item can be found.
using ItemsLocations = vector<vector<Place>>;
/// Alias for a pair of place (aka vertex) and its level - how many items were taken.
using LeveledVertex = pair<Place, PresentItems>;
/// Alias for structure that for one leveled vertex remembers its parent leveled vertex.
using Predecessors = unordered_map<LeveledVertex, LeveledVertex, hash<LeveledVertex>>;
/// Alias for structure, that remembers all places visited on different levels (with different set of items).
using Visited = unordered_map<Place, list<PresentItems>>;
/// Alias for structure, that stores in queue all leveled vertices to be reviewed by BFS algorithm.
using Queue = queue<LeveledVertex>;


/**
 * @brief Represents graph with items, scattered across all vertices,
 * where each item can be in man places, and many items can be in each place.
 * Provides an algorithm to find shortest path from start to end, where at least
 * one item of each type is taken.
 */
class Graph {

public:
    /**
     * @brief Constructs Graph object.
     * @param map from which to construct graph object.
     */
    explicit Graph(const Map &map);

    /**
     * @brief Represents algorithm to find shortest path from start to end, where at least
     * one item of each type is taken.
     * @param start represents start place of the shortest path.
     * @param end represents end place of the shortest path.
     * @return list of vertices, which represents the shortest path, where vertices can be in path more than once.
     */
    list<Place> AlgorithmBFS(Place start, Place end) const;

private:

    /**
     * @brief Initialize adjacency list.
     * @param connections represents array of connections (edges between places).
     */
    void InitAdjList(const vector<Connection> &connections);

    /**
     * @brief Initialize located items for each place, where is at least one items.
     * @param items represents places where each item can be found.
     */
    void InitItemsLocations(const ItemsLocations &items);

    /**
     * @brief Find the path to the place, from its start ot the end.
     * @param place represents the end of the path.
     * @param predecessors represents all predecessors of the place.
     * @return path to the place, from start.
     */
    list<Place> FindPredecessors(Place place, const Predecessors &predecessors) const;

    /**
     * @brief gets items stored in the specified place.
     * @param place where items may by present.
     * @return items in the place if present, or empty.
     */
    PresentItems getItemsInPlace(Place place) const;

    /**
     * @brief Takes all items from the specified place if there are some to current set of items.
     * @param currentItems represents current set of items.
     * @param at represents place at which to take items, if there are some.
     * @return same set if items if no new items were found, or updated set of items which some new items.
     */
    PresentItems TakeItems(const PresentItems &currentItems, Place at) const;

    /**
     * @brief Checks if every type of the item is actually present in some places.
     * @param items represents places for each item type.
     * @return true, if all types of items are present in graph, false some item type don't have any items in the graph.
     */
    static bool ItemsExistInGraph(const ItemsLocations &items);

    /**
     * @brief Checks if provided set of items has all items.
     * @return true if all items are collected.
     */
    static bool hasAllItems(const PresentItems &presentItems);

    /**
     * @brief Check if provided subset is subset of the superset.
     * @return true if subset is subset of superset.
     */
    static bool isSubset(const PresentItems &subset, const PresentItems &superset);

    /**
     * @brief Check if provided superset is superset of the subset.
     * @return true if superset is superset of subset.
     */
    static bool isSuperset(const PresentItems &superset, const PresentItems &subset);

    static bool InsertToVisited(Visited &visited, Place place, const PresentItems &presentItems);

    /// Represents adjacency list of the graph.
    vector<list<Place>> _adjacencyList;
    /// Represents each place, which have some items.
    unordered_map<Place, PresentItems> _itemsLocations;
    /// Represents number of places in the graph.
    size_t _places;
    /// Represents number of item types in the graph.
    size_t _itemTypes;
};

Graph::Graph(const Map &map)
        : _places(map.places)
          , _itemTypes(map.items.size()) {
    if (!ItemsExistInGraph(map.items))
        throw exception();
    InitAdjList(map.connections);
    InitItemsLocations(map.items);
}

void Graph::InitAdjList(const vector<Connection> &connections) {
    _adjacencyList = vector<list<Place>>(_places);
    for (auto [v, u]: connections) {
        _adjacencyList[v].push_back(u);
        _adjacencyList[u].push_back(v);
    }
}

void Graph::InitItemsLocations(const ItemsLocations &items) {
    for (Item i = 0; i < items.size(); i++) {
        for (Place p: items[i]) {
            if (_itemsLocations.count(p) == 0)
                _itemsLocations[p] = PresentItems(items.size(), false);
            _itemsLocations[p][i] = true;
        }
    }
}

list<Place> Graph::AlgorithmBFS(Place start, Place end) const {

    PresentItems startItems = getItemsInPlace(start);
    if (start == end && hasAllItems(startItems))
        return {start};

    Visited visited;
    Queue queue;
    Predecessors predecessors;

    queue.emplace(start, startItems);
    visited.emplace(start, list<PresentItems>{startItems});

    while (!queue.empty()) {
        auto [vertex, items] = queue.front();
        queue.pop();

        if (vertex == end && hasAllItems(items))
            break;
        for (Place adjacent: _adjacencyList[vertex]) {
            auto withTakenItems = TakeItems(items, adjacent);
            if (InsertToVisited(visited, adjacent, withTakenItems)) {
                queue.emplace(adjacent, withTakenItems);
                predecessors[{adjacent, withTakenItems}] = {vertex, items};
            }

        }
    }

    return FindPredecessors(end, predecessors);
}

bool Graph::ItemsExistInGraph(const ItemsLocations &items) {
    return all_of(items.cbegin(), items.cend(),
                  [](const auto &itemPlaces) -> bool { return !itemPlaces.empty(); });
}

bool Graph::hasAllItems(const PresentItems &presentItems) {
    return all_of(presentItems.begin(), presentItems.end(),
                  [](bool itemIsInPlace) -> bool { return itemIsInPlace; });
}

PresentItems Graph::TakeItems(const PresentItems &currentItems, const Place at) const {
    PresentItems items = getItemsInPlace(at);
    for (Item i = 0; i < _itemTypes; i++)
        if (currentItems[i])
            items[i] = true;
    return items;
}

PresentItems Graph::getItemsInPlace(Place place) const {
    if (_itemsLocations.count(place))
        return _itemsLocations.at(place);
    return PresentItems(_itemTypes, false);
}

list<Place> Graph::FindPredecessors(const Place place, const Predecessors &predecessors) const {
    list<Place> path;
    LeveledVertex predecessor = {place, PresentItems(_itemTypes, true)};
    if (predecessors.count(predecessor))
        path.emplace_front(predecessor.first);
    while (predecessors.count(predecessor)) {
        predecessor = predecessors.at(predecessor);
        path.emplace_front(predecessor.first);
    }
    return path;
}

bool Graph::isSubset(const PresentItems &subset, const PresentItems &superset) {
    for (Item i = 0; i < subset.size(); i++) {
        if (auto hasInSubset = subset[i], hasInSuperset = superset[i];
                hasInSubset && !hasInSuperset)
            return false;
    }
    return true;
}

bool Graph::isSuperset(const PresentItems &superset, const PresentItems &subset) {
    for (Item i = 0; i < superset.size(); i++) {
        if (auto hasInSubset = subset[i], hasInSuperset = superset[i];
                hasInSubset && !hasInSuperset)
            return false;
    }
    return true;
}

bool Graph::InsertToVisited(Visited &visited, const Place place, const PresentItems &presentItems) {
    bool hasInsertedSuperset = false;
    auto &list = visited[place];
    for (auto beg = list.begin(),
                 end = list.end(); beg != end; beg++) {
        if (isSubset(presentItems, *beg))
            return false;
        else if (isSuperset(presentItems, *beg)) {
            if (!hasInsertedSuperset) {
                *beg = presentItems;
                hasInsertedSuperset = true;
            } else {
                auto toDelete = beg--;
                list.erase(toDelete);
            }
        }
    }
    if (!hasInsertedSuperset)
        list.emplace_front(presentItems);
    return true;
}

std::list<Place> find_path(const Map &map) {

    try {
        Graph g(map);
        return g.AlgorithmBFS(map.start, map.end);
    }
    catch (exception &e) {
        return {};
    }
}

#ifndef __PROGTEST__

using TestCase = std::pair<size_t, Map>;

// Class template argument deduction exists since C++17 :-)
const std::array examples = {
//        0
        TestCase{1, Map{2, 0, 0,
                        {{0, 1}},
                        {{0}}
        }},
//        1
        TestCase{3, Map{2, 0, 0,
                        {{0, 1}},
                        {{1}}
        }},
//        2
        TestCase{3, Map{4, 0, 1,
                        {{0, 2}, {2, 3}, {0, 3}, {3, 1}},
                        {}
        }},
//        3
        TestCase{4, Map{4, 0, 1,
                        {{0, 2}, {2, 3}, {0, 3}, {3, 1}},
                        {{2}}
        }},
//        4
        TestCase{0, Map{4, 0, 1,
                        {{0, 2}, {2, 3}, {0, 3}, {3, 1}},
                        {{2}, {}}
        }},
//        5
        TestCase{0, Map{6, 1, 4,
                        {{1, 2}, {2, 3}, {2, 4}},
                        {{5}}
        }},
//        6
        TestCase{7, Map{6, 1, 5,
                        {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}},
                        {{0}, {4}}
        }},
//        7
        TestCase{0, Map{6, 1, 4,
                        {{1, 2}, {2, 3}, {2, 4}},
                        {{5}, {1}, {2}, {3}, {4}}
        }},
//       8
        TestCase{0, Map{6, 1, 4,
                        {},
                        {{5}, {1}, {2}, {3}, {4}}
        }},
//       9
        TestCase{0, Map{6, 1, 1,
                        {},
                        {{5}, {1}, {2}, {3}, {4}}
        }},
//      10
        TestCase{5, Map{5, 0, 2,
                        {{1, 4}, {1, 3}, {2, 3}, {2, 4}, {0, 3}, {0, 4}},
                        {{1, 3}, {3}, {4}}
        }},
//      11
        TestCase{6, Map{6, 2, 4,
                        {{0, 3}, {0, 4}, {0, 5}, {1, 3}, {1, 4}, {1, 5}, {2, 3}, {2, 4}, {2, 5},},
                        {{5}, {5}, {1}, {0, 1}, {0}, {3}, {4}}
        }},
//      12
        TestCase{5, Map{11, 0, 6,
                 {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}, {0, 9}, {9, 10}, {9, 7}, {9, 8}, {8, 6}, {6, 4}, {6, 2},
                  {4, 5}},
                 {{1, 10, 3, 5}, {7, 5}}
        }}

};

int main() {
    int fail = 0;
    for (size_t i = 0; i < examples.size(); i++) {
        auto sol = find_path(examples[i].second);
        if (sol.size() != examples[i].first) {
            std::cout << "Wrong answer for map " << i << std::endl;
            for (auto el : sol)
                std::cout << el << " ";
            std::cout << std::endl;
            fail++;
        }
    }

    if (fail) std::cout << "Failed " << fail << " tests" << std::endl;
    else std::cout << "All tests completed" << std::endl;

    return 0;
}

#endif
