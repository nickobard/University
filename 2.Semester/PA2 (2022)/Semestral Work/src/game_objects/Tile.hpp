#pragma once
#include "../components/GraphicsComponent.hpp"

/**
 * @brief Abstract class representing Tiles in the map.
 * 
 */
class Tile {

  public:

    /**
     * @brief Enum representing all types of tiles in the game.
     * 
     */
    enum TileTypes {
      EMPTY_TILE,
      WALL_TILE
    };

    /**
     * @brief Construct a new Tile object.
     * 
     * @param texture texture to construct graphics component.
     */
    Tile( Texture * texture );

    /**
     * @brief Virtual destructor which destroys the Tile object.
     * 
     */
    virtual ~Tile();

    /**
     * @brief Pure virtual method to get the type of the tile.
     * 
     * @return int the type of the tile.
     */
    virtual int GetType() = 0;

    /**
     * @brief Pure virtual method to render the tile.
     * 
     * @param position where to render tile in pixels.
     */
    virtual void Render( Vector2<float> position ) = 0;

  protected:

    // Graphics component of the tile class.
    GraphicsComponent * graphics_;
};