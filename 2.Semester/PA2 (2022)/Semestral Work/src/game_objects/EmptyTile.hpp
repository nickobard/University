#pragma once
#include "Tile.hpp"

/**
 * @brief Class that represents Empty tile subclass of the
 * Tile superclass.
 * 
 */
class EmptyTile : public Tile {
  
  public:
    
    /**
     * @brief Construct a new Empty Tile object.
     * 
     * @param texture texture for graphics component to render the tile.
     */
    EmptyTile(Texture * texture);

    /**
     * @brief Render tile on the screen.
     * 
     * @param position where the tile should be rendered in pixels.
     */
    void Render( Vector2<float> position ) override;

    /**
     * @brief Get the type of the polymorphic tile.
     * 
     * @return int number of the enum Tile Types.
     */
    int GetType() override;

};