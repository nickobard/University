#pragma once

#include <map>
#include <algorithm>
#include <string>
#include <cmath>

#include "../structures/TileNodeBuilder.hpp"
#include "../structures/MapParser.hpp"
#include "../structures/MapReader.hpp"
#include "../game_objects/NullTile.hpp"
#include "../structures/TileNode.hpp"

constexpr int TILE_SIZE = 20;

/**
 * @brief Class that represents game maps in the game world.
 */
class GameMap {

public:

    /**
     * @brief Constructs game map from the .map file. O(n).
     * @param path to the .map file to be loaded.
     */
    explicit GameMap(const string &path);

    /**
     * @brief Deletes all created tile from map. O(n).
     */
    ~GameMap();

    /**
     * @brief Render on tiles on the map. O(n).
     */
    void RenderMap() const;

    /**
     * @brief Loads game map. O(n), n - number of tiles. O(n)
     * @param path to the map file to read and load map from it.
     */
    void LoadMap(const string &path);

    /**
     * @brief Clears the map - both array and map collections of tiles. O(n).
     */
    void ClearMap();

    /**
     * @brief Get tile center from current position of the game object. O(1).
     * @param position of the game object in pixels.
     * @return center of the supposed tile on which game object currently is.
     */
    static Vector2<int> CentralizePosition(const Vector2<int> &position);

    /**
     * @brief Convert position to pixels representation. O(1).
     * @param position of the tile in integer coordinates representation.
     * @return position in pixels.
     */
    static Vector2<int> GetPixelsPosition(const Vector2<int> &position);

    /// Get map info member.
    inline MapInfo GetMapInfo();

private:

    /**
     * @brief Loads tiles to array for fast iterating and rendering.
     */
    void LoadRenderMap();

    /// Represents 2D linked matrix of tile nodes.
    vector<vector<TileNode *>> tileNodesArray2D_;

    /// Collection of tiles stored in array for rendering.
    vector<Tile *> renderTilesArray_;

    /// Stores information about the map - number of bonuses, spawn points etc.
    MapInfo mapInfo_;

};

inline MapInfo GameMap::GetMapInfo() {
    return mapInfo_;
}