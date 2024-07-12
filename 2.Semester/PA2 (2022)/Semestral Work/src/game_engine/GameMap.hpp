#pragma once
#include <map>
#include "../structures/Vector2.hpp"
#include "../game_objects/Tile.hpp"
#include "../game_objects/EmptyTile.hpp"
#include "../game_objects/WallTile.hpp"

/**
 * @brief Class that represents game maps in the game world.
 * 
 */
class GameMap {

  public:

    enum TilesTypes {
      WALL_TILE,
      EMPTY_TILE
    };

    GameMap() ;
    ~GameMap();


    void RenderMap();

    void GenerateMap ();

  private:

    void LoadTiles();
    void FreeTiles();

    static constexpr size_t MAX_TILES_NUMBER    = 2;

    Tile * tiles_ [MAX_TILES_NUMBER];

    map<Vector2<int>,Tile *> gameMap_;

};