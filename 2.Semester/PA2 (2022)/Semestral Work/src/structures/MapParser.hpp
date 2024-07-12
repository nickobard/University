#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "Vector2.hpp"
#include "../game_objects/Tile.hpp"
#include "MapReader.hpp"

using namespace std;

/// Structure that represents information about tile.
struct TileInfo {

    /// Type of the tile.
    TileType type_ = TileType::NONE;
    /// Option feature of the tile.
    TileOption option_ = TileOption::NONE;
    /// Position of the tile in pixels.
    Vector2<float> position_ = Vector2<float>::Zero();
    /// Direction of the tile.
    Vector2<float> direction_ = Vector2<float>::Zero();

};

/**
 * @brief Class that parses tile data objects to tile info objects,
 * used for building tiles.
 */
class MapParser {

public:

    /**
     * @brief Constructs map parser object.
     */
    MapParser() = default;

    /**
     * @brief Constructs map parser object and parses tile data to tile info.
     * @param tilesData represents collection of tile data objects used for parsing.
     */
    explicit MapParser(const vector<vector<TileData>> &tilesData);

    /**
     * @brief Parses tile data collection to tile info collection.
     * @param tilesData represents collection of tile data objects used for parsing.
     * @return true if successfully parsed.
     * @return false if failed to parse.
     */
    bool ParseMap(const vector<vector<TileData>> &tilesData);

    /// Gets parsed tiles info collection.
    inline const vector<vector<TileInfo>> &GetTilesInfo() const;

private:

    /**
     * @brief Parses tile data to tile info and returns tile info object.
     * @param tileData represents data to be parsed.
     * @param tilePos represents position of the tile in the game map, not in pixels.
     * @return parsed tile info object.
     */
    static TileInfo ParseTile(TileData tileData, const Vector2<int> &tilePos);

    /**
     * @brief Parse char tile type to enum value TileType.
     * @param tileType represents type of the tile.
     * @return enum value of the TileType.
     */
    static TileType ParseTileType(char tileType);

    /**
     * @brief Parse char tile option to enum value TileOption.
     * @param tileOption represents option of the tile.
     * @return enum value of the TileOption.
     */
    static TileOption ParseOptionType(char tileOption);

    /**
     * @brief Parse char tile direction to vector2 representation.
     * @param tileDirection represents direction of the tile.
     * @return Vector2 object with direction of the tile.
     */
    static Vector2<float> ParseTileDirection(char tileDirection);

    /**
     * @brief Parse tile position in game map to pixels representation.
     * @param tilePosition represents position of the tile in the game map.
     * @return pixels representation of the tile position.
     */
    static Vector2<float> ParseTilePosition(const Vector2<int> &tilePosition);

    /// 2D array of tile info structures with information about each tile.
    vector<vector<TileInfo>> tilesInfo;
};

inline const vector<vector<TileInfo>> &MapParser::GetTilesInfo() const {
    return tilesInfo;
}