#pragma once

#include "../game_objects/EmptyTile.hpp"
#include "../game_objects/CrossTile.hpp"
#include "../game_objects/WallTile.hpp"
#include "../game_objects/TunnelTile.hpp"
#include "../game_objects/PortalTile.hpp"
#include "MapParser.hpp"

class GameFilesystem;

/// Structure that represents general information about the map.
struct MapInfo {
    /// Represents total number of bonuses in the map.
    int bonuses_ = 0;
    /// Represents player or pacman spawn point.
    TileNode *playerSpawn_ = nullptr;
    /// Represents ghost spawn point.
    TileNode *ghostsSpawn_ = nullptr;
};

/**
 * @brief Represents class that builds all tile nodes using tile info and connects them with each other.
 */
class TileNodeBuilder {

public:

    /**
     * @brief Constructs tile node builder object.
     */
    TileNodeBuilder();

    /**
     * @brief Load tile nodes using tiles info to the tileNodes_ 2D array.
     * @param tilesInfo represents collection of tile info objects.
     * @param header represents map header with information about the map.
     */
    void LoadTileNodes(const vector<vector<TileInfo>> &tilesInfo, const MapHeader &header);

    /**
     * @brief Destroys all loaded tiles if there are any. O(n).
     */
    void ClearTileNodes();

    /// Get reference to the loaded collection of tile nodes.
    inline const vector<vector<TileNode *>> &GetTileNodesMap() const;

    /// Get map info object with information about the loaded map.
    inline MapInfo GetMapInfo() const;

private:

    /**
     * @brief Checks whether spawn points of player and AI are correct.
     * @return true if spawn points are correct and could be set up.
     * @return false if spawn points are incorrect and could not be set up.
     */
    bool CheckSpawnPoints();

    /**
     * @brief Checks whether portal nodes are set up correctly if there are any.
     * @return true if there are no portals or they are set up correctly
     * @return false if there portals are NOT set up correctly.
     */
    bool CheckPortals();

    /**
     * @brief Build tiles form given collection of tile information structures.
     * @param tilesInfo with information about each tile to build.
     */
    void BuildTileNodes(const vector<vector<TileInfo>> &tilesInfo);

    /**
     * @brief Builds tile node using tile info.
     * @param tileInfo represents information about the tile in the map.
     * @return created tile according to tile information structure.
     */
    TileNode *BuildTileNode(const TileInfo &tileInfo);

    /**
     * @brief Connect nodes within 2D array to each other making them linked.
     */
    void ConnectNodes();

    /**
     * @brief Checks and connects portal nodes and tiles if there are any.
     */
    void ConnectPortals();

    /**
     * @brief Connect two giver portal nodes with each other.
     * @param entrance represent portal node which is connected to exit.
     * @param exit represents portal node which to which is connected entrance.
     */
    void ConnectPortal(TileNode *entrance, TileNode *exit);


    /**
     * @brief Builds empty tile.
     * @param tileInfo represents information about tile to build into node.
     */
    TileNode *BuildEmptyTileNode(const TileInfo &tileInfo);

    /**
     * @brief Builds portal tile.
     * @param tileInfo represents information about tile to build into node.
     */
    TileNode *BuildPortalTileNode(const TileInfo &tileInfo);

    /**
     * @brief Builds cross tile.
     * @param tileInfo represents information about tile to build into node.
     */
    TileNode *BuildCrossTileNode(const TileInfo &tileInfo);

    /**
     * @brief Builds wall tile.
     * @param tileInfo represents information about tile to build into node.
     */
    TileNode *BuildWallTileNode(const TileInfo &tileInfo);

    /**
     * @brief Builds tunnel tile.
     * @param tileInfo represents information about tile to build into node.
     */
    TileNode *BuildTunnelTileNode(const TileInfo &tileInfo);

    /**
     * @brief Builds null tile.
     * @param tileInfo represents information about tile to build into node.
     */
    TileNode *BuildNullTileNode(const TileInfo &tileInfo);

    /**
     * @brief Checks and sets up spawn point nodes in the game map.
     */
    void AddSpawns();

    /**
     * @brief Add option to the tile node.
     * @param tileNode to which add some tile option.
     * @param option represents optional feature of the tile, like having bonus etc.
     */
    void AddOption(TileNode *tileNode, TileOption option);

    /// Loaded tiles nodes.
    vector<vector<TileNode *>> tileNodes_;
    /// Header of the map with important information about the map.
    MapHeader header_;
    /// Information about the map.
    MapInfo mapInfo_;
    /// Filesystem from game service locator.
    GameFilesystem &filesystem_;
};

inline const vector<vector<TileNode *>> &TileNodeBuilder::GetTileNodesMap() const {
    return tileNodes_;
}

inline MapInfo TileNodeBuilder::GetMapInfo() const {
    return mapInfo_;
}
