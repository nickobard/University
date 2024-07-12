#pragma once

#include "Tile.hpp"

/**
 * @brief Class that represents Wall tile subclass of the
 * Tile superclass.
 */
class WallTile : public Tile {

public:

    /**
     * @brief Construct a new Wall Tile object.
     * @param texture for graphics component to render the tile.
     * @param position where tile should be rendered.
     */
    WallTile(Texture *texture, const Vector2<float> &position);

    [[nodiscard]]
    bool isObstacle() const override;

    [[nodiscard]]
    TileType GetType() const override;

};