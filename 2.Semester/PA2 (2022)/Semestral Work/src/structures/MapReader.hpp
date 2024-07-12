#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Vector2.hpp"

using namespace std;

/// Structure that represents header info in the game map file.
struct MapHeader {

    /// Represents map size, first is rows, second is columns.
    pair<size_t, size_t> mapSize_ = {0, 0};
    /// Represents two connected portals in the game map.
    pair<Vector2<int>, Vector2<int>> portalsPair_;
    /// Represents spawn points for pacman and ghost,
    /// first is pacman or player, second is ghosts.
    pair<Vector2<int>, Vector2<int>> spawnPoints_;
    /// Stores true if there is no portals in the map.
    bool noPortals_;
};

/// Structure that represents read data about the tile from each layer of the game map.
struct TileData {

    /// Represents type of the tile - wall, empty, cross etc.
    char type_;
    /// Represents option on the tile - bonus, cherry, corner wall etc.
    char option_;
    /// Represents direction of the tile in its transform component.
    char direction_;
};

/**
 * @brief Class that reads map file and stores map chars in the 2D vector
 * for further parsing or processing, checking file stream and map size from
 * map header information.
 */
class MapReader {

public:

    /**
     * @brief Constructs map reader object.
     */
    MapReader() = default;

    /**
     * @brief Constructor, that reads and loads map.
     * @param path to the map file.
     */
    explicit MapReader(const string &path);

    /**
     * @brief Destructor of the map reader object.
     */
    ~MapReader();

    /**
     * @brief Opens, reads header and reads map from the file map.
     * @param path to map file.
     * @return true if successfully read file.
     * @return false if failed to read file.
     */
    bool Read(const string &path);

    /// Get 2D collection of TileData objects.
    inline const vector<vector<TileData>> &GetTilesData() const;

    /// Get map header of the read map..
    inline const MapHeader GetMapHeader() const;

private:

    /**
     * @brief Opens brace of the stored data in the game map file,
     * indicating start of the reading some useful data.
     * @return true if opened data stored after the open brace.
     * @return false if open brace is not presents and there is no stored data.
     */
    bool OpenBrace();

    /**
     * @brief Closes brace of the stored data, indicating end of the reading useful data.
     * @return true if successfully closed brace.
     * @return false if NOT closed brace successfully.
     */
    bool CloseBrace();

    /**
     * @brief Checks next chunk of data in the game map file.
     * @param dataType represents type of the expected data.
     * @return true if current chunk of data is of the specified dataType.
     * @return false if current chunk of data is NOT of the specified dataType.
     */
    bool CheckDataType(const string &dataType);

    /**
     * @brief Reads all game map layers - typemap, option map and direction map.
     * @return true if successfully loaded maps.
     * @return false if failed to load maps.
     */
    bool ReadMaps();

    /**
     * @brief Reads map of the specified type.
     * @param type of the map layer to be read.
     * @return true if read successfully desired type of the map layer.
     */
    bool ReadMap(const string &type);

    /**
     * @brief Inits 2D collection of tile data with size of the game map from the header.
     * @return true if successfully initialized 2D collection.
     */
    bool InitMap();

    /**
     * @brief Reads typemap layer of the game map and stores it to the tile data objects in collection.
     * @return true if success.
     */
    bool ReadTiles();

    /**
     * @brief Reads options layer of the game map and stores it to the collection of tile data objects.
     * @return true if success.
     */
    bool ReadOptions();

    /**
     * @brief Reads directions of the each tile form direction layer of the game map,
     * and stores it to the collection of the tile data objects.
     * @return true if success.
     */
    bool ReadDirections();

    /**
     * @brief Init input file stream to the map file. O(1).
     * @param path to the map file to open.
     * @return true if file is opened.
     * @return false if failed to open the file.
     */
    bool OpenMapFile(const string &path);

    /**
     * @brief Read map header with info about the map. O(1).
     * @return true if success.
     * @return false if failure.
     */
    bool ReadMapHeader();

    /**
     * @brief Read size of the game map form header of the map file.
     * @return true if successfully read size.
     */
    bool ReadSize();

    /**
     * @brief Read spawn points of the player and ghosts form header of the game map file.
     * @return true if success.
     */
    bool ReadSpawns();

    /**
     * @brief Read position of the spawn point or portal.
     * @param position of the spawn point or portal.
     * @return true if successfully read.
     */
    bool ReadPosition(Vector2<int> &position);

    /**
     * @brief Read portals if there are any from header of the game map file.
     * @return true if successfully read.
     */
    bool ReadPortals();


    /// Information about the game map.
    MapHeader header_;
    /// Input file stream to the map file.
    ifstream mapFileInput_;
    /// Loaded tiles data into 2D array.
    vector<vector<TileData>> tilesData;

};

inline const vector<vector<TileData>> &MapReader::GetTilesData() const {
    return tilesData;
}

inline const MapHeader MapReader::GetMapHeader() const {
    return header_;
}


